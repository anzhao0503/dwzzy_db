#include "table.h"

TableManagement::TableManagement() {
	this->storage_manager = new StorageManagement();
	this->storage_manager->InitStorage("store.txt");
}

TableManagement::TableManagement(char* db_name) {
	this->storage_manager = new StorageManagement();
	this->storage_manager->InitStorage(db_name);
}
TableManagement::~TableManagement() {
	delete storage_manager;
}

int TableManagement::InitTable(char* tb_name, int db_id, int index, bool exist) {
	FILE* fp;
	if ((fp = fopen("benchmark_format.txt", "r")) == NULL) {
		cout<<"error find format"<<endl;
		return -1;
	}
	AttrType *types;
	int *attr_length;
	int attribute_num;
	int i = 0;
	char buffer[256];
	while(i<8) {
	   fgets(buffer, sizeof(buffer), fp);
	   char seg[] = " ";
	   char* substr;
	   substr = strtok(buffer, seg);
	   if (strcmp(substr, tb_name) == 0) {
		   // get table meta data
		   substr = strtok(NULL, seg);
		   int attr_num = atoi(substr);
		   attribute_num = attr_num;
		   attr_length = (int*)malloc(sizeof(int)*attribute_num);
		   types = (AttrType*)malloc(sizeof(AttrType)*attribute_num);
		   int j = 0;
		   int attr_len;
		   while (j < attr_num) {
			   substr = strtok(NULL, seg);
			   substr = strtok(NULL, seg);
			   AttrType type;
			   if (strcmp(substr, "INTEGER") == 0) {
				   type = INTEGER;
				   attr_len = 24;
			   } else if (strcmp(substr, "FLOAT") == 0) {
				   type = FLOAT;
				   attr_len = 24;
			   } else if (strcmp(substr, "CHAR") == 0) {
				   type = CHAR;
			   } else if (strcmp(substr, "VARCHAR") == 0) {
				   type = VARCHAR;
			   } else if (strcmp(substr, "DATE") == 0) {
				   type = DATE;
				   attr_len = 12;
			   }
			   types[j] = type;
			   substr = strtok(NULL, seg);
			   if (type == CHAR || type == VARCHAR) {
				   attr_len = atoi(substr) + 1;
			   }
			   attr_length[j] = attr_len;
			   j++;
		   }

		   // load data to disk and create Table
		   ADDR seg_id = this->storage_manager->addr_space.GetCurrentSeg();
		   ADDR start_addr = this->storage_manager->addr_space.GetCurrentAddr();
		   char buf[PAGE_SIZE+1];
		   long long tuple_num = 0;
		   off_t offset = tuple_num * MAX_TUPLE_SIZE;
		   int ret = 0;
		   lseek(this->storage_manager->fd,offset,SEEK_SET);
		   while ((ret = read(this->storage_manager->fd, buf, PAGE_SIZE)) != 0) {
			   this->storage_manager->Write(buf, PAGE_SIZE);
			   tuple_num += 8;
			   offset = tuple_num * MAX_TUPLE_SIZE;
			   lseek(this->storage_manager->fd,offset,SEEK_SET);
		   }
//		   this->storage_manager->FlushBlock();
		   Table* new_table = new Table(tb_name, db_id, index, seg_id, start_addr, exist, types, attr_length, attribute_num);
		   new_table->table_meta->tuple_num = tuple_num;
		   this->tables.insert((vector<Table*>::iterator)this->tables.begin()+index, new_table);
		   break;
	   }
	   else {
		   i++;
	   }
	}
	fclose(fp);
	return 1;
}

char* TableManagement::GetTuple(int tb_id, int index) {
	char page[PAGE_SIZE];
	char* result;
	result = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
	ADDR addr = this->tables[tb_id]->start_addr+index*MAX_TUPLE_SIZE;
	int re = this->storage_manager->ReadBuffer(addr, page, PAGE_SIZE);
	if (re != 0)
	{
		int off = this->storage_manager->GetOffset(addr);
		strncpy(result, page+off*MAX_TUPLE_SIZE, MAX_TUPLE_SIZE);
		return result;
	}
	else {
		return NULL;
	}
}

char* TableManagement::GetTuple(int tb_id, ADDR addr, int tmp) {
	char page[PAGE_SIZE];
	char* result;
	result = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
	int re = this->storage_manager->ReadBuffer(addr, page, PAGE_SIZE);
	if (re != 0)
	{
		int off = this->storage_manager->GetOffset(addr);
		strncpy(result, page+off*MAX_TUPLE_SIZE, MAX_TUPLE_SIZE);
		return result;
	}
	else {
		return NULL;
	}
}

int TableManagement::CreateIndex(int tb_id, int col) {
	Table* table = this->tables[tb_id];
	if (col > table->table_meta->attribute_num) {
		cout<<"wrong column number"<<endl;
		return -1;
	}
	char index_name[16];
	sprintf(index_name, "%d", tb_id);
	strcat(index_name, "_");
	char* tmp;
	sprintf(tmp, "%d", col);
	strcat(index_name, tmp);
	strcat(index_name, ".index");
	bpt::bplus_tree database(index_name, true);
	int index = col;
	for (int i = 0; i < table->table_meta->tuple_num; i++) {
		char* tuple;
		tuple = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
		memcpy(tuple, this->GetTuple(tb_id, i), MAX_TUPLE_SIZE);
		void* part;
		TypeMalloc(part, table->table_meta->attr_meta[index]->attribute_type, strlen(tuple+table->table_meta->attr_meta[index]->attribute_offset));
		Encoder::decode(tuple+table->table_meta->attr_meta[index]->attribute_offset, strlen(tuple+table->table_meta->attr_meta[index]->attribute_offset), part, table->table_meta->attr_meta[index]->attribute_type);
		database.insert((char*)part,table->start_addr+i*MAX_TUPLE_SIZE);
		free(tuple);
	}
	this->tables[tb_id]->table_meta->attr_meta[col]->attribute_index = 1;
	return 0;
}

int TableManagement::SearchIndex(FILE* fout, int tb_id, int col, char* keys[], Operator left_op, Operator right_op) {
	char index_name[16];
	sprintf(index_name, "%d", tb_id);
	strcat(index_name, "_");
	char* tmp;
	sprintf(tmp, "%d", col);
	strcat(index_name, tmp);
	strcat(index_name, ".index");
	bpt::bplus_tree database(index_name);
	if (sizeof(keys) == 1) {
		value_t value;
		if (database.search((char*)keys[0], &value) != 0)
			printf("Key %s not found\n", keys[0]);
		else{
			char* tuple;
			tuple = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
			memcpy(tuple, this->GetTuple(tb_id, value, -1), MAX_TUPLE_SIZE);
			fprintf(fout, "%s\n", tuple);
			free(tuple);
		}
	} else if (sizeof(keys) == 2) {
		bpt::key_t start(keys[0]);
		value_t values[4096];
		bool next = true;
		while (next) {
			int ret = database.search_range(&start, keys[1], values, 4096, left_op, right_op, &next);
			if (ret < 0)
				break;
			for (int i = 0; i < ret; i++) {
				char* tuple;
				tuple = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
				memcpy(tuple, this->GetTuple(tb_id, values[i], -1), MAX_TUPLE_SIZE);
				fprintf(fout, "%s\n", tuple);
				free(tuple);
			}
		}
	}
	fclose(fout);
	return 0;
}

bool TableManagement::GetTupleIndex(int tb_id, int col, char* keys[], Operator left_op, Operator right_op, char* result[]) {
	char index_name[16];
	sprintf(index_name, "%d", tb_id);
	strcat(index_name, "_");
	char* tmp;
	sprintf(tmp, "%d", col);
	strcat(index_name, tmp);
	strcat(index_name, ".index");
	bpt::bplus_tree database(index_name);
	if (sizeof(keys) == 1) {
		value_t value;
		if (database.search((char*)keys[0], &value) != 0) {
			printf("Key %s not found\n", keys[0]);
			return false;
		}
		else{
			char* tuple;
			tuple = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
			memcpy(tuple, this->GetTuple(tb_id, value, -1), MAX_TUPLE_SIZE);
			result[0] = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
			memcpy(result[0], tuple, sizeof(char)*MAX_TUPLE_SIZE);
		}
	} else if (sizeof(keys) == 2) {
		bpt::key_t start(keys[0]);
		value_t values[4096];
		bool next = true;
		int num = 0;
		while (next) {
			int ret = database.search_range(&start, keys[1], values, 4096, left_op, right_op, &next);
			if (ret < 0)
				break;
			for (int i = 0; i < ret; i++) {
				char* tuple;
				tuple = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
				memcpy(tuple, this->GetTuple(tb_id, values[i], -1), MAX_TUPLE_SIZE);
				result[num] = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
				memcpy(result[num], tuple, sizeof(char)*MAX_TUPLE_SIZE);
				num++;
			}
		}
	}
	return true;
}

int TableManagement::GetCmpCondition(vector<int> cols, vector<Operator>& operators, char* keys[], char* low, char* high) {
	if (cols.size() == 1) { // single condition equal
		if (operators[0] == eq) {
			return 1;
		} else if (operators[0] == le) {
			low = "!";
			high = keys[0];
			return 2;
		} else if (operators[0] == ge) {
			low = keys[0];
			high = "~";
			return 2;
		} else if (operators[0] == nq) {
			return 0;
		}
	} else if (cols.size() == 2) {
		if (cols[0] != cols[1]) {
			return -2;
		} else if ((operators[0] == ge || operators[0] == gt) && (operators[1] == le || operators[1] == lt)) {
			low = keys[0];
			high = keys[1];
			return 2;
		} else if ((operators[1] == ge || operators[1] == gt) && (operators[0] == le || operators[0] == lt)) {
			high = keys[0];
			low = keys[1];
			Operator tmp = operators[1];
			operators[1] = operators[0];
			operators[0] = tmp;
			return 2;
		}
		return -2;
	}
	return -1;
}

bool TableManagement::CheckTuple(int tb_id, char* tuple, vector<int> cols, vector<Operator> operators, char* keys[]) {
	Table* table = this->tables[tb_id];
	Operator op;
	for (int i = 0; i < cols.size(); i++) {
		void* part;
		TypeMalloc(part, table->table_meta->attr_meta[i]->attribute_type, strlen(tuple+table->table_meta->attr_meta[i]->attribute_offset));
		Encoder::decode(tuple+table->table_meta->attr_meta[i]->attribute_offset, strlen(tuple+table->table_meta->attr_meta[i]->attribute_offset), part, table->table_meta->attr_meta[i]->attribute_type);
		op = operators[i];
		if (table->table_meta->attr_meta[i]->attribute_type == INTEGER || table->table_meta->attr_meta[i]->attribute_type == DATE){
			int k = atoi(keys[i]);
			int getk = (int)((size_t)part);
			if (op == eq && getk != k) {
				return false;
			} else if (op == ge && getk < k) {
				return false;
			} else if (op == le && getk > k) {
				return false;
			} else if (op == lt && getk >= k) {
				return false;
			} else if (op == gt && getk <= k) {
				return false;
			}
		} else if (table->table_meta->attr_meta[i]->attribute_type == FLOAT) {
			float k = atol(keys[i]);
			float getk = (float)((size_t)part);
			float x = k - getk;
			if (op == eq && fabs(x) > EPSILON) {
				return false;
			} else if (op == ge && getk < k) {
				return false;
			} else if (op == le && getk > k) {
				return false;
			} else if (op == lt && (fabs(x) < EPSILON || getk > k)) {
				return false;
			} else if (op == gt && (fabs(x) < EPSILON || getk < k)) {
				return false;
			}
		}
		else{
			if (op == eq) {
				if (strcmp(keys[i], (char*)part) != 0) {
					return false;
				}
			} else if (op == ge) {
				if (strcmp((char*)part, keys[i]) < 0) {
					return false;
				}
			} else if (op == le) {
				if (strcmp((char*)part, keys[i]) > 0) {
					return false;
				}
			} else if (op == gt) {
				if (strcmp((char*)part, keys[i]) <= 0) {
					return false;
				}
			} else if (op == lt) {
				if (strcmp((char*)part, keys[i]) >= 0) {
					return false;
				}
			} else {
				return false;
			}
		}
	}
	return true;
}

bool TableManagement::TableScan(int tb_id) {
	Table* table = this->tables[tb_id];
	if (table->table_meta->tuple_num == 0)
		return false;
	FILE* fout;
	fout = fopen("result_tablescan", "w");
	if (!fout)
		return false;
	for (int i = 0; i < table->table_meta->tuple_num; i++) {
		char* tuple;
		tuple = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
		memcpy(tuple, this->GetTuple(tb_id, i), MAX_TUPLE_SIZE);
		// decode
		for (int j = 0; j < table->table_meta->attribute_num; j++) {
			void* part;
			TypeMalloc(part, table->table_meta->attr_meta[j]->attribute_type, strlen(tuple+table->table_meta->attr_meta[j]->attribute_offset));
			Encoder::decode(tuple+table->table_meta->attr_meta[j]->attribute_offset, strlen(tuple+table->table_meta->attr_meta[j]->attribute_offset), part, table->table_meta->attr_meta[j]->attribute_type);
			fprintf(fout, "%s\t", part);
		}
		fprintf(fout, "\n");
		free(tuple);
	}
	fclose(fout);
	return true;
}

bool TableManagement::IndexScan(int tb_id) {
	Table* table = this->tables[tb_id];
	if (table->table_meta->tuple_num == 0)
		return false;
	FILE* fout;
	fout = fopen("result_indexscan", "w");
	if (!fout)
		return false;
	char* keys[2];
	keys[0] = (char*)malloc(sizeof(char)*5);
	keys[0] = "!";
	keys[0] = (char*)malloc(sizeof(char)*5);
	keys[1] = "~";
	this->SearchIndex(fout, tb_id, 0, keys, ge, le);
	return true;
}

bool TableManagement::Select(int tb_id, vector<int> cols, vector<Operator> operators, char* keys[]) {
	Table* table = this->tables[tb_id];
	if (table->table_meta->tuple_num == 0)
		return false;
	char* low = "!";
	char* high = "~";
	int condition_count = this->GetCmpCondition(cols, operators, keys, low, high);
	FILE* fout;
	fout = fopen("result_tableselect", "w");
	if (condition_count == 1 && table->table_meta->attr_meta[cols[0]]->attribute_index != -1) {
		// equal condition select and has index
		this->SearchIndex(fout, tb_id, cols[0], keys, operators[0], operators[1]);
	} else if (condition_count == 2 && table->table_meta->attr_meta[cols[0]]->attribute_index != -1)  {
		//range condition select and has index
		char* input[2];
		input[0] = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
		input[1] = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
		memcpy(input[0], low, sizeof(low));
		memcpy(input[1], high, sizeof(high));
		this->SearchIndex(fout, tb_id, cols[0], input, operators[0], operators[1]);
	} else {
		// no index or without conditions or non-equal condition or multiple conditions
		for (int i = 0; i < table->table_meta->tuple_num; i++) {
			char* tuple;
			tuple = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
			memcpy(tuple, this->GetTuple(tb_id, i), MAX_TUPLE_SIZE);
			if (this->CheckTuple(tb_id, tuple, cols, operators, keys)) {
				fprintf(fout, "%s\n", tuple);
			}
		}
		fclose(fout);
	}
	return true;
}

bool TableManagement::Project(int tb_id, vector<int> cols) {
	Table* table = this->tables[tb_id];
	if (table->table_meta->tuple_num == 0)
		return false;
	FILE* fout;
	fout = fopen("result_project", "w");
	if (!fout)
		return false;
	if (cols.size() == 0) {
		// select *
		for (int i = 0; i < table->table_meta->tuple_num; i++) {
			char* tuple;
			tuple = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
			memcpy(tuple, this->GetTuple(tb_id, i), MAX_TUPLE_SIZE);
			// decode
			for (int j = 0; j < table->table_meta->attribute_num; j++) {
				void* part;
				TypeMalloc(part, table->table_meta->attr_meta[j]->attribute_type, strlen(tuple+table->table_meta->attr_meta[j]->attribute_offset));
				Encoder::decode(tuple+table->table_meta->attr_meta[j]->attribute_offset, strlen(tuple+table->table_meta->attr_meta[j]->attribute_offset), part, table->table_meta->attr_meta[j]->attribute_type);
				fprintf(fout, "%s\t", part);
			}
			fprintf(fout, "\n");
			free(tuple);
		}
	} else {
		for (int i = 0; i < table->table_meta->tuple_num; i++) {
			char* tuple;
			tuple = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
			memcpy(tuple, this->GetTuple(tb_id, i), MAX_TUPLE_SIZE);
			// decode
			for (int j = 0; j < cols.size(); j++) {
				int col = cols[j];
				void* part;
				TypeMalloc(part, table->table_meta->attr_meta[col]->attribute_type, strlen(tuple+table->table_meta->attr_meta[col]->attribute_offset));
				Encoder::decode(tuple+table->table_meta->attr_meta[col]->attribute_offset, strlen(tuple+table->table_meta->attr_meta[col]->attribute_offset), part, table->table_meta->attr_meta[col]->attribute_type);
				fprintf(fout, "%s\t", part);
			}
			fprintf(fout, "\n");
			free(tuple);
		}
	}
	fclose(fout);
	return true;
}

bool TableManagement::Project(FILE* fout, int tb_id, vector<int> cols) {
	Table* table = this->tables[tb_id];
	if (table->table_meta->tuple_num == 0)
		return false;
	if (!fout)
		return false;
	if (cols.size() == 0) {
		// select *
		for (int i = 0; i < table->table_meta->tuple_num; i++) {
			char* tuple;
			tuple = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
			memcpy(tuple, this->GetTuple(tb_id, i), MAX_TUPLE_SIZE);
			// decode
			for (int j = 0; j < table->table_meta->attribute_num; j++) {
				void* part;
				TypeMalloc(part, table->table_meta->attr_meta[j]->attribute_type, strlen(tuple+table->table_meta->attr_meta[j]->attribute_offset));
				Encoder::decode(tuple+table->table_meta->attr_meta[j]->attribute_offset, strlen(tuple+table->table_meta->attr_meta[j]->attribute_offset), part, table->table_meta->attr_meta[j]->attribute_type);
				fprintf(fout, "%s\t", part);
			}
			fprintf(fout, "\n");
			free(tuple);
		}
	} else {
		for (int i = 0; i < table->table_meta->tuple_num; i++) {
			char* tuple;
			tuple = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
			memcpy(tuple, this->GetTuple(tb_id, i), MAX_TUPLE_SIZE);
			// decode
			for (int j = 0; j < cols.size(); j++) {
				int col = cols[j];
				void* part;
				TypeMalloc(part, table->table_meta->attr_meta[col]->attribute_type, strlen(tuple+table->table_meta->attr_meta[col]->attribute_offset));
				Encoder::decode(tuple+table->table_meta->attr_meta[col]->attribute_offset, strlen(tuple+table->table_meta->attr_meta[col]->attribute_offset), part, table->table_meta->attr_meta[col]->attribute_type);
				fprintf(fout, "%s\t", part);
			}
			fprintf(fout, "\n");
			free(tuple);
		}
	}
	fclose(fout);
	return true;
}

bool TableManagement::SingleIndexJoin(int right_tb_id, int col2, char* keys[], Operator op, char* result[]) {

	if (op == eq) {
		char* tuple2;
		tuple2 = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
		this->GetTupleIndex(right_tb_id, col2, keys, eq, eq, result);
	} else if (op == ge || op == gt) {
		char* low = "!";
		char* high;
		high = (char*)malloc(sizeof(keys[0]));
		memcpy(high, keys[0], sizeof(keys[0]));
		this->GetTupleIndex(right_tb_id, col2, keys, op, le, result);
	} else if (op == le || op == lt) {
		char* high = "~";
		char* low;
		low = (char*)malloc(sizeof(keys[0]));
		memcpy(low, keys[0], sizeof(keys[0]));
		this->GetTupleIndex(right_tb_id, col2, keys, ge, op, result);
	} else {
		return NULL;
	}
	return true;
}

bool TableManagement::IndexJoin(int left_tb_id, int right_tb_id, vector<int> cols1, vector<int> cols2, vector<Operator> operators, bool isReverse) {
	Table* left_table = this->tables[left_tb_id];
	Table* right_table = this->tables[right_tb_id];
	if (left_table->table_meta->tuple_num == 0 || right_table->table_meta->tuple_num == 0) {
		return false;
	}
	if (cols1.size() != cols2.size() || cols1.size() != operators.size()) {
		return false;
	}
	FILE* fout;
	fout = fopen("result_indexjoin", "w");
	if (!fout)
		return false;
	if (cols1.size() == 1) {
		// single condition
		int col1 = cols1[0];
		int col2 = cols2[0];
		if (right_table->table_meta->attr_meta[col2]->attribute_index == -1) {
			// col2 in right table does not have index
			return false;
		}
		for (int i = 0; i < left_table->table_meta->tuple_num; i++) {
			char* tuple1;
			tuple1 = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
			memcpy(tuple1, this->GetTuple(left_tb_id, i), MAX_TUPLE_SIZE);
			// decode
			void* part;
			TypeMalloc(part, left_table->table_meta->attr_meta[col1]->attribute_type, strlen(tuple1+left_table->table_meta->attr_meta[col1]->attribute_offset));
			Encoder::decode(tuple1+left_table->table_meta->attr_meta[col1]->attribute_offset, strlen(tuple1+left_table->table_meta->attr_meta[col1]->attribute_offset), part, left_table->table_meta->attr_meta[col1]->attribute_type);
			char* keys[2];
			if (left_table->table_meta->attr_meta[col1]->attribute_type == INTEGER or left_table->table_meta->attr_meta[col1]->attribute_type == FLOAT || left_table->table_meta->attr_meta[col1]->attribute_type == DATE) {
				keys[0] = (char*)malloc(MAX_INT_ASCII_LENGTH);
				sprintf(keys[0], "%s", part);
			} else {
				keys[0] = (char*)malloc(MAX_VARCHAR_LENGTH);
				memcpy(keys[0], part, sizeof(part));
			}
			if (operators[0] == eq) {
				char* tuple2;
				tuple2 = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
				char* result[1];
				this->GetTupleIndex(right_tb_id, col2, keys, eq, eq, result);
				memcpy(tuple2, result[0], MAX_TUPLE_SIZE);
				if (tuple2 != NULL) {
					if (!isReverse) {
						for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
							void* part;
							TypeMalloc(part, left_table->table_meta->attr_meta[k]->attribute_type, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset));
							Encoder::decode(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset), part, left_table->table_meta->attr_meta[k]->attribute_type);
							fprintf(fout, "%s\t", part);
							free(part);
						}
						for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
							if (k != col2) {
								void* part;
								TypeMalloc(part, right_table->table_meta->attr_meta[k]->attribute_type, strlen(tuple2+right_table->table_meta->attr_meta[k]->attribute_offset));
								Encoder::decode(tuple2+right_table->table_meta->attr_meta[k]->attribute_offset, strlen(tuple2+right_table->table_meta->attr_meta[k]->attribute_offset), part, right_table->table_meta->attr_meta[k]->attribute_type);
								fprintf(fout, "%s\t", part);
								free(part);
							}
						}
						fprintf(fout, "\n");
					} else {
						for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
							void* part;
							TypeMalloc(part, right_table->table_meta->attr_meta[k]->attribute_type, strlen(tuple2+right_table->table_meta->attr_meta[k]->attribute_offset));
							Encoder::decode(tuple2+right_table->table_meta->attr_meta[k]->attribute_offset, strlen(tuple2+right_table->table_meta->attr_meta[k]->attribute_offset), part, right_table->table_meta->attr_meta[k]->attribute_type);
							fprintf(fout, "%s\t", part);
							free(part);
						}
						for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
							if (k != col1) {
								void* part;
								TypeMalloc(part, left_table->table_meta->attr_meta[k]->attribute_type, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset));
								Encoder::decode(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset), part, left_table->table_meta->attr_meta[k]->attribute_type);
								fprintf(fout, "%s\t", part);
								free(part);
							}
						}
						fprintf(fout, "\n");
					}
				}
				free(result);
			} else if (operators[0] == ge || operators[0] == gt) {
				char* low = "!";
				char* high;
				high = (char*)malloc(sizeof(keys[0]));
				memcpy(high, keys[0], sizeof(keys[0]));
				char* result[4096];
				this->GetTupleIndex(right_tb_id, col2, keys, operators[0], le, result);
				for (int j = 0; j < sizeof(result) / MAX_TUPLE_SIZE; j++) {
					if (!isReverse) {
						for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
							void* part;
							TypeMalloc(part, left_table->table_meta->attr_meta[k]->attribute_type, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset));
							Encoder::decode(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset), part, left_table->table_meta->attr_meta[k]->attribute_type);
							fprintf(fout, "%s\t", part);
							free(part);
						}
						for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
							if (k != col2) {
								void* part;
								TypeMalloc(part, right_table->table_meta->attr_meta[k]->attribute_type, strlen(result[j]+right_table->table_meta->attr_meta[k]->attribute_offset));
								Encoder::decode(result[j]+right_table->table_meta->attr_meta[k]->attribute_offset, strlen(result[j]+right_table->table_meta->attr_meta[k]->attribute_offset), part, right_table->table_meta->attr_meta[k]->attribute_type);
								fprintf(fout, "%s\t", part);
								free(part);
							}
						}
						fprintf(fout, "\n");
					} else {
						for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
							void* part;
							TypeMalloc(part, right_table->table_meta->attr_meta[k]->attribute_type, strlen(result[j]+right_table->table_meta->attr_meta[k]->attribute_offset));
							Encoder::decode(result[j]+right_table->table_meta->attr_meta[k]->attribute_offset, strlen(result[j]+right_table->table_meta->attr_meta[k]->attribute_offset), part, right_table->table_meta->attr_meta[k]->attribute_type);
							fprintf(fout, "%s\t", part);
							free(part);
						}
						for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
							if (k != col1) {
								void* part;
								TypeMalloc(part, left_table->table_meta->attr_meta[k]->attribute_type, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset));
								Encoder::decode(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset), part, left_table->table_meta->attr_meta[k]->attribute_type);
								fprintf(fout, "%s\t", part);
								free(part);
							}
						}
						fprintf(fout, "\n");
					}
				}
				free(result);
			} else if (operators[0] == le || operators[0] == lt) {
				char* high = "~";
				char* low;
				low = (char*)malloc(sizeof(keys[0]));
				memcpy(low, keys[0], sizeof(keys[0]));
				char* result[4096];
				this->GetTupleIndex(right_tb_id, col2, keys, ge, operators[0], result);
				for (int j = 0; j < sizeof(result) / MAX_TUPLE_SIZE; j++) {
					if (!isReverse) {
						for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
							void* part;
							TypeMalloc(part, left_table->table_meta->attr_meta[k]->attribute_type, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset));
							Encoder::decode(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset), part, left_table->table_meta->attr_meta[k]->attribute_type);
							fprintf(fout, "%s\t", part);
							free(part);
						}
						for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
							if (k != col2) {
								void* part;
								TypeMalloc(part, right_table->table_meta->attr_meta[k]->attribute_type, strlen(result[j]+right_table->table_meta->attr_meta[k]->attribute_offset));
								Encoder::decode(result[j]+right_table->table_meta->attr_meta[k]->attribute_offset, strlen(result[j]+right_table->table_meta->attr_meta[k]->attribute_offset), part, right_table->table_meta->attr_meta[k]->attribute_type);
								fprintf(fout, "%s\t", part);
								free(part);
							}
						}
						fprintf(fout, "\n");
					} else {
						for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
							void* part;
							TypeMalloc(part, right_table->table_meta->attr_meta[k]->attribute_type, strlen(result[j]+right_table->table_meta->attr_meta[k]->attribute_offset));
							Encoder::decode(result[j]+right_table->table_meta->attr_meta[k]->attribute_offset, strlen(result[j]+right_table->table_meta->attr_meta[k]->attribute_offset), part, right_table->table_meta->attr_meta[k]->attribute_type);
							fprintf(fout, "%s\t", part);
							free(part);
						}
						for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
							if (k != col1) {
								void* part;
								TypeMalloc(part, left_table->table_meta->attr_meta[k]->attribute_type, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset));
								Encoder::decode(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset), part, left_table->table_meta->attr_meta[k]->attribute_type);
								fprintf(fout, "%s\t", part);
								free(part);
							}
						}
						fprintf(fout, "\n");
					}
				}
				free(result);
			} else {
				// non-equal
				cols1.push_back(cols1[0]);
				cols2.push_back(cols2[0]);
				operators[0] = lt;
				operators.push_back(gt);
				char* result1[4096];
				this->SingleIndexJoin(right_tb_id, cols2[0], keys, operators[0], result1);
				for (int j = 0; j < sizeof(result1) / MAX_TUPLE_SIZE; j++) {
					if (!isReverse) {
						for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
							void* part;
							TypeMalloc(part, left_table->table_meta->attr_meta[k]->attribute_type, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset));
							Encoder::decode(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset), part, left_table->table_meta->attr_meta[k]->attribute_type);
							fprintf(fout, "%s\t", part);
							free(part);
						}
						for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
							if (k != col2) {
								void* part;
								TypeMalloc(part, right_table->table_meta->attr_meta[k]->attribute_type, strlen(result1[j]+right_table->table_meta->attr_meta[k]->attribute_offset));
								Encoder::decode(result1[j]+right_table->table_meta->attr_meta[k]->attribute_offset, strlen(result1[j]+right_table->table_meta->attr_meta[k]->attribute_offset), part, right_table->table_meta->attr_meta[k]->attribute_type);
								fprintf(fout, "%s\t", part);
								free(part);
							}
						}
						fprintf(fout, "\n");
					} else {
						for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
							void* part;
							TypeMalloc(part, right_table->table_meta->attr_meta[k]->attribute_type, strlen(result1[j]+right_table->table_meta->attr_meta[k]->attribute_offset));
							Encoder::decode(result1[j]+right_table->table_meta->attr_meta[k]->attribute_offset, strlen(result1[j]+right_table->table_meta->attr_meta[k]->attribute_offset), part, right_table->table_meta->attr_meta[k]->attribute_type);
							fprintf(fout, "%s\t", part);
							free(part);
						}
						for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
							if (k != col1) {
								void* part;
								TypeMalloc(part, left_table->table_meta->attr_meta[k]->attribute_type, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset));
								Encoder::decode(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset), part, left_table->table_meta->attr_meta[k]->attribute_type);
								fprintf(fout, "%s\t", part);
								free(part);
							}
						}
						fprintf(fout, "\n");
					}
				}
				free(result1);

				char* result2[4096];
				this->SingleIndexJoin(right_tb_id, cols2[1], keys, operators[1], result2);
				for (int j = 0; j < sizeof(result2) / MAX_TUPLE_SIZE; j++) {
					if (!isReverse) {
						for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
							void* part;
							TypeMalloc(part, left_table->table_meta->attr_meta[k]->attribute_type, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset));
							Encoder::decode(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset), part, left_table->table_meta->attr_meta[k]->attribute_type);
							fprintf(fout, "%s\t", part);
							free(part);
						}
						for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
							if (k != col2) {
								void* part;
								TypeMalloc(part, right_table->table_meta->attr_meta[k]->attribute_type, strlen(result2[j]+right_table->table_meta->attr_meta[k]->attribute_offset));
								Encoder::decode(result2[j]+right_table->table_meta->attr_meta[k]->attribute_offset, strlen(result2[j]+right_table->table_meta->attr_meta[k]->attribute_offset), part, right_table->table_meta->attr_meta[k]->attribute_type);
								fprintf(fout, "%s\t", part);
								free(part);
							}
						}
						fprintf(fout, "\n");
					} else {
						for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
							void* part;
							TypeMalloc(part, right_table->table_meta->attr_meta[k]->attribute_type, strlen(result2[j]+right_table->table_meta->attr_meta[k]->attribute_offset));
							Encoder::decode(result2[j]+right_table->table_meta->attr_meta[k]->attribute_offset, strlen(result2[j]+right_table->table_meta->attr_meta[k]->attribute_offset), part, right_table->table_meta->attr_meta[k]->attribute_type);
							fprintf(fout, "%s\t", part);
							free(part);
						}
						for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
							if (k != col1) {
								void* part;
								TypeMalloc(part, left_table->table_meta->attr_meta[k]->attribute_type, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset));
								Encoder::decode(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset), part, left_table->table_meta->attr_meta[k]->attribute_type);
								fprintf(fout, "%s\t", part);
								free(part);
							}
						}
						fprintf(fout, "\n");
					}
				}
				free(result2);
			}
		}
	} else {
		// multiple conditions
		int col1 = cols1[0];
		int col2 = cols2[0];
		for (int i = 0; i < left_table->table_meta->tuple_num; i++) {
			char* tuple1;
			tuple1 = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
			memcpy(tuple1, this->GetTuple(left_tb_id, i), MAX_TUPLE_SIZE);
			// decode
			void* part;
			TypeMalloc(part, left_table->table_meta->attr_meta[col1]->attribute_type, strlen(tuple1+left_table->table_meta->attr_meta[col1]->attribute_offset));
			Encoder::decode(tuple1+left_table->table_meta->attr_meta[col1]->attribute_offset, strlen(tuple1+left_table->table_meta->attr_meta[col1]->attribute_offset), part, left_table->table_meta->attr_meta[col1]->attribute_type);
			char* keys[1];
			if (left_table->table_meta->attr_meta[col1]->attribute_type == INTEGER or left_table->table_meta->attr_meta[col1]->attribute_type == FLOAT || left_table->table_meta->attr_meta[col1]->attribute_type == DATE) {
				keys[0] = (char*)malloc(MAX_INT_ASCII_LENGTH);
				sprintf(keys[0], "%s", part);
			} else {
				keys[0] = (char*)malloc(MAX_VARCHAR_LENGTH);
				memcpy(keys[0], part, sizeof(part));
			}
			free(part);
			char* tuples1[4096]; // result of condition 1
			this->SingleIndexJoin(right_tb_id, cols2[0], keys, operators[0], tuples1);
			vector<int> cols(cols1.size()-1);
			vector<Operator> ops(cols1.size()-1);
			for (int idx = 0; idx < cols1.size() - 1; idx++) {
				cols.push_back(cols1[idx+1]);
				ops.push_back(operators[idx+1]);
			}
			char* other_keys[4];
			for (int idx = 1; idx < cols1.size(); idx++) {
				TypeMalloc(part, left_table->table_meta->attr_meta[cols1[idx]]->attribute_type, strlen(tuple1+left_table->table_meta->attr_meta[cols1[idx]]->attribute_offset));
				Encoder::decode(tuple1+left_table->table_meta->attr_meta[cols1[idx]]->attribute_offset, strlen(tuple1+left_table->table_meta->attr_meta[cols1[idx]]->attribute_offset), part, left_table->table_meta->attr_meta[col1]->attribute_type);
				if (left_table->table_meta->attr_meta[cols1[idx]]->attribute_type == INTEGER or left_table->table_meta->attr_meta[cols1[idx]]->attribute_type == FLOAT || left_table->table_meta->attr_meta[cols1[idx]]->attribute_type == DATE) {
					other_keys[idx-1] = (char*)malloc(MAX_INT_ASCII_LENGTH);
					sprintf(other_keys[idx-1], "%s", part);
				} else {
					other_keys[idx-1] = (char*)malloc(MAX_VARCHAR_LENGTH);
					memcpy(other_keys[idx-1], part, sizeof(part));
				}
				free(part);
			}
			for (int j = 0; j < sizeof(tuples1) / MAX_TUPLE_SIZE; j++) {
				if (this->CheckTuple(right_tb_id, tuples1[j], cols, ops, other_keys)) {
					// fit other conditions
					if (!isReverse) {
						for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
							void* part;
							TypeMalloc(part, left_table->table_meta->attr_meta[k]->attribute_type, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset));
							Encoder::decode(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset), part, left_table->table_meta->attr_meta[k]->attribute_type);
							fprintf(fout, "%s\t", part);
							free(part);
						}
						for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
							if (k != col2) {
								void* part;
								TypeMalloc(part, right_table->table_meta->attr_meta[k]->attribute_type, strlen(tuples1[j]+right_table->table_meta->attr_meta[k]->attribute_offset));
								Encoder::decode(tuples1[j]+right_table->table_meta->attr_meta[k]->attribute_offset, strlen(tuples1[j]+right_table->table_meta->attr_meta[k]->attribute_offset), part, right_table->table_meta->attr_meta[k]->attribute_type);
								fprintf(fout, "%s\t", part);
								free(part);
							}
						}
						fprintf(fout, "\n");
					} else {
						for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
							void* part;
							TypeMalloc(part, right_table->table_meta->attr_meta[k]->attribute_type, strlen(tuples1[j]+right_table->table_meta->attr_meta[k]->attribute_offset));
							Encoder::decode(tuples1[j]+right_table->table_meta->attr_meta[k]->attribute_offset, strlen(tuples1[j]+right_table->table_meta->attr_meta[k]->attribute_offset), part, right_table->table_meta->attr_meta[k]->attribute_type);
							fprintf(fout, "%s\t", part);
							free(part);
						}
						for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
							if (k != col1) {
								void* part;
								TypeMalloc(part, left_table->table_meta->attr_meta[k]->attribute_type, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset));
								Encoder::decode(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset), part, left_table->table_meta->attr_meta[k]->attribute_type);
								fprintf(fout, "%s\t", part);
								free(part);
							}
						}
						fprintf(fout, "\n");
					}
				}
			}
		}

	}
	return true;
}

bool TableManagement::ProductIndexJoin(int left_tb_id, int right_tb_id) {
	Table* left_table = this->tables[left_tb_id];
	Table* right_table = this->tables[right_tb_id];
	if (left_table->table_meta->tuple_num == 0 || right_table->table_meta->tuple_num == 0) {
		return false;
	}
	FILE* fout;
	fout = fopen("result_productindexjoin", "w");
	if (!fout)
		return false;
	for (int i = 0; i < left_table->table_meta->tuple_num; i++) {
		char* tuple1;
		tuple1 = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
		memcpy(tuple1, this->GetTuple(left_tb_id, i), MAX_TUPLE_SIZE);
		// decode
		void* part;
		TypeMalloc(part, left_table->table_meta->attr_meta[0]->attribute_type, strlen(tuple1+left_table->table_meta->attr_meta[0]->attribute_offset));
		Encoder::decode(tuple1+left_table->table_meta->attr_meta[0]->attribute_offset, strlen(tuple1+left_table->table_meta->attr_meta[0]->attribute_offset), part, left_table->table_meta->attr_meta[0]->attribute_type);
		char* keys[2];
		keys[0] = (char*)malloc(sizeof(char)*5);
		keys[0] = "!";
		keys[0] = (char*)malloc(sizeof(char)*5);
		keys[1] = "~";
		char* result1[4096];
		this->GetTupleIndex(right_tb_id, 0, keys, ge, le, result1);
		for (int j = 0; j < sizeof(result1) / MAX_TUPLE_SIZE; j++) {
			for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
				void* part;
				TypeMalloc(part, left_table->table_meta->attr_meta[k]->attribute_type, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset));
				Encoder::decode(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset, strlen(tuple1+left_table->table_meta->attr_meta[k]->attribute_offset), part, left_table->table_meta->attr_meta[k]->attribute_type);
				fprintf(fout, "%s\t", part);
				free(part);
			}
			for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
				void* part;
				TypeMalloc(part, right_table->table_meta->attr_meta[k]->attribute_type, strlen(result1[j]+right_table->table_meta->attr_meta[k]->attribute_offset));
				Encoder::decode(result1[j]+right_table->table_meta->attr_meta[k]->attribute_offset, strlen(result1[j]+right_table->table_meta->attr_meta[k]->attribute_offset), part, right_table->table_meta->attr_meta[k]->attribute_type);
				fprintf(fout, "%s\t", part);
				free(part);
			}
			fprintf(fout, "\n");
		}
	}
	return true;
}

Table::Table(char* name, int db_id, int index, ADDR seg_id, ADDR start_addr, bool exist, AttrType *types, int *attr_length, int attribute_num) {
	this->db_id = db_id;
	this->start_addr = start_addr;
	this->index = index;
	if (!exist) {
		// not in the disk
		TableMeta* new_table_meta = new TableMeta();
		memcpy(new_table_meta->table_name, name, MAX_TABLE_NAME_LENGTH);
		new_table_meta->db_id = db_id;
		new_table_meta->start_addr = start_addr;
		new_table_meta->attribute_num = attribute_num;
		int off = 0;
		for (int i = 0; i < attribute_num; i++) {
			AttributeMeta* new_attr_meta = new AttributeMeta();
			new_attr_meta->attribute_index = i;
			new_attr_meta->attribute_type = types[i];
			new_attr_meta->attribute_length = attr_length[i];
			new_attr_meta->attribute_offset = off;
			off += attr_length[i];
			new_table_meta->attr_meta.push_back(new_attr_meta);
		}
		this->table_meta = new_table_meta;
		if (meta_info->db_meta.size() <= db_id) {
			// database not exists
			DBMeta* new_db_meta = new DBMeta();
			new_db_meta->seg_id = seg_id;
			new_db_meta->table_num = 1;
			new_db_meta->table_meta.push_back(new_table_meta);
			meta_info->db_meta.insert((vector<DBMeta*>::iterator)meta_info->db_meta.begin()+db_id, new_db_meta);
			meta_info->db_meta[db_id]->table_num = 1;
		} else {
			meta_info->db_meta[db_id]->table_meta.insert((vector<TableMeta*>::iterator)meta_info->db_meta[db_id]->table_meta.begin()+index, new_table_meta);
			meta_info->db_meta[db_id]->table_num++;
		}
	}
	else {
		this->table_meta = meta_info->db_meta[db_id]->table_meta[index];
	}
}


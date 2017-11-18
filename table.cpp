#include "table.h"

TableManagement::TableManagement() {
	this->storage_manager = new StorageManagement();
	this->storage_manager->InitStorage("store.txt");
	this->tables = new vector<Table>();
}

TableManagement::TableManagement(char* db_name) {
	this->storage_manager = new StorageManagement();
	this->storage_manager->InitStorage(db_name);
	this->tables = new vector<Table>();
}
TableManagement::~TableManagement() {
	delete storage_manager;
}

int TableManagement::InitTable(char* tb_name, int db_id, int index, bool exist) {
	FILE* fp;
	if ((fp = fopen("benchmark_format.txt", "r")) == NULL) {
		cout<<"error"<<endl;
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
	   if (strcpy(substr, tb_name) == 0) {
		   // get table meta data
		   substr = strtok(NULL, seg);
		   int attr_num = atoi(substr);
		   attribute_num = attr_num;
		   attr_length = (int*)malloc(sizeof(int)*attribute_num);
		   types = (AttrType*)malloc(sizeof(AttrType)*attribute_num);
		   int j = 0;
		   while (j < attr_num) {
			   substr = strtok(NULL, seg);
			   substr = strtok(NULL, seg);
			   AttrType type;
			   if (strcpy(substr, "INTEGER") == 0) {
				   type = INTEGER;
			   } else if (strcpy(substr, "FLOAT") == 0) {
				   type = FLOAT;
			   } else if (strcpy(substr, "CHAR") == 0) {
				   type = CHAR;
			   } else if (strcpy(substr, "VARCHAR") == 0) {
				   type = VARCHAR;
			   } else if (strcpy(substr, "DATE") == 0) {
				   type = DATE;
			   }
			   types[j] = type;
			   substr = strtok(NULL, seg);
			   int attr_len = atoi(substr);
			   attr_length[j] = attr_len;
			   j++;
		   }

		   // load data to disk and create Table
		   ADDR seg_id = this->storage_manager->addr_space.GetCurrentSeg();
		   ADDR start_addr = this->storage_manager->addr_space.GetCurrentAddr();
		   FILE* fp1;
		   if ((fp1 = fopen(tb_name, "r")) == NULL) {
		   		cout<<"error"<<endl;
		   		return -1;
		   	}
		   char buf[MAX_TUPLE_SIZE+1];
		   int tuple_num = 0;
		   while (!feof(fp1)) {
			   fgets(buf, sizeof(buf), fp);
			   char* input = (char*)calloc(sizeof(char)*MAX_TUPLE_SIZE+1, sizeof(char));
			   char seg1[] = "|";
			   char* substr1;
			   char* part;
			   int j = 0;
			   while (j < attribute_num) {
				   substr1 = strtok(buf, seg1);
				   int res = Encoder::encode(substr1, part, attr_length[j], types[j]);
				   if (res != -1) {
					   strcat(input, part);
				   }
				   j++;
			   }
			   this->storage_manager->Write(input, MAX_TUPLE_SIZE);
			   tuple_num += 1;
			   free(input);
		   }
		   Table new_table = new Table(tb_name, db_id, index, seg_id, start_addr, exist, types, attr_length, attribute_num);
		   new_table.table_meta->tuple_num = tuple_num;
		   this->tables.insert((vector<Table>::iterator)this->tables+index, new_table);
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
	char result[MAX_TUPLE_SIZE];
	ADDR addr = this->tables[tb_id].start_addr+index*MAX_TUPLE_SIZE;
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
	char result[MAX_TUPLE_SIZE];
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
	Table table = this->tables[tb_id];
	if (col > table.table_meta->attribute_num) {
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
	for (int i = 0; i < table.table_meta->tuple_num; i++) {
		char* tuple;
		tuple = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
		memcpy(tuple, this->GetTuple(tb_id, i), MAX_TUPLE_SIZE);
		char* col_content;
		void* part;
		col_content = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
		strncpy(col_content, tuple+table.table_meta->attr_meta[index].attribute_offset, table.table_meta->attr_meta[index].attribute_length);
		Encoder::decode(col_content, table.table_meta->attr_meta[index].attribute_length, part, table.table_meta->attr_meta[index].attribute_type);
		database.insert(col_content,table.start_addr+i*MAX_TUPLE_SIZE);
		free(tuple);
		free(col_content);
	}
	this->tables[tb_id].table_meta->attr_meta[col].attribute_index = 1;
	return 0;
}

int TableManagement::SearchIndex(FILE* fout, int tb_id, int col, char* keys[]) {
	Table table = this->tables[tb_id];
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
			int ret = database.search_range(&start, keys[1], values, 4096, &next);
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
	return 0;
}

int TableManagement::GetCmpCondition(vector<int> cols, vector<Operator> operators, char* keys[], char*& low, char*& high) {
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
			return 2;
		}
		return -2;
	}
	return -1;
}

bool TableManagement::TableScan(int tb_id) {
	Table table = this->tables[tb_id];
	if (table.table_meta->tuple_num == 0)
		return false;
	FILE* fout;
	fout = fopen("result_tablescan", "w");
	if (!fout)
		return false;
	for (int i = 0; i < table.table_meta->tuple_num; i++) {
		char* tuple;
		tuple = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
		memcpy(tuple, this->GetTuple(tb_id, i), MAX_TUPLE_SIZE);
		// decode
		for (int j = 0; j < table.table_meta->attribute_num; j++) {
			char* col_content;
			void* part;
			col_content = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
			strncpy(col_content, tuple+table.table_meta->attr_meta[j].attribute_offset, table.table_meta->attr_meta[j].attribute_length);
			Encoder::decode(col_content, table.table_meta->attr_meta[j].attribute_length, part, table.table_meta->attr_meta[j].attribute_type);
			fprintf(fout, "%s\t", col_content);
			free(col_content);
		}
		fprintf(fout, "\n");
		free(tuple);
	}
	fclose(fout);
	return true;
}


bool TableManagement::SingleSelect(int tb_id, vector<int> cols, vector<Operator> operators, char* keys[]) {
	Table table = this->tables[tb_id];
	if (table.table_meta->tuple_num == 0)
		return false;
	char* low = "!";
	char* high = "~";
	int condition_count = this->GetCmpCondition(cols, operators, keys, low, high);
	FILE* fout;
	fout = fopen("result_tableselect", "w");
	if (condition_count >= 1 && table.table_meta->attr_meta[cols[0]].attribute_index != -1) {
		// condition select and has index
		this->SearchIndex(fout, tb_id, cols[0], keys);
	} else {
		// without conditions
		this->Project(fout, tb_id, cols);
	}
	return true;
}

bool TableManagement::Project(int tb_id, vector<int> cols) {
	Table table = this->tables[tb_id];
	if (table.table_meta->tuple_num == 0)
		return false;
	FILE* fout;
	fout = fopen("result_project", "w");
	if (!fout)
		return false;
	if (cols.size() == 0) {
		// select *
		for (int i = 0; i < table.table_meta->tuple_num; i++) {
			char* tuple;
			tuple = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
			memcpy(tuple, this->GetTuple(tb_id, i), MAX_TUPLE_SIZE);
			// decode
			for (int j = 0; j < table.table_meta->attribute_num; j++) {
				char* col_content;
				void* part;
				col_content = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
				strncpy(col_content, tuple+table.table_meta->attr_meta[j].attribute_offset, table.table_meta->attr_meta[j].attribute_length);
				Encoder::decode(col_content, table.table_meta->attr_meta[j].attribute_length, part, table.table_meta->attr_meta[j].attribute_type);
				fprintf(fout, "%s\t", col_content);
				free(col_content);
			}
			fprintf(fout, "\n");
			free(tuple);
		}
	} else {
		for (int i = 0; i < table.table_meta->tuple_num; i++) {
			char* tuple;
			tuple = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
			memcpy(tuple, this->GetTuple(tb_id, i), MAX_TUPLE_SIZE);
			// decode
			for (int j = 0; j < cols.size(); j++) {
				char* col_content;
				int col = cols[j];
				void* part;
				col_content = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
				strncpy(col_content, tuple+table.table_meta->attr_meta[col].attribute_offset, table.table_meta->attr_meta[col].attribute_length);
				Encoder::decode(col_content, table.table_meta->attr_meta[col].attribute_length, part, table.table_meta->attr_meta[col].attribute_type);
				fprintf(fout, "%s\t", col_content);
				free(col_content);
			}
			fprintf(fout, "\n");
			free(tuple);
		}
	}
	fclose(fout);
	return true;
}

bool TableManagement::Project(FILE* fout, int tb_id, vector<int> cols) {
	Table table = this->tables[tb_id];
	if (table.table_meta->tuple_num == 0)
		return false;
	if (!fout)
		return false;
	if (cols.size() == 0) {
		// select *
		for (int i = 0; i < table.table_meta->tuple_num; i++) {
			char* tuple;
			tuple = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
			memcpy(tuple, this->GetTuple(tb_id, i), MAX_TUPLE_SIZE);
			// decode
			for (int j = 0; j < table.table_meta->attribute_num; j++) {
				char* col_content;
				void* part;
				col_content = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
				strncpy(col_content, tuple+table.table_meta->attr_meta[j].attribute_offset, table.table_meta->attr_meta[j].attribute_length);
				Encoder::decode(col_content, table.table_meta->attr_meta[j].attribute_length, part, table.table_meta->attr_meta[j].attribute_type);
				fprintf(fout, "%s\t", col_content);
				free(col_content);
			}
			fprintf(fout, "\n");
			free(tuple);
		}
	} else {
		for (int i = 0; i < table.table_meta->tuple_num; i++) {
			char* tuple;
			tuple = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
			memcpy(tuple, this->GetTuple(tb_id, i), MAX_TUPLE_SIZE);
			// decode
			for (int j = 0; j < cols.size(); j++) {
				char* col_content;
				int col = cols[j];
				void* part;
				col_content = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
				strncpy(col_content, tuple+table.table_meta->attr_meta[col].attribute_offset, table.table_meta->attr_meta[col].attribute_length);
				Encoder::decode(col_content, table.table_meta->attr_meta[col].attribute_length, part, table.table_meta->attr_meta[col].attribute_type);
				fprintf(fout, "%s\t", col_content);
				free(col_content);
			}
			fprintf(fout, "\n");
			free(tuple);
		}
	}
	fclose(fout);
	return true;
}

Table::Table(char* name, int db_id, int index, ADDR seg_id, ADDR start_addr, bool exist, AttrType *types, int *attr_length, int attribute_num) {
	this->db_id = db_id;
	this->start_addr = start_addr;
	this->index = index;
	if (!exist) {
		// not in the disk
		TableMeta new_table_meta = new TableMeta();
		memcpy(new_table_meta.table_name, name, MAX_TABLE_NAME_LENGTH);
		new_table_meta.db_id = db_id;
		new_table_meta.start_addr = start_addr;
		new_table_meta.attribute_num = attribute_num;
		int off = 0;
		for (int i = 0; i < attribute_num; i++) {
			AttributeMeta new_attr_meta = new AttributeMeta();
			new_attr_meta.attribute_index = i;
			new_attr_meta.attribute_type = types[i];
			new_attr_meta.attribute_length = attr_length[i];
			new_attr_meta.attribute_offset = off;
			off += attr_length[i];
			new_table_meta.attr_meta.push_back(new_attr_meta);
		}
		this->table_meta = new_table_meta;
		if (meta_info.db_meta.size() <= db_id) {
			// database not exists
			DBMeta new_db_meta = new DBMeta();
			new_db_meta.seg_id = seg_id;
			new_db_meta.table_num = 1;
			new_db_meta.table_meta.push_back(new_table_meta);
			meta_info.db_meta.insert((vector<DBMeta>::iterator)meta_info.db_meta.begin()+db_id, new_db_meta);
			meta_info.db_meta[db_id].table_num = 1;
		} else {
			meta_info.db_meta[db_id].table_meta.insert((vector<TableMeta>::iterator)meta_info.db_meta[db_id].table_meta.begin()+index, new_table_meta);
			meta_info.db_meta[db_id].table_num++;
		}
	}
	else {
		this->table_meta = meta_info.db_meta[db_id].table_meta[index];
	}
}

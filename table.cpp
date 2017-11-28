#include "table.h"
const char data_dir[32] = "../../db_data/";

TableManagement::TableManagement() {
	this->storage_manager = new StorageManagement();
//	this->storage_manager->InitStorage("store.txt");
}

TableManagement::TableManagement(vector<char*> tb_names) {
	this->storage_manager = new StorageManagement();
	this->storage_manager->InitStorage(tb_names);
}
TableManagement::~TableManagement() {
	delete storage_manager;
}

TableMeta* TableManagement::GetTableMeta(int table_index){
	vector<Table*>::iterator iter;
	int i = 0;
	for(iter = (this->tables).begin(); i != table_index; i++, iter ++){}
	return (*iter)->table_meta;
}

int TableManagement::CartesianProduct(int* table_indexs){
	TableMeta* table_meta[2];
	int fd[2] = {0,0}; 
	int fd_output;
	int tuple_num[2];
	uint64_t offset_table_s = 0;
	uint64_t offset_table_b = 0;
	uint64_t offset_rst = 0;
	size_t bytes_rtn;
	uint64_t rst_count = 0, rst_index = 0;
	char* rst_buf = (char*)malloc(sizeof(char)*TUPLE_SIZE*2*OUTPUT_BUF_SIZE);
	char* buf = (char*)malloc(sizeof(char)*BLOCK_SIZE*BLOCK_NUM);
	for(int i = 0;i < 2;i++){
		fd[i] = open(this->GetTableMeta(table_indexs[i])->data_file_path, O_RDONLY);
	}
	fd_output = open("output.txt", O_RDWR | O_CREAT);
	if(fd_output == NULL){printf("error");}
	bytes_rtn = read(fd[0], buf, BLOCK_SIZE*(BLOCK_NUM - 1));
	tuple_num[0] = bytes_rtn / TUPLE_SIZE;
	while(true){
		bytes_rtn = read(fd[1], buf + BLOCK_SIZE*(BLOCK_NUM - 1), BLOCK_SIZE);
		if(bytes_rtn == 0){
			break;
		}
		for(int j = 0; j < bytes_rtn / TUPLE_SIZE; j++){
			for(int k = 0; k < tuple_num[0]; k++){
				memcpy(rst_buf + offset_rst, buf + BLOCK_SIZE*(BLOCK_NUM - 1) + offset_table_s, TUPLE_SIZE);
				offset_rst += TUPLE_SIZE;
				memcpy(rst_buf + offset_rst, buf + offset_table_b, TUPLE_SIZE);
				offset_rst += TUPLE_SIZE;
				offset_table_b += TUPLE_SIZE;
				rst_count ++;
				rst_index ++;
				if(rst_index == OUTPUT_BUF_SIZE){
					rst_index = 0;
					offset_rst = 0;
					write(fd_output, rst_buf, TUPLE_SIZE*2*OUTPUT_BUF_SIZE);
				}
			}
			offset_table_s += TUPLE_SIZE;
			offset_table_b += 0;
		}
		write(fd_output, rst_buf, TUPLE_SIZE*2*rst_index);
		
	}
	free(buf);
	close(fd_output);
	for(int i = 0;i < 2;i++){
		close(fd[i]);
	}
}

int TableManagement::Join(int* table_indexs, int* attr_indexs, bool equal_flag){
	TableMeta* table_meta[2];
	AttributeMeta* attr_meta[2];
	int fd[2] = {0,0}; 
	int fd_output;
	int tuple_num[2];
	uint64_t offset_table_s = 0;
	uint64_t offset_table_b = 0;
	uint64_t offset_rst = 0;
	size_t bytes_rtn;
	uint64_t rst_count = 0, rst_index = 0;
	char *p_attr_s, *p_attr_b;
	int isEqual;
	char* rst_buf = (char*)malloc(sizeof(char)*TUPLE_SIZE*2*OUTPUT_BUF_SIZE);
	char* buf = (char*)malloc(sizeof(char)*BLOCK_SIZE*BLOCK_NUM);
	for(int i = 0;i < 2;i++){
		fd[i] = open(this->GetTableMeta(table_indexs[i])->data_file_path, O_RDONLY);
		attr_meta[i] = this->GetTableMeta(table_indexs[i])->GetAttributeMeta(attr_indexs[i]);
	}
	fd_output = open("output.txt", O_RDWR | O_CREAT);
	if(fd_output == NULL){printf("error");}
	bytes_rtn = read(fd[0], buf, BLOCK_SIZE*(BLOCK_NUM - 1));
	tuple_num[0] = bytes_rtn / TUPLE_SIZE;

	while(true){
		bytes_rtn = read(fd[1], buf + BLOCK_SIZE*(BLOCK_NUM - 1), BLOCK_SIZE);
		if(bytes_rtn == 0){
			break;
		}
		for(int j = 0; j < bytes_rtn / TUPLE_SIZE; j++){
			for(int k = 0; k < tuple_num[0]; k++){
				p_attr_s = buf + BLOCK_SIZE*(BLOCK_NUM - 1) + offset_table_s + attr_meta[1]->attribute_offset;
				p_attr_b = buf + offset_table_b + attr_meta[0]->attribute_offset;
				isEqual = !(strcmp(p_attr_s, p_attr_b));
				printf("%s--%s:%d\n",p_attr_s,p_attr_b,isEqual);
				if(isEqual == equal_flag){
					memcpy(rst_buf + offset_rst, buf + BLOCK_SIZE*(BLOCK_NUM - 1) + offset_table_s, TUPLE_SIZE);
					offset_rst += TUPLE_SIZE;
					memcpy(rst_buf + offset_rst, buf + offset_table_b, TUPLE_SIZE);
					offset_rst += TUPLE_SIZE;
					rst_count ++;
					rst_index ++;
				}
				offset_table_b += TUPLE_SIZE;
				if(rst_index == OUTPUT_BUF_SIZE){
					rst_index = 0;
					offset_rst = 0;
					write(fd_output, rst_buf, TUPLE_SIZE*2*OUTPUT_BUF_SIZE);
				}
			}
			offset_table_s += TUPLE_SIZE;
			offset_table_b = 0;
		}
		write(fd_output, rst_buf, TUPLE_SIZE*2*rst_index);
		
	}
	printf("%d", rst_count);
	free(buf);
	close(fd_output);
	for(int i = 0;i < 2;i++){
		close(fd[i]);
	}
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
		   char attr_names[16][MAX_ATTR_NAME_LENGTH];
		   int j = 0;
		   int attr_len;
		   while (j < attr_num) {
			   substr = strtok(NULL, seg);;
			   strcpy(attr_names[j], substr);
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
		   ADDR seg_id = index;
		   ADDR start_addr = this->storage_manager->segment_table.seg_table[seg_id]->start_addr;
		   char buf[PAGE_SIZE+1];
		   long long tuple_num = 0;
		   off_t offset = tuple_num * MAX_TUPLE_SIZE;
		   int ret = 0;
		   lseek(this->storage_manager->fd[index],offset,SEEK_SET);
		   while ((ret = read(this->storage_manager->fd[index], buf, PAGE_SIZE)) != 0) {

			   this->storage_manager->Write(index, buf, PAGE_SIZE);
			   tuple_num += 8;
			   offset = tuple_num * MAX_TUPLE_SIZE;
			   lseek(this->storage_manager->fd[index],offset,SEEK_SET);
		   }
//		   this->storage_manager->FlushBlock();
		   Table* new_table = new Table(tb_name, db_id, index, attr_names, types, attr_length, attribute_num, start_addr);
		   long long length = lseek(this->storage_manager->fd[index], 0L, SEEK_END);
		   new_table->table_meta->tuple_num = length / MAX_TUPLE_SIZE;

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

	ADDR virtual_addr = addr >> OFFSET_BIT << OFFSET_BIT;
	int re = this->storage_manager->ReadBuffer(virtual_addr, page, PAGE_SIZE);
	if (re != 0)
	{
		int off = this->storage_manager->GetOffset(addr);
		memcpy(result, page+off, MAX_TUPLE_SIZE);
		return result;
	}
	else {
		return NULL;
	}
}

char* TableManagement::GetTuple(int tb_id, ADDR addr, int tmp) {
//	ADDR start_addr = this->storage_manager->segment_table.seg_table[tb_id]->start_addr;
	char page[PAGE_SIZE];
	char* result;
	result = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
	ADDR virtual_addr = addr >> OFFSET_BIT << OFFSET_BIT;
	int re = this->storage_manager->ReadBuffer(virtual_addr, page, PAGE_SIZE);
	if (re != 0)
	{
		int off = this->storage_manager->GetOffset(addr);
		memcpy(result, page+off, MAX_TUPLE_SIZE);
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
	char tmp[2];
	sprintf(tmp, "%d", col);
	strcat(index_name, tmp);
	strcat(index_name, ".index");
	bpt::bplus_tree database(index_name, true);
	int index = col;
	for (int i = 0; i < table->table_meta->tuple_num; i++) {
		char* tuple;
		tuple = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
		memcpy(tuple, this->GetTuple(tb_id, i), MAX_TUPLE_SIZE);
//		void* part;
//		TypeMalloc(part, table->table_meta->attr_meta[index]->attribute_type, strlen(tuple+table->table_meta->attr_meta[index]->attribute_offset));

//		Encoder::decode(tuple+table->table_meta->attr_meta[index]->attribute_offset, strlen(tuple+table->table_meta->attr_meta[index]->attribute_offset), part, table->table_meta->attr_meta[index]->attribute_type);
//		cout << tuple+table->table_meta->attr_meta[index]->attribute_offset << endl;
		database.insert(tuple+table->table_meta->attr_meta[index]->attribute_offset,table->start_addr+i*MAX_TUPLE_SIZE);
		free(tuple);
	}
	this->tables[tb_id]->table_meta->attr_meta[col]->attribute_index = 1;
	return 0;
}

int TableManagement::SearchIndex(FILE* fout, int tb_id, int col, int condition_num, char* keys[], Operator left_op, Operator right_op) {
	Table* table = this->tables[tb_id];
	char index_name[16];
	sprintf(index_name, "%d", tb_id);
	strcat(index_name, "_");
	char tmp[2];
	sprintf(tmp, "%d", col);
	strcat(index_name, tmp);
	strcat(index_name, ".index");
	bpt::bplus_tree database(index_name);
	if (condition_num == 1) {
		value_t value;
		if (database.search((char*)keys[0], &value) != 0)
			printf("Key %s not found\n", keys[0]);
		else{
			char* tuple;
			tuple = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
			memcpy(tuple, this->GetTuple(tb_id, value, -1), MAX_TUPLE_SIZE);
			for (int j = 0; j < table->table_meta->attribute_num; j++) {
				void* part;
				TypeMalloc(part, table->table_meta->attr_meta[j]->attribute_type, strlen(tuple+table->table_meta->attr_meta[j]->attribute_offset));
//				cout << tuple+table->table_meta->attr_meta[j]->attribute_offset << endl;
				fprintf(fout, "%s|", tuple+table->table_meta->attr_meta[j]->attribute_offset);
			}
			fprintf(fout, "\n");
			free(tuple);
		}
	} else {
		bpt::key_t start(keys[0]);
		value_t values[409600];
		bool next = true;
		while (next) {
			int ret = database.search_range(&start, keys[1], values, 409600, left_op, right_op, &next);
			if (ret < 0)
				break;
			for (int i = 0; i < ret; i++) {
				char* tuple;
				tuple = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
				memcpy(tuple, this->GetTuple(tb_id, values[i], -1), MAX_TUPLE_SIZE);
//				cout << tuple << endl;
				for (int j = 0; j < table->table_meta->attribute_num; j++) {
//					void* part;
//					TypeMalloc(part, table->table_meta->attr_meta[j]->attribute_type, strlen(tuple+table->table_meta->attr_meta[j]->attribute_offset));
	//				cout << tuple+table->table_meta->attr_meta[j]->attribute_offset << endl;
					fprintf(fout, "%s|", tuple+table->table_meta->attr_meta[j]->attribute_offset);
				}
				fprintf(fout, "\n");
				free(tuple);
			}
		}
	}
	fclose(fout);
	return 0;
}

int TableManagement::SearchIndex(int tb_id, int col, int condition_num, char* keys[], Operator left_op, Operator right_op, void* result[]) {
	int num = 0;
	char index_name[16];
	sprintf(index_name, "%d", tb_id);
	strcat(index_name, "_");
	char tmp[2];
	sprintf(tmp, "%d", col);
	strcat(index_name, tmp);
	strcat(index_name, ".index");
	bpt::bplus_tree database(index_name);
	if (condition_num == 1) {
		value_t value;
		if (database.search((char*)keys[0], &value) != 0)
			printf("Key %s not found\n", keys[0]);
		else{
			char* tuple;
			tuple = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
			memcpy(tuple, this->GetTuple(tb_id, value, -1), MAX_TUPLE_SIZE);
			result[0] = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
			memcpy(result[0], tuple, MAX_TUPLE_SIZE);
			free(tuple);
			num = 1;
		}
	} else {
		bpt::key_t start(keys[0]);
		value_t values[409600];
		bool next = true;
		while (next) {
			int ret = database.search_range(&start, keys[1], values, 409600, left_op, right_op, &next);
			if (ret < 0)
				break;
			for (int i = 0; i < ret; i++) {
				num += 1;
				char* tuple;
				tuple = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
				memcpy(tuple, this->GetTuple(tb_id, values[i], -1), MAX_TUPLE_SIZE);
				result[i] = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
				memcpy(result[i], tuple, MAX_TUPLE_SIZE);
				free(tuple);
			}
		}
	}
	return num;
}

int TableManagement::GetCmpCondition(vector<int> cols, vector<Operator>& operators, char* keys[], char* &low, char* &high) {
	if (cols.size() == 1) { // single condition equal
		if (operators[0] == eq) {
			return 1;
		} else if (operators[0] == le || operators[1] == lt) {
			low = "!";
			high = keys[0];
			operators[1] = operators[0];
			operators[0] = gt;
			return 2;
		} else if (operators[0] == ge || operators[0] == gt) {
			low = keys[0];
			operators[1] = lt;
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
	for (int idx = 0; idx < cols.size(); idx++) {
		int i = cols[idx];
//		cout << keys[idx] << " " << tuple+table->table_meta->attr_meta[i]->attribute_offset << endl;
		void* part;
		TypeMalloc(part, table->table_meta->attr_meta[i]->attribute_type, strlen(tuple+table->table_meta->attr_meta[i]->attribute_offset));
		uint32_t la;
		Encoder::decode(tuple+table->table_meta->attr_meta[i]->attribute_offset, strlen(tuple+table->table_meta->attr_meta[i]->attribute_offset), part, table->table_meta->attr_meta[i]->attribute_type, &la);

		void* key;
		TypeMalloc(key, table->table_meta->attr_meta[i]->attribute_type, strlen(keys[idx]));
		Encoder::decode(keys[idx], strlen(keys[idx]), key, table->table_meta->attr_meta[i]->attribute_type, &la);

		op = operators[idx];

//		cout << i << " " << table->table_meta->attr_meta[i]->attribute_type << endl;
		if (table->table_meta->attr_meta[i]->attribute_type == INTEGER || table->table_meta->attr_meta[i]->attribute_type == DATE){
			int64_t k = *(int64_t*)key;
			int64_t getk = *(int64_t*)part;
//			cout << k << " " << getk << endl;
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
			} else if (op == nq && getk == k) {
				return false;
			}
		}  else if (table->table_meta->attr_meta[i]->attribute_type == FLOAT) {
			float k = *(float*)key;
			float getk = *(float*)part;
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
				if (strcmp(keys[idx], (char*)part) != 0) {
					return false;
				}
			} else if (op == ge) {
				if (strcmp((char*)part, keys[idx]) < 0) {
					return false;
				}
			} else if (op == le) {
				if (strcmp((char*)part, keys[idx]) > 0) {
					return false;
				}
			} else if (op == gt) {
				if (strcmp((char*)part, keys[idx]) <= 0) {
					return false;
				}
			} else if (op == lt) {
				if (strcmp((char*)part, keys[idx]) >= 0) {
					return false;
				}
			} else if (op == nq) {
				if (strcmp(keys[idx], (char*)part) == 0) {
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
			fprintf(fout, "%s|", tuple+table->table_meta->attr_meta[j]->attribute_offset);
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
	keys[0] = (char*)malloc(sizeof(char)*2);
	memcpy(keys[0], "!", 2);
	keys[1] = (char*)malloc(sizeof(char)*512);
	memcpy(keys[1], "~", 1);
	for (int i = 0; i < 50; i++)
		strcat(keys[1], "~");
	this->SearchIndex(fout, tb_id, 0, 2, keys, ge, lt);
	return true;
}

bool TableManagement::Select(int tb_id, vector<int> cols, vector<Operator> operators, char* keys[]) {
	Table* table = this->tables[tb_id];
	if (table->table_meta->tuple_num == 0)
		return false;
	char* low = "!";
	char* high;
	high = (char*)malloc(sizeof(high)*200);
	memcpy(high, "~", 1);
	for (int i = 0; i < 50; i++)
		strcat(high, "~");
	int condition_count = this->GetCmpCondition(cols, operators, keys, low, high);
	FILE* fout;
	fout = fopen("result_tableselect", "w");
	if (condition_count == 1 && table->table_meta->attr_meta[cols[0]]->attribute_index != -1) {
		// equal condition select and has index
		this->SearchIndex(fout, tb_id, cols[0], condition_count, keys, operators[0], operators[1]);
	} else if (condition_count == 2 && table->table_meta->attr_meta[cols[0]]->attribute_index != -1)  {
		//range condition select and has index
		char* input[2];
		input[0] = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
		input[1] = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
		memcpy(input[0], low, sizeof(low));
		memcpy(input[1], high, sizeof(high));
		this->SearchIndex(fout, tb_id, cols[0], condition_count, input, operators[0], operators[1]);
	} else {
		// no index or without conditions or non-equal condition or multiple conditions
		for (int i = 0; i < table->table_meta->tuple_num; i++) {
			char* tuple;
			tuple = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
			memcpy(tuple, this->GetTuple(tb_id, i), MAX_TUPLE_SIZE);
			if (this->CheckTuple(tb_id, tuple, cols, operators, keys)) {
				for (int j = 0; j < table->table_meta->attribute_num; j++) {
					fprintf(fout, "%s|", tuple+table->table_meta->attr_meta[j]->attribute_offset);
				}
				fprintf(fout, "\n");
				free(tuple);
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
				fprintf(fout, "%s|", tuple+table->table_meta->attr_meta[j]->attribute_offset);
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
				fprintf(fout, "%s|", tuple+table->table_meta->attr_meta[col]->attribute_offset);
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
				fprintf(fout, "%s|", tuple+table->table_meta->attr_meta[j]->attribute_offset);
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
				fprintf(fout, "%s|", tuple+table->table_meta->attr_meta[col]->attribute_offset);
			}
			fprintf(fout, "\n");
			free(tuple);
		}
	}
	fclose(fout);
	return true;
}

bool TableManagement::NestedLoopJoin(int left_tb_id, int right_tb_id, vector<int> cols1, vector<int> cols2, vector<Operator> operators, bool isReverse) {
	Table* left_table = this->tables[left_tb_id];
	Table* right_table = this->tables[right_tb_id];
	if (left_table->table_meta->tuple_num == 0 || right_table->table_meta->tuple_num == 0)
			return false;
	FILE* fout;
	fout = fopen("result_nestedloopjoin", "w");
	if (!fout)
		return false;
	for (int i = 0; i < right_table->table_meta->tuple_num; i++) {
		char* tuple1;
		tuple1 = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
		memcpy(tuple1, this->GetTuple(right_tb_id, i), MAX_TUPLE_SIZE);
		char* keys[10];
		for (int idx = 0; idx < cols2.size(); idx++) {
			int col1 = cols2[idx];
			keys[idx] = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
			memcpy(keys[idx], tuple1+right_table->table_meta->attr_meta[col1]->attribute_offset, right_table->table_meta->attr_meta[col1]->attribute_length);
		}
		for (int j = 0; j < left_table->table_meta->tuple_num; j++) {
			char* tuple2;
			tuple2 = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
			memcpy(tuple2, this->GetTuple(left_tb_id, j), MAX_TUPLE_SIZE);
			if (this->CheckTuple(left_tb_id, tuple2, cols1, operators, keys)) {
				if (!isReverse) {
					for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
						fprintf(fout, "%s|", tuple2+left_table->table_meta->attr_meta[k]->attribute_offset);
					}
					for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
						fprintf(fout, "%s|", tuple1+right_table->table_meta->attr_meta[k]->attribute_offset);
					}
				} else {
					for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
						fprintf(fout, "%s|", tuple1+right_table->table_meta->attr_meta[k]->attribute_offset);
					}
					for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
						fprintf(fout, "%s|", tuple2+left_table->table_meta->attr_meta[k]->attribute_offset);
					}
				}
				free(tuple2);
				fprintf(fout, "\n");
			}
		}
		free(tuple1);
	}
	fclose(fout);
	return true;
}

bool TableManagement::NestedLoopCartesianProduct(int left_tb_id, int right_tb_id, bool isReverse) {
	Table* left_table = this->tables[left_tb_id];
	Table* right_table = this->tables[right_tb_id];
	if (left_table->table_meta->tuple_num == 0 || right_table->table_meta->tuple_num == 0)
			return false;
	FILE* fout;
	fout = fopen("result_nlcp", "w");
	if (!fout)
		return false;
	for (int i = 0; i < left_table->table_meta->tuple_num; i++) {
		char* tuple1;
		tuple1 = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
		memcpy(tuple1, this->GetTuple(left_tb_id, i), MAX_TUPLE_SIZE);
		// decode

		for (int j = 0; j < right_table->table_meta->tuple_num; j++) {
			char* tuple2;
			tuple2 = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
			memcpy(tuple2, this->GetTuple(right_tb_id, j), MAX_TUPLE_SIZE);
			if (!isReverse) {
				for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
					fprintf(fout, "%s|", tuple1+left_table->table_meta->attr_meta[k]->attribute_offset);
				}
				for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
					fprintf(fout, "%s|", tuple2+right_table->table_meta->attr_meta[k]->attribute_offset);
				}
			} else {
				for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
					fprintf(fout, "%s|", tuple2+right_table->table_meta->attr_meta[k]->attribute_offset);
				}
				for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
					fprintf(fout, "%s|", tuple1+left_table->table_meta->attr_meta[k]->attribute_offset);
				}
			}
			free(tuple2);
			fprintf(fout, "\n");
		}
		free(tuple1);
	}
	fclose(fout);
	return true;
}

int TableManagement::SingleIndexJoin(int right_tb_id, int col2, char* keys[], Operator op, void* result[]) {

	if (op == eq) {
		return this->SearchIndex(right_tb_id, col2, 1, keys, eq, eq, result);
	} else if (op == ge || op == gt) {
		Operator op1;
		keys[1] = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
		memcpy(keys[1], keys[0], sizeof(keys[0]));
		memcpy(keys[0], "!", sizeof("!"));
		if (op == ge) {
			op1 = le;
		} else {
			op1 = lt;
		}
		return this->SearchIndex(right_tb_id, col2, 2, keys, ge, op1, result);
	} else if (op == le || op == lt) {
		Operator op2;
		if (op == le) {
			op2 = ge;
		} else {
			op2 = gt;
		}
		keys[1] = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
		memcpy(keys[1], "~~~~~~~~~~~~~~~~~~~~~~~", sizeof("~~~~~~~~~~~~~~~~~~~~~~~"));
		return this->SearchIndex(right_tb_id, col2, 2, keys, op2, le, result);
	} else {
		return -1;
	}
	return -1;
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
			char* keys[2];
			keys[0] = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
			memcpy(keys[0], tuple1+left_table->table_meta->attr_meta[col1]->attribute_offset, left_table->table_meta->attr_meta[col1]->attribute_length);
			if (operators[0] == eq) {
				void* result[4096];
				this->SearchIndex(right_tb_id, col2, 1, keys, operators[0], operators[0], result);
				char* tuple2;
				tuple2 = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);

				if (result[0] != NULL)
					memcpy(tuple2, result[0], MAX_TUPLE_SIZE);
				if (tuple2 != NULL) {
					if (!isReverse) {
						for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
							fprintf(fout, "%s|", tuple1+left_table->table_meta->attr_meta[k]->attribute_offset);
						}
						for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
							fprintf(fout, "%s|", tuple2+right_table->table_meta->attr_meta[k]->attribute_offset);
						}
						fprintf(fout, "\n");
					} else {
						for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
							fprintf(fout, "%s|", tuple2+right_table->table_meta->attr_meta[k]->attribute_offset);
						}
						for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
							fprintf(fout, "%s|", tuple1+left_table->table_meta->attr_meta[k]->attribute_offset);
						}
						fprintf(fout, "\n");
					}
				}
			} else if (operators[0] == ge || operators[0] == gt) {
				keys[1] = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
				memcpy(keys[1], keys[0], sizeof(keys[0]));
				memcpy(keys[0], "!", sizeof("!"));
				void* result[409600];
				Operator op;
				if (operators[0] == ge) {
					op = le;
				} else {
					op = lt;
				}
				int num = this->SearchIndex(right_tb_id, col2, 2, keys, ge, op, result);
				for (int j = 0; j < num; j++) {
					if (result[j] != NULL) {
						char* tuple2;
						tuple2 = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
						memcpy(tuple2, result[j], MAX_TUPLE_SIZE);
						if (!isReverse) {
							for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
								fprintf(fout, "%s|", tuple1+left_table->table_meta->attr_meta[k]->attribute_offset);
							}
							for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
								fprintf(fout, "%s|", tuple2+right_table->table_meta->attr_meta[k]->attribute_offset);
							}
							fprintf(fout, "\n");
						} else {
							for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
								fprintf(fout, "%s|", tuple2+right_table->table_meta->attr_meta[k]->attribute_offset);
							}
							for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
								fprintf(fout, "%s|", tuple1+left_table->table_meta->attr_meta[k]->attribute_offset);
							}
							fprintf(fout, "\n");
						}
						free(tuple2);
					}
				}

			} else if (operators[0] == le || operators[0] == lt) {
				Operator op;
				if (operators[0] == lt) {
					op = gt;
				} else {
					op = ge;
				}
				keys[1] = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
				memcpy(keys[1], "~~~~~~~~~~~~~~~~~~~~~~~", sizeof("~~~~~~~~~~~~~~~~~~~~~~~"));
				void* result[409600];
				int num = this->SearchIndex(right_tb_id, col2, 2, keys, op, le, result);
				for (int j = 0; j < num; j++) {
					if (result[j] != NULL) {
						char* tuple2;
						tuple2 = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
						memcpy(tuple2, result[j], MAX_TUPLE_SIZE);
						if (!isReverse) {
							for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
								fprintf(fout, "%s|", tuple1+left_table->table_meta->attr_meta[k]->attribute_offset);
							}
							for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
								fprintf(fout, "%s|", tuple2+right_table->table_meta->attr_meta[k]->attribute_offset);
							}
							fprintf(fout, "\n");
						} else {
							for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
								fprintf(fout, "%s|", tuple2+right_table->table_meta->attr_meta[k]->attribute_offset);
							}
							for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
								fprintf(fout, "%s|", tuple1+left_table->table_meta->attr_meta[k]->attribute_offset);
							}
							fprintf(fout, "\n");
						}
						free(tuple2);
					}
				}
			} else {
				// non-equal
				operators[0] = lt;
//				operators.push_back(gt);
				operators[1] = gt;
				void* result1[4096];
				int num1 = this->SingleIndexJoin(right_tb_id, cols2[0], keys, operators[0], result1);
				for (int j = 0; j < num1; j++) {
					char* tuple2;
					tuple2 = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
					memcpy(tuple2, result1[j], MAX_TUPLE_SIZE);
					if (!isReverse) {
						for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
							fprintf(fout, "%s|", tuple1+left_table->table_meta->attr_meta[k]->attribute_offset);
						}
						for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
							fprintf(fout, "%s|", tuple2+right_table->table_meta->attr_meta[k]->attribute_offset);
						}
						fprintf(fout, "\n");
					} else {
						for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
							fprintf(fout, "%s|", tuple2+right_table->table_meta->attr_meta[k]->attribute_offset);
						}
						for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
							fprintf(fout, "%s|", tuple1+left_table->table_meta->attr_meta[k]->attribute_offset);
						}
						fprintf(fout, "\n");
					}
					free(tuple2);
				}
				keys[0] = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
				memcpy(keys[0], tuple1+left_table->table_meta->attr_meta[col1]->attribute_offset, left_table->table_meta->attr_meta[col1]->attribute_length);
				void* result2[4096];
				int num2 = this->SingleIndexJoin(right_tb_id, cols2[0], keys, operators[1], result2);
				for (int j = 0; j < num2; j++) {
					char* tuple2;
					tuple2 = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
					memcpy(tuple2, result2[j], MAX_TUPLE_SIZE);
					if (!isReverse) {
						for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
							fprintf(fout, "%s|", tuple1+left_table->table_meta->attr_meta[k]->attribute_offset);
						}
						for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
							fprintf(fout, "%s|", tuple2+right_table->table_meta->attr_meta[k]->attribute_offset);
						}
						fprintf(fout, "\n");
					} else {
						for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
							fprintf(fout, "%s|", tuple2+right_table->table_meta->attr_meta[k]->attribute_offset);
						}
						for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
							fprintf(fout, "%s|", tuple1+left_table->table_meta->attr_meta[k]->attribute_offset);
						}
						fprintf(fout, "\n");
					}
					free(tuple2);
				}
				operators[0] = nq;
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
			char* keys[1];
			keys[0] = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
			memcpy(keys[0], tuple1+left_table->table_meta->attr_meta[col1]->attribute_offset, MAX_TUPLE_SIZE);
			if (operators[0] != nq) {
				void* tuples1[4096]; // result of condition 1
				int num = this->SingleIndexJoin(right_tb_id, cols2[0], keys, operators[0], tuples1);
				vector<int> cols;
				vector<Operator> ops;
				for (int idx = 0; idx < cols1.size() - 1; idx++) {
					cols.insert((vector<int>::iterator)cols.begin()+idx, cols2[idx+1]);
					Operator op1;
					if (operators[idx+1] == ge) {
						op1 = le;
					} else if (operators[idx+1] == gt) {
						op1 = lt;
					} else if (operators[idx+1] == le) {
						op1 = ge;
					} else if (operators[idx+1] == lt) {
						op1 = gt;
					} else if (operators[idx+1] == nq) {
						op1 = lt;
					}
					ops.insert((vector<Operator>::iterator)ops.begin()+idx, op1);
					if (operators[idx+1] == nq) {
						op1 = gt;
						ops.insert((vector<Operator>::iterator)ops.begin()+idx+1, op1);
						cols.insert((vector<int>::iterator)cols.begin()+idx+1, cols2[idx+1]);
					}
				}
				char* other_keys[4];
				for (int idx = 1; idx < cols1.size(); idx++) {
					other_keys[idx-1] = (char*)malloc(sizeof(char)*MAX_TUPLE_SIZE);
					memcpy(other_keys[idx-1], tuple1+left_table->table_meta->attr_meta[cols1[idx]]->attribute_offset, MAX_TUPLE_SIZE);
				}
				for (int j = 0; j < num; j++) {
					if (this->CheckTuple(right_tb_id, (char*)tuples1[j], cols, ops, other_keys)) {
						// fit other conditions
						if (!isReverse) {
							for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
								fprintf(fout, "%s|", tuple1+left_table->table_meta->attr_meta[k]->attribute_offset);
							}
							for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
								fprintf(fout, "%s|", tuples1[j]+right_table->table_meta->attr_meta[k]->attribute_offset);
							}
							fprintf(fout, "\n");
						} else {
							for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
								fprintf(fout, "%s|", tuples1[j]+right_table->table_meta->attr_meta[k]->attribute_offset);
							}
							for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
								fprintf(fout, "%s|", tuple1+left_table->table_meta->attr_meta[k]->attribute_offset);
							}
							fprintf(fout, "\n");
						}
					}
				}
			}
		}

	}
	return true;
}

int TableManagement::IndexCartesianProduct(int left_tb_id, int right_tb_id, bool isReverse) {
	cout << "ok" << endl;
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
		memcpy(tuple1, this->GetTuple(left_tb_id, 1), MAX_TUPLE_SIZE);

		char* keys[2];
		keys[0] = (char*)malloc(sizeof(char)*5);
		keys[0] = "!";
		keys[1] = (char*)malloc(sizeof(char)*10);
		keys[1] = "~~~~~~~~";
		void* result1[4096000];
		int num = this->SearchIndex(right_tb_id, 0, 2, keys, ge, le, result1);
		for (int j = 0; j < num; j++) {
			for (int k = 0; k < left_table->table_meta->attribute_num; k++) {
				fprintf(fout, "%s|", tuple1+left_table->table_meta->attr_meta[k]->attribute_offset);
			}
			for (int k = 0; k < right_table->table_meta->attribute_num; k++) {
				fprintf(fout, "%s|", result1[j]+right_table->table_meta->attr_meta[k]->attribute_offset);
			}
			fprintf(fout, "\n");
		}
	}
	return 0;
}

Table::Table(char* name, int db_id, int index, char attr_names[][MAX_ATTR_NAME_LENGTH], AttrType *types, int *attr_length, int attribute_num, ADDR start_addr) {
	this->db_id = db_id;
	this->index = index;
	this->start_addr = start_addr;
	TableMeta* new_table_meta = new TableMeta();
	memcpy(new_table_meta->table_name, name, MAX_TABLE_NAME_LENGTH);
	strcpy(new_table_meta->data_file_path, data_dir);
	strcat(new_table_meta->data_file_path, name);
	strcat(new_table_meta->data_file_path, ".data");
	new_table_meta->db_id = db_id;
	new_table_meta->attribute_num = attribute_num;
	int off = 0;
	for (int i = 0; i < attribute_num; i++) {
		AttributeMeta* new_attr_meta = new AttributeMeta();
		new_attr_meta->attribute_index = -1;
		strcpy(new_attr_meta->attribute_name, attr_names[i]);
		new_attr_meta->attribute_type = types[i];
		new_attr_meta->attribute_length = attr_length[i];
		new_attr_meta->attribute_offset = off;
		off += attr_length[i];
		new_table_meta->attr_meta.push_back(new_attr_meta);
	}
	this->table_meta = new_table_meta;
}

void Table::dump(){
	printf("table info:\n");
	fflush(stdout);
	this->table_meta->dump();
}
void TableManagement::dump(){
	printf("table management info:\n");
	fflush(stdout);	
	for(vector<Table*>::iterator iter = (this->tables).begin(); iter != (this->tables).end(); iter ++){
		(*iter)->dump();
	}
}


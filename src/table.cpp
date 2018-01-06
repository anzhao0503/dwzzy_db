#include "../include/table.h"
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

//int TableManagement::CartesianProduct(int* table_indexs){
//	TableMeta* table_meta[2];
//	int fd[2] = {0,0};
//	int fd_output;
//	int tuple_num[2];
//	uint64_t offset_table_s = 0;
//	uint64_t offset_table_b = 0;
//	uint64_t offset_rst = 0;
//	size_t bytes_rtn;
//	uint64_t rst_count = 0, rst_index = 0;
//	char* rst_buf = (char*)malloc(sizeof(char)*TUPLE_SIZE*2*OUTPUT_BUF_SIZE);
//	char* buf = (char*)malloc(sizeof(char)*BLOCK_SIZE*BLOCK_NUM);
//	for(int i = 0;i < 2;i++){
//		fd[i] = open(this->GetTableMeta(table_indexs[i])->data_file_path, O_RDONLY);
//	}
//	fd_output = open("output.txt", O_RDWR | O_CREAT);
//	if(fd_output == NULL){printf("error");}
//	bytes_rtn = read(fd[0], buf, BLOCK_SIZE*(BLOCK_NUM - 1));
//	tuple_num[0] = bytes_rtn / TUPLE_SIZE;
//	while(true){
//		bytes_rtn = read(fd[1], buf + BLOCK_SIZE*(BLOCK_NUM - 1), BLOCK_SIZE);
//		if(bytes_rtn == 0){
//			break;
//		}
//		for(int j = 0; j < bytes_rtn / TUPLE_SIZE; j++){
//			for(int k = 0; k < tuple_num[0]; k++){
//				memcpy(rst_buf + offset_rst, buf + BLOCK_SIZE*(BLOCK_NUM - 1) + offset_table_s, TUPLE_SIZE);
//				offset_rst += TUPLE_SIZE;
//				memcpy(rst_buf + offset_rst, buf + offset_table_b, TUPLE_SIZE);
//				offset_rst += TUPLE_SIZE;
//				offset_table_b += TUPLE_SIZE;
//				rst_count ++;
//				rst_index ++;
//				if(rst_index == OUTPUT_BUF_SIZE){
//					rst_index = 0;
//					offset_rst = 0;
//					write(fd_output, rst_buf, TUPLE_SIZE*2*OUTPUT_BUF_SIZE);
//				}
//			}
//			offset_table_s += TUPLE_SIZE;
//			offset_table_b += 0;
//		}
//		write(fd_output, rst_buf, TUPLE_SIZE*2*rst_index);
//
//	}
//	free(buf);
//	close(fd_output);
//	for(int i = 0;i < 2;i++){
//		close(fd[i]);
//	}
//}
//
//int TableManagement::Join(int* table_indexs, int* attr_indexs, bool equal_flag){
//	TableMeta* table_meta[2];
//	AttributeMeta* attr_meta[2];
//	int fd[2] = {0,0};
//	int fd_output;
//	int tuple_num[2];
//	uint64_t offset_table_s = 0;
//	uint64_t offset_table_b = 0;
//	uint64_t offset_rst = 0;
//	size_t bytes_rtn;
//	uint64_t rst_count = 0, rst_index = 0;
//	char *p_attr_s, *p_attr_b;
//	int isEqual;
//	char* rst_buf = (char*)malloc(sizeof(char)*TUPLE_SIZE*2*OUTPUT_BUF_SIZE);
//	char* buf = (char*)malloc(sizeof(char)*BLOCK_SIZE*BLOCK_NUM);
//	for(int i = 0;i < 2;i++){
//		fd[i] = open(this->GetTableMeta(table_indexs[i])->data_file_path, O_RDONLY);
//		attr_meta[i] = this->GetTableMeta(table_indexs[i])->GetAttributeMeta(attr_indexs[i]);
//	}
//	fd_output = open("output.txt", O_RDWR | O_CREAT);
//	if(fd_output == NULL){printf("error");}
//	bytes_rtn = read(fd[0], buf, BLOCK_SIZE*(BLOCK_NUM - 1));
//	tuple_num[0] = bytes_rtn / TUPLE_SIZE;
//
//	while(true){
//		bytes_rtn = read(fd[1], buf + BLOCK_SIZE*(BLOCK_NUM - 1), BLOCK_SIZE);
//		if(bytes_rtn == 0){
//			break;
//		}
//		for(int j = 0; j < bytes_rtn / TUPLE_SIZE; j++){
//			for(int k = 0; k < tuple_num[0]; k++){
//				p_attr_s = buf + BLOCK_SIZE*(BLOCK_NUM - 1) + offset_table_s + attr_meta[1]->attribute_offset;
//				p_attr_b = buf + offset_table_b + attr_meta[0]->attribute_offset;
//				isEqual = !(strcmp(p_attr_s, p_attr_b));
//				printf("%s--%s:%d\n",p_attr_s,p_attr_b,isEqual);
//				if(isEqual == equal_flag){
//					memcpy(rst_buf + offset_rst, buf + BLOCK_SIZE*(BLOCK_NUM - 1) + offset_table_s, TUPLE_SIZE);
//					offset_rst += TUPLE_SIZE;
//					memcpy(rst_buf + offset_rst, buf + offset_table_b, TUPLE_SIZE);
//					offset_rst += TUPLE_SIZE;
//					rst_count ++;
//					rst_index ++;
//				}
//				offset_table_b += TUPLE_SIZE;
//				if(rst_index == OUTPUT_BUF_SIZE){
//					rst_index = 0;
//					offset_rst = 0;
//					write(fd_output, rst_buf, TUPLE_SIZE*2*OUTPUT_BUF_SIZE);
//				}
//			}
//			offset_table_s += TUPLE_SIZE;
//			offset_table_b = 0;
//		}
//		write(fd_output, rst_buf, TUPLE_SIZE*2*rst_index);
//
//	}
//	printf("%d", rst_count);
//	free(buf);
//	close(fd_output);
//	for(int i = 0;i < 2;i++){
//		close(fd[i]);
//	}
//}

char* TableManagement::GetTuple(int tb_id, int index, int tuple_size) {
	char page[PAGE_SIZE];
	char* result;
	result = (char*)malloc(sizeof(char)*tuple_size);
	ADDR addr = this->tables[tb_id]->start_addr+index*tuple_size;
	ADDR virtual_addr = addr >> OFFSET_BIT << OFFSET_BIT;
	int re = this->storage_manager->ReadBuffer(virtual_addr, page, PAGE_SIZE);
	if (re != 0)
	{
		ADDR off = this->storage_manager->GetOffset(addr);
		ADDR page_id = this->storage_manager->GetPageId(virtual_addr);
		int idx = off / MAX_TUPLE_SIZE;
//		if (this->storage_manager->segment_table.seg_table[tb_id]->page_table[page_id]->TestTuple(idx) == 1) {
			// tuple not free
			memcpy(result, page+off, tuple_size);
//		}
//		memcpy(result, page+off, tuple_size);
		return result;
	}
	else {
		return NULL;
	}
}

char* TableManagement::GetTuple(int tb_id, ADDR addr, int tuple_size, int tmp) {
//	ADDR start_addr = this->storage_manager->segment_table.seg_table[tb_id]->start_addr;
	char page[PAGE_SIZE];
	char* result;
	result = (char*)malloc(sizeof(char)*tuple_size);
	ADDR virtual_addr = addr >> OFFSET_BIT << OFFSET_BIT;
	int re = this->storage_manager->ReadBuffer(virtual_addr, page, PAGE_SIZE);
	if (re != 0)
	{
		ADDR off = this->storage_manager->GetOffset(addr);
		ADDR page_id = this->storage_manager->GetPageId(virtual_addr);
		int idx = off / MAX_TUPLE_SIZE;
//		if (this->storage_manager->segment_table.seg_table[tb_id]->page_table[page_id]->TestTuple(idx) == 1) {
			// tuple not free
			memcpy(result, page+off, tuple_size);
//		}
		return result;
	}
	else {
		return NULL;
	}
}

char* TableManagement::GetPage(int tb_id, int index, ADDR &add) {
	char* result;
	result = (char*)malloc(sizeof(char)*PAGE_SIZE);
	ADDR addr = this->tables[tb_id]->start_addr+index*MAX_TUPLE_SIZE;
	ADDR virtual_addr = addr >> OFFSET_BIT << OFFSET_BIT;
	int re = this->storage_manager->ReadBuffer(virtual_addr, result, PAGE_SIZE);
	add = virtual_addr;
	if (re != 0)
	{
		return result;
	}
	else {
		return NULL;
	}
}

int TableManagement::GetTableId(char* t_name) {
	std::string tb_name = t_name;
	map<string, int>::iterator iter;
	iter = this->table_map.find(tb_name);
	if (iter == this->table_map.end()) {
		cout << "ERROR: Table name " << tb_name << " doesn't exist" << endl;
		return -1;
	}
	return iter->second;
}

string TableManagement::GetTableName(int tb_id) {
	map<int, string>::iterator iter;
	iter = this->idx_name_map.find(tb_id);
	if (iter == this->idx_name_map.end()) {
		cout << "ERROR: Table id " << tb_id << " doesn't exist" << endl;
		return NULL;
	}
	return iter->second;
}

int TableManagement::InitTable(char* t_name, int db_id) {
	std::string tb_name;
	std::string tmp_str = t_name;
	string::size_type pos;
	string pattern = ".";
	tmp_str+=pattern;
	int size = tmp_str.size();
	for (int i = 0; i < size; i++) {
		pos = tmp_str.find(pattern, i);
		if (pos < size) {
			tb_name = tmp_str.substr(i, pos-i);
			break;
		}
	}
	if (this->table_map.count(tb_name) != 0) {
		cout << "ERROR: Table name exists" << endl;
		return -1;
	}
	int index = this->table_count;
	this->table_count += 1;
	this->table_map.insert(pair<string, int>(tb_name, index));
	FILE* fp;
	if ((fp = fopen("benchmark_format.txt", "r")) == NULL) {
		cout<<"error find format"<<endl;
		return -1;
	}
	TYPE *types;
	int *attr_length;
	int attribute_num;
	int i = 0;
	char buffer[256];
	while(i<8) {
	   fgets(buffer, sizeof(buffer), fp);
	   char seg[] = " ";
	   char* substr;
	   substr = strtok(buffer, seg);
	   if (strcmp(substr, t_name) == 0) {
		   // get table meta data
		   substr = strtok(NULL, seg);
		   int attr_num = atoi(substr);
		   attribute_num = attr_num;
		   attr_length = (int*)malloc(sizeof(int)*attribute_num);
		   types = (TYPE*)malloc(sizeof(TYPE)*attribute_num);
		   char attr_names[16][MAX_ATTR_NAME_LENGTH];
		   int j = 0;
		   int attr_len;
		   while (j < attr_num) {
			   substr = strtok(NULL, seg);
			   strcpy(attr_names[j], substr);
			   substr = strtok(NULL, seg);
			   TYPE type;
			   if (strcmp(substr, "INTEGER") == 0) {
				   type = I;
				   attr_len = 24;
			   } else if (strcmp(substr, "FLOAT") == 0) {
				   type = F;
				   attr_len = 24;
			   } else if (strcmp(substr, "CHAR") == 0) {
				   type = C;
			   } else if (strcmp(substr, "VARCHAR") == 0) {
				   type = V;
			   } else if (strcmp(substr, "DATE") == 0) {
				   type = D;
				   attr_len = 12;
			   }
			   types[j] = type;
			   substr = strtok(NULL, seg);
			   if (type == C || type == V) {
				   attr_len = atoi(substr) + 1;
			   }
			   attr_length[j] = attr_len;
			   j++;
		   }
		   // load data to disk and create Table
		   ADDR seg_id = index;
		   ADDR start_addr = this->storage_manager->segment_table.seg_table[seg_id]->start_addr;
		   char buf[MAX_TUPLE_SIZE+1];
		   long long tuple_num = 0;
		   off_t offset = tuple_num * MAX_TUPLE_SIZE;
		   int ret = 0;
		   lseek(this->storage_manager->fd[index],offset,SEEK_SET);
		   while ((ret = read(this->storage_manager->fd[index], buf, MAX_TUPLE_SIZE)) != 0) {
			   this->storage_manager->Write(index, buf, MAX_TUPLE_SIZE);
			   tuple_num += 1;
			   offset = tuple_num * MAX_TUPLE_SIZE;
			   lseek(this->storage_manager->fd[index],offset,SEEK_SET);
		   }
//		   cout << "tuple " << tuple_num << endl;
//		   this->storage_manager->FlushBlock();
		   Table* new_table = new Table(t_name, db_id, index, MAX_TUPLE_SIZE, attr_names, types, attr_length, attribute_num, start_addr);
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

int TableManagement::CreateTable(int db_id, char* t_name, int tuple_size, char attr_names[][MAX_ATTR_NAME_LENGTH], TYPE *types, int *attr_length, int attribute_num) {
	std::string tb_name = t_name;
	map<string, int>::iterator it;
	it = this->table_map.find(tb_name);

	if (it != this->table_map.end()) {
		cout << "ex " << it->first << " " << it->second << endl;
		cout << "ERROR: Table name exists" << endl;
		return -1;
	}
	int index = this->table_count;
	this->table_count += 1;
	this->table_map.insert(pair<string, int>(tb_name, index));
	this->idx_name_map.insert(pair<int, string>(index, tb_name));
	ADDR seg_id = index;
	this->storage_manager->segment_table.Add_Seg();
    ADDR start_addr = this->storage_manager->segment_table.seg_table[seg_id]->start_addr;
    this->storage_manager->fd[index] = open(t_name,O_CREAT|O_EXCL|O_RDWR,0777);
	Table* new_table = new Table(t_name, db_id, index, tuple_size, attr_names, types, attr_length, attribute_num, start_addr);
	new_table->table_meta->tuple_num = 0;
	this->tables.insert((vector<Table*>::iterator)this->tables.begin()+index, new_table);
	cout << "create table ok" << endl;
	return index;
}

int TableManagement::CreateTable(int db_id, char* t_name, int tuple_size, char attr_names[][MAX_ATTR_NAME_LENGTH], TYPE *types, int *attr_length, int *attribute_offset, int attribute_num) {
	std::string tb_name = t_name;
	map<string, int>::iterator it;
	it = this->table_map.find(tb_name);

	if (it != this->table_map.end()) {
		cout << "ex " << it->first << " " << it->second << endl;
		cout << "ERROR: Table name exists" << endl;
		return -1;
	}
	int index = this->table_count;
	this->table_count += 1;
	this->table_map.insert(pair<string, int>(tb_name, index));
	this->idx_name_map.insert(pair<int, string>(index, tb_name));

	ADDR seg_id = index;
	this->storage_manager->segment_table.Add_Seg();
    ADDR start_addr = this->storage_manager->segment_table.seg_table[seg_id]->start_addr;
    this->storage_manager->fd[index] = open(t_name,O_CREAT|O_EXCL|O_RDWR,0777);
	Table* new_table = new Table(t_name, db_id, index, tuple_size, attr_names, types, attr_length, attribute_offset, attribute_num, start_addr);
	new_table->table_meta->tuple_num = 0;
	this->tables.insert((vector<Table*>::iterator)this->tables.begin()+index, new_table);
	return index;
}

bool TableManagement::DropTable(char* t_name) {
	int tb_id = this->GetTableId(t_name);
	Table* table = this->tables[tb_id];
	if (table->exist == false) {
		cout << "table " << tb_id << " does not exist" << endl;
		return false;
	}
	int tuple_size = table->table_meta->tuple_size;
	if (table->table_meta->tuple_num == 0)
		return false;
	for (int i = 0; i < table->table_meta->tuple_num; i+=8) {
		char* page;
		page = (char*)malloc(sizeof(char)*PAGE_SIZE);
		ADDR virtual_addr;
		memcpy(page, this->GetPage(tb_id, i, virtual_addr), PAGE_SIZE);
		ADDR page_id = this->storage_manager->GetPageId(virtual_addr);
		int flag = 0;
		for (int j = 0; j < PAGE_SIZE / tuple_size; j++) {
			//this->storage_manager->segment_table.seg_table[tb_id]->page_table[page_id]->FreeTuple(j);
			table->table_meta->real_tuple_num-=1;
		}
	}
	string tb_name = t_name;
	this->table_map.erase(tb_name);
	table->exist = false;
	cout << "drop table ok" << endl;
	return true;
}

bool TableManagement::Insert(int tb_id, vector<int> cols, char* values[]) {
	Table* table = this->tables[tb_id];
	if (table->exist == false) {
		cout << "table " << tb_id << " does not exist" << endl;
		return false;
	}
	int tuple_size = table->table_meta->tuple_size;
	if (cols.size() != 0 && cols.size() < table->table_meta->attribute_num) {
		cout << "Not enough columns" << endl;
		return false;
	}
	char* tuple = (char*)malloc(sizeof(char)*table->table_meta->tuple_size);
	int offset = 0;
	int len = 0;

	for (int i = 0; i < table->table_meta->attribute_num; i++) {
		TYPE type = table->table_meta->attr_meta[i]->attribute_type;
		offset = table->table_meta->attr_meta[i]->attribute_offset;
		len = table->table_meta->attr_meta[i]->attribute_length;
//		cout << type << endl;
		if (type == I) {
			uint32_t l;
			char v[MAX_INT_ASCII_LENGTH] = "";
			int value = atoi(values[i]);
			char tmp[sizeof(values[i])];
			sprintf(tmp, "%d", value);
			if (strcmp(tmp, values[i]) != 0) {
				cout << "Not the correct type in column" << i << endl;
				return -1;
			}
//			Encoder::encode((void*)&value, v, &l, I);
//			cout << value << " " << tmp << endl;
//			cout << tmp << endl;
			memcpy(tuple+offset, tmp, len);

		} else if (type == F) {
			uint32_t l;
			char v[MAX_FLOAT_ASCII_LENGTH];
			float value = atol(values[i]);
			Encoder::encode((void*)&value, v, &l, F);
			memcpy(tuple+offset, v, len);

		} else if (type == V || type == C) {
//			char v[strlen(values[i])];
//			Encoder::encode((void*)&values[i], v, &l, V, strlen(values[i]));
//			cout << values[i] << endl;
			memcpy(tuple+offset, values[i], len);

		} else if (type == D) {
			uint32_t l;
			char v[MAX_DATE_ASCII_LENGTH];
			Encoder::encode((void*)&values[i], v, &l, D);
			memcpy(tuple+offset, v, len);
		}
		if (table->table_meta->attr_meta[i]->attribute_index == 1) {
			ADDR addr = this->storage_manager->segment_table.seg_table[tb_id]->addr_space->GetCurrentAddr();
			this->InsertIndex(tb_id, i, tuple+offset, addr);
		}
	}
	this->tables[tb_id]->table_meta->tuple_num++;
	this->storage_manager->Write(tb_id, tuple, tuple_size);
	cout << "insert ok" << endl;
	return true;
}

bool TableManagement::Update(int tb_id, vector<int> up_cols, char* up_keys[], vector<int> cols, vector<OP> operators, char* keys[]) {
	Table* table = this->tables[tb_id];
	if (table->exist == false) {
		cout << "table " << tb_id << " does not exist" << endl;
		return false;
	}
	int tuple_size = table->table_meta->tuple_size;
	if (table->table_meta->tuple_num == 0)
		return false;
	char* low = "!";
	char* high;
	high = (char*)malloc(sizeof(high)*200);
	memcpy(high, "~", 1);
	for (int i = 0; i < 50; i++)
		strcat(high, "~");
	// no index or without conditions or non-equal condition or multiple conditions
	for (int i = 0; i < table->table_meta->tuple_num; i+=8) {
		char* page;
		page = (char*)malloc(sizeof(char)*PAGE_SIZE);
		char* res_page;
		res_page = (char*)malloc(sizeof(char)*PAGE_SIZE);
		ADDR virtual_addr;
		memcpy(page, this->GetPage(tb_id, i, virtual_addr), PAGE_SIZE);
		memcpy(res_page, page, PAGE_SIZE);
		int flag = 0;
		for (int k = 0; k <  PAGE_SIZE / tuple_size; k++) {
			char* tuple;
			tuple = (char*)malloc(sizeof(char)*tuple_size);
			memcpy(tuple, page+k*tuple_size, tuple_size);
			if (this->CheckTuple(tb_id, tuple, cols, operators, keys)) {
				flag = 1;
				char* res_tuple;
				res_tuple = (char*)malloc(sizeof(char)*tuple_size);
				memcpy(res_tuple, tuple, tuple_size);
				for (int j = 0; j < up_cols.size(); j++) {
					memcpy(res_tuple+table->table_meta->attr_meta[up_cols[j]]->attribute_offset, up_keys[j], table->table_meta->attr_meta[up_cols[j]]->attribute_length);
					if (table->table_meta->attr_meta[j]->attribute_index == 1) {
						ADDR addr = virtual_addr + k * tuple_size;
						this->UpdateIndex(tb_id, j, res_tuple+table->table_meta->attr_meta[up_cols[j]]->attribute_offset, addr);
					}
				}
				memcpy(res_page+k*tuple_size, res_tuple, tuple_size);
				free(tuple);
			}
		}
		if (flag == 1) {
			this->storage_manager->WriteBuffer(virtual_addr, res_page, PAGE_SIZE);
		}
	}

	return true;
}

bool TableManagement::Delete(int tb_id, vector<int> cols, vector<OP> operators, char* keys[]) {
	Table* table = this->tables[tb_id];
	if (table->exist == false) {
		cout << "table " << tb_id << " does not exist" << endl;
		return false;
	}
	int tuple_size = table->table_meta->tuple_size;
	if (table->table_meta->tuple_num == 0)
		return false;
	char* low = "!";
	char* high;
	high = (char*)malloc(sizeof(high)*200);
	memcpy(high, "~", 1);
	for (int i = 0; i < 50; i++)
		strcat(high, "~");

	for (int i = 0; i < table->table_meta->tuple_num; i+=8) {
		char* page;
		page = (char*)malloc(sizeof(char)*PAGE_SIZE);
		ADDR virtual_addr;
		memcpy(page, this->GetPage(tb_id, i, virtual_addr), PAGE_SIZE);
		ADDR page_id = this->storage_manager->GetPageId(virtual_addr);
		int flag = 0;
		for (int j = 0; (j < PAGE_SIZE / tuple_size && i + j <  table->table_meta->tuple_num); j++) {
			char* tuple;
			tuple = (char*)malloc(sizeof(char)*tuple_size);
			memcpy(tuple, page+j*tuple_size, tuple_size);
			if (this->CheckTuple(tb_id, tuple, cols, operators, keys)) {
				//this->storage_manager->segment_table.seg_table[tb_id]->page_table[page_id]->FreeTuple(j);
				table->table_meta->real_tuple_num-=1;
				for (int k = 0; k < table->table_meta->attribute_num; k++) {
					if (table->table_meta->attr_meta[k]->attribute_index == 1) {
						this->RemoveIndex(tb_id, k, tuple+table->table_meta->attr_meta[k]->attribute_offset);
					}
				}
			}
			free(tuple);
		}
	}
	cout << "delete ok" << endl;
	return true;
}

int TableManagement::CreateIndex(int tb_id, int col) {
	Table* table = this->tables[tb_id];
	if (table->exist == false) {
		cout << "table " << tb_id << " does not exist" << endl;
		return false;
	}
	int tuple_size = table->table_meta->tuple_size;
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
		tuple = (char*)malloc(sizeof(char)*tuple_size);
		memcpy(tuple, this->GetTuple(tb_id, i, tuple_size), tuple_size);
//		void* part;
//		TypeMalloc(part, table->table_meta->attr_meta[index]->attribute_type, strlen(tuple+table->table_meta->attr_meta[index]->attribute_offset));

//		Encoder::decode(tuple+table->table_meta->attr_meta[index]->attribute_offset, strlen(tuple+table->table_meta->attr_meta[index]->attribute_offset), part, table->table_meta->attr_meta[index]->attribute_type);
//		cout << tuple+table->table_meta->attr_meta[index]->attribute_offset << endl;
		database.insert(tuple+table->table_meta->attr_meta[index]->attribute_offset,table->start_addr+i*tuple_size);
		free(tuple);
	}
	this->tables[tb_id]->table_meta->attr_meta[col]->attribute_index = 1;
	return 0;
}

int TableManagement::UpdateIndex(int tb_id, int col, char* key, value_t value) {
	char index_name[16];
	sprintf(index_name, "%d", tb_id);
	strcat(index_name, "_");
	char tmp[2];
	sprintf(tmp, "%d", col);
	strcat(index_name, tmp);
	strcat(index_name, ".index");
	bpt::bplus_tree database(index_name);
	database.update(key, value);
	return 0;
}

int TableManagement::InsertIndex(int tb_id, int col, char* key, value_t value) {
	char index_name[16];
	sprintf(index_name, "%d", tb_id);
	strcat(index_name, "_");
	char tmp[2];
	sprintf(tmp, "%d", col);
	strcat(index_name, tmp);
	strcat(index_name, ".index");
	bpt::bplus_tree database(index_name);
	database.insert(key, value);
	return 0;
}

int TableManagement::RemoveIndex(int tb_id, int col, char* key) {
	char index_name[16];
	sprintf(index_name, "%d", tb_id);
	strcat(index_name, "_");
	char tmp[2];
	sprintf(tmp, "%d", col);
	strcat(index_name, tmp);
	strcat(index_name, ".index");
	bpt::bplus_tree database(index_name);
	database.remove(key);
	return 0;
}

int TableManagement::SearchIndex(FILE* fout, int tb_id, int col, int condition_num, char* keys[], OP left_op, OP right_op) {
	Table* table = this->tables[tb_id];
	if (table->exist == false) {
		cout << "table " << tb_id << " does not exist" << endl;
		return false;
	}
	int tuple_size = table->table_meta->tuple_size;
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
			tuple = (char*)malloc(sizeof(char)*tuple_size);
			memcpy(tuple, this->GetTuple(tb_id, value, tuple_size, -1), tuple_size);
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
				tuple = (char*)malloc(sizeof(char)*tuple_size);
				memcpy(tuple, this->GetTuple(tb_id, values[i], tuple_size, -1), tuple_size);
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

int TableManagement::SearchIndex(int res_tb_id, int tb_id, int col, int condition_num, char* keys[], OP left_op, OP right_op) {
	Table* table = this->tables[tb_id];
	if (table->exist == false) {
		cout << "table " << tb_id << " does not exist" << endl;
		return false;
	}
	int tuple_size = table->table_meta->tuple_size;
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
			tuple = (char*)malloc(sizeof(char)*tuple_size);
			memcpy(tuple, this->GetTuple(tb_id, value, tuple_size, -1), tuple_size);
			this->tables[res_tb_id]->table_meta->tuple_num += 1;
			this->tables[res_tb_id]->table_meta->real_tuple_num += 1;
			this->storage_manager->Write(res_tb_id, tuple, tuple_size);
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
				tuple = (char*)malloc(sizeof(char)*tuple_size);
				memcpy(tuple, this->GetTuple(tb_id, values[i], tuple_size, -1), tuple_size);
				this->tables[res_tb_id]->table_meta->tuple_num += 1;
				this->tables[res_tb_id]->table_meta->real_tuple_num += 1;
				this->storage_manager->Write(res_tb_id, tuple, tuple_size);
				free(tuple);
			}
		}
	}
	return 0;
}

int TableManagement::SearchIndex(int tb_id, int col, int condition_num, char* keys[], OP left_op, OP right_op, void* result[]) {
	int num = 0;
	int tuple_size = this->tables[tb_id]->table_meta->tuple_size;
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
			tuple = (char*)malloc(sizeof(char)*tuple_size);
			memcpy(tuple, this->GetTuple(tb_id, value, tuple_size, -1), tuple_size);
			result[0] = (char*)malloc(sizeof(char)*tuple_size);
			memcpy(result[0], tuple, tuple_size);
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
				tuple = (char*)malloc(sizeof(char)*tuple_size);
				memcpy(tuple, this->GetTuple(tb_id, values[i], tuple_size, -1), tuple_size);
				result[i] = (char*)malloc(sizeof(char)*tuple_size);
				memcpy(result[i], tuple, tuple_size);
				free(tuple);
			}
		}
	}
	return num;
}

int TableManagement::GetCmpCondition(vector<int> cols, vector<OP>& operators, char* keys[], char* &low, char* &high) {
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
			OP tmp = operators[1];
			operators[1] = operators[0];
			operators[0] = tmp;
			return 2;
		}
		return -2;
	}
	return -1;
}

bool TableManagement::CheckTuple(int tb_id, char* tuple, vector<int> cols, vector<OP> operators, char* keys[]) {
	Table* table = this->tables[tb_id];
	OP op;
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
		if (table->table_meta->attr_meta[i]->attribute_type == I || table->table_meta->attr_meta[i]->attribute_type == D){
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
		}  else if (table->table_meta->attr_meta[i]->attribute_type == F) {
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
	if (table->exist == false) {
		cout << "table " << tb_id << " does not exist" << endl;
		return false;
	}
	int tuple_size = table->table_meta->tuple_size;
	if (table->table_meta->tuple_num == 0)
		return false;
	FILE* fout;
	fout = fopen("result_tablescan", "w");
	if (!fout)
		return false;
	for (int i = 0; i < table->table_meta->tuple_num; i++) {
		char* tuple;
		tuple = (char*)malloc(sizeof(char)*tuple_size);
		memcpy(tuple, this->GetTuple(tb_id, i, tuple_size), tuple_size);

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
	if (table->exist == false) {
		cout << "table " << tb_id << " does not exist" << endl;
		return false;
	}
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

bool TableManagement::Select(int tb_id, vector<int> cols, vector<OP> operators, char* keys[]) {
	Table* table = this->tables[tb_id];
	if (table->exist == false) {
		cout << "table " << tb_id << " does not exist" << endl;
		return false;
	}
	int tuple_size = table->table_meta->tuple_size;
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
		input[0] = (char*)malloc(sizeof(char)*tuple_size);
		input[1] = (char*)malloc(sizeof(char)*tuple_size);
		memcpy(input[0], low, sizeof(low));
		memcpy(input[1], high, sizeof(high));
		this->SearchIndex(fout, tb_id, cols[0], condition_count, input, operators[0], operators[1]);
	} else {
		// no index or without conditions or non-equal condition or multiple conditions
		for (int i = 0; i < table->table_meta->tuple_num; i++) {
			char* tuple;
			tuple = (char*)malloc(sizeof(char)*tuple_size);
			memcpy(tuple, this->GetTuple(tb_id, i, tuple_size), tuple_size);
			if (this->CheckTuple(tb_id, tuple, cols, operators, keys)) {
				for (int j = 0; j < table->table_meta->attribute_num; j++) {
//					cout << table->table_meta->attr_meta[j]->attribute_offset << endl;
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

int TableManagement::SelectTmp(int tb_id, vector<int> cols, vector<OP> operators, char* keys[]) {
	Table* table = this->tables[tb_id];
	if (table->exist == false) {
		cout << "table " << tb_id << " does not exist" << endl;
		return false;
	}
	int tuple_size = table->table_meta->tuple_size;
	if (table->table_meta->tuple_num == 0)
		return false;

	// Tmp table
	time_t currtime = time(NULL);
	tm* p = localtime(&currtime);
	char filename[100] = {0};
	sprintf(filename,"tmp%d%02d%02d%02d%02d%02d",tb_id,p->tm_mon+1,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
	int res_tuple_size = tuple_size;
	int attribute_num = table->table_meta->attribute_num;
	char attr_names[16][MAX_ATTR_NAME_LENGTH];
	TYPE *types;
	int *attr_length;
	int *attr_offset;
	types = (TYPE*)malloc(sizeof(TYPE)*attribute_num);
	attr_length = (int*)malloc(sizeof(int)*attribute_num);
	attr_offset = (int*)malloc(sizeof(int)*attribute_num);
	for (int i = 0; i < attribute_num; i++) {
		strcpy(attr_names[i], table->table_meta->attr_meta[i]->attribute_name);
		types[i] = table->table_meta->attr_meta[i]->attribute_type;
		attr_length[i] = table->table_meta->attr_meta[i]->attribute_length;
		attr_offset[i] = table->table_meta->attr_meta[i]->attribute_offset;
	}

	int res_tb_id = CreateTable(0, filename, res_tuple_size, attr_names, types, attr_length, attr_offset, attribute_num);
	char* low = "!";
	char* high;
	high = (char*)malloc(sizeof(high)*200);
	memcpy(high, "~", 1);
	for (int i = 0; i < 50; i++)
		strcat(high, "~");
	int condition_count = this->GetCmpCondition(cols, operators, keys, low, high);
	if (condition_count == 1 && table->table_meta->attr_meta[cols[0]]->attribute_index != -1) {
		// equal condition select and has index
		this->SearchIndex(res_tb_id, tb_id, cols[0], condition_count, keys, operators[0], operators[1]);
	} else if (condition_count == 2 && table->table_meta->attr_meta[cols[0]]->attribute_index != -1)  {
		//range condition select and has index
		char* input[2];
		input[0] = (char*)malloc(sizeof(char)*tuple_size);
		input[1] = (char*)malloc(sizeof(char)*tuple_size);
		memcpy(input[0], low, sizeof(low));
		memcpy(input[1], high, sizeof(high));
		this->SearchIndex(res_tb_id, tb_id, cols[0], condition_count, input, operators[0], operators[1]);
	} else {
		// no index or without conditions or non-equal condition or multiple conditions
		for (int i = 0; i < table->table_meta->tuple_num; i++) {
			char* tuple;
			tuple = (char*)malloc(sizeof(char)*tuple_size);
			memcpy(tuple, this->GetTuple(tb_id, i, tuple_size), tuple_size);
			if (this->CheckTuple(tb_id, tuple, cols, operators, keys)) {
				this->tables[res_tb_id]->table_meta->tuple_num += 1;
				this->tables[res_tb_id]->table_meta->real_tuple_num += 1;
				this->storage_manager->Write(res_tb_id, tuple, tuple_size);
			}
		}
	}
	cout << "select ok " << endl;
	return res_tb_id;
}

void TableManagement::Project(int tb_id, vector<int> cols) {
	Table* table = this->tables[tb_id];
	if (table->exist == false) {
		cout << "table " << tb_id << " does not exist" << endl;
		return;
	}
	int tuple_size = table->table_meta->tuple_size;
	if (table->table_meta->tuple_num == 0) {
		cout << "empty table" << endl;
		return;
	}
	FILE* fout;
	fout = fopen("result_project", "w");
	if (!fout)
		return;
	if (cols.size() == 0) {
		// select *
		for (int i = 0; i < table->table_meta->tuple_num; i++) {
			char* tuple;
			tuple = (char*)malloc(sizeof(char)*tuple_size);
			memcpy(tuple, this->GetTuple(tb_id, i, tuple_size), tuple_size);
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
			tuple = (char*)malloc(sizeof(char)*tuple_size);
			memcpy(tuple, this->GetTuple(tb_id, i, tuple_size), tuple_size);
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
	cout << "project ok" << endl;
	//return true;
}

int TableManagement::ProjectTmp(int tb_id, vector<int> cols) {
	Table* table = this->tables[tb_id];
	if (table->exist == false) {
		cout << "table " << tb_id << " does not exist" << endl;
		return false;
	}
	int tuple_size = table->table_meta->tuple_size;
	if (table->table_meta->tuple_num == 0)
		return false;

	// Tmp table
	time_t currtime = time(NULL);
	tm* p = localtime(&currtime);
	char filename[100] = {0};
	sprintf(filename,"tmp%d%02d%02d%02d%02d%02d",tb_id,p->tm_mon+1,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
	int res_tb_id = -1;
	if (cols.size() == 0) {
		// select *
		int res_tuple_size = tuple_size;
		int attribute_num = table->table_meta->attribute_num;
		char attr_names[16][MAX_ATTR_NAME_LENGTH];
		TYPE *types;
		int *attr_length;
		int *attr_offset;
		types = (TYPE*)malloc(sizeof(TYPE)*attribute_num);
		attr_length = (int*)malloc(sizeof(int)*attribute_num);
		attr_offset = (int*)malloc(sizeof(int)*attribute_num);
		for (int i = 0; i < attribute_num; i++) {
			strcpy(attr_names[i], table->table_meta->attr_meta[i]->attribute_name);
			types[i] = table->table_meta->attr_meta[i]->attribute_type;
			attr_length[i] = table->table_meta->attr_meta[i]->attribute_length;
			attr_offset[i] = table->table_meta->attr_meta[i]->attribute_offset;
		}
		res_tb_id = CreateTable(0, filename, res_tuple_size, attr_names, types, attr_length, attr_offset, attribute_num);

		for (int i = 0; i < table->table_meta->tuple_num; i++) {
			char* tuple;
			tuple = (char*)malloc(sizeof(char)*tuple_size);
			memcpy(tuple, this->GetTuple(tb_id, i, tuple_size), tuple_size);
			this->tables[res_tb_id]->table_meta->tuple_num += 1;
			this->tables[res_tb_id]->table_meta->real_tuple_num += 1;
			this->storage_manager->Write(res_tb_id, tuple, tuple_size);
			free(tuple);
		}
	} else {
		int res_tuple_size = tuple_size;
		int attribute_num = cols.size();
		char attr_names[16][MAX_ATTR_NAME_LENGTH];
		TYPE *types;
		int *attr_length;
		int *attr_offset;
		types = (TYPE*)malloc(sizeof(TYPE)*attribute_num);
		attr_length = (int*)malloc(sizeof(int)*attribute_num);
		attr_offset = (int*)malloc(sizeof(int)*attribute_num);
		for (int i = 0; i < cols.size(); i++) {
			int col = cols[i];
			strcpy(attr_names[i], table->table_meta->attr_meta[col]->attribute_name);
			types[i] = table->table_meta->attr_meta[col]->attribute_type;
			attr_length[i] = table->table_meta->attr_meta[col]->attribute_length;
			attr_offset[i] = table->table_meta->attr_meta[i]->attribute_offset;
		}

		res_tb_id = CreateTable(0, filename, res_tuple_size, attr_names, types, attr_length, attr_offset, attribute_num);
		Table* res_table = this->tables[res_tb_id];
		for (int i = 0; i < table->table_meta->tuple_num; i++) {
			char* tuple;
			tuple = (char*)malloc(sizeof(char)*tuple_size);
			memcpy(tuple, this->GetTuple(tb_id, i, tuple_size), tuple_size);
			char* result;
			result = (char*)malloc(sizeof(char)*tuple_size);
			int offset = 0;
			for (int j = 0; j < cols.size(); j++) {
				int col = cols[j];
				offset = res_table->table_meta->attr_meta[j]->attribute_offset;
				memcpy(result+offset, tuple+table->table_meta->attr_meta[col]->attribute_offset, res_table->table_meta->attr_meta[j]->attribute_length);
			}
			this->tables[res_tb_id]->table_meta->tuple_num += 1;
			this->storage_manager->Write(res_tb_id, result, tuple_size);
			free(result);
			free(tuple);
		}
	}
	return res_tb_id;
}

bool TableManagement::Project(FILE* fout, int tb_id, vector<int> cols) {
	Table* table = this->tables[tb_id];
	if (table->exist == false) {
		cout << "table " << tb_id << " does not exist" << endl;
		return false;
	}
	int tuple_size = table->table_meta->tuple_size;
	if (table->table_meta->tuple_num == 0)
		return false;
	if (!fout)
		return false;
	if (cols.size() == 0) {
		// select *
		for (int i = 0; i < table->table_meta->tuple_num; i++) {
			char* tuple;
			tuple = (char*)malloc(sizeof(char)*tuple_size);
			memcpy(tuple, this->GetTuple(tb_id, i, tuple_size), tuple_size);
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
			tuple = (char*)malloc(sizeof(char)*tuple_size);
			memcpy(tuple, this->GetTuple(tb_id, i, tuple_size), tuple_size);
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

bool TableManagement::NestedLoopJoin(int left_tb_id, int right_tb_id, vector<int> cols1, vector<int> cols2, vector<OP> operators, bool isReverse) {
	Table* left_table = this->tables[left_tb_id];
	Table* right_table = this->tables[right_tb_id];
	if (left_table->exist == false) {
		cout << "table " << left_tb_id << " does not exist" << endl;
		return false;
	}
	if (right_table->exist == false) {
		cout << "table " << right_tb_id << " does not exist" << endl;
		return false;
	}
	int left_tuple_size = left_table->table_meta->tuple_size;
	int right_tuple_size = right_table->table_meta->tuple_size;
	if (left_table->table_meta->tuple_num == 0 || right_table->table_meta->tuple_num == 0)
			return false;
	FILE* fout;
	fout = fopen("result_nestedloopjoin", "w");
	if (!fout)
		return false;
	for (int i = 0; i < right_table->table_meta->tuple_num; i++) {
		char* tuple1;
		tuple1 = (char*)malloc(sizeof(char)*right_tuple_size);
		memcpy(tuple1, this->GetTuple(right_tb_id, i, right_tuple_size), right_tuple_size);
		char* keys[10];
		for (int idx = 0; idx < cols2.size(); idx++) {
			int col1 = cols2[idx];
			keys[idx] = (char*)malloc(sizeof(char)*right_tuple_size);
			memcpy(keys[idx], tuple1+right_table->table_meta->attr_meta[col1]->attribute_offset, right_table->table_meta->attr_meta[col1]->attribute_length);
		}
		for (int j = 0; j < left_table->table_meta->tuple_num; j++) {
			char* tuple2;
			tuple2 = (char*)malloc(sizeof(char)*left_tuple_size);
			memcpy(tuple2, this->GetTuple(left_tb_id, j, left_tuple_size), left_tuple_size);
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

int TableManagement::NestedLoopJoinTmp(int left_tb_id, int right_tb_id, vector<int> cols1, vector<int> cols2, vector<OP> operators, bool isReverse) {
	Table* left_table = this->tables[left_tb_id];
	Table* right_table = this->tables[right_tb_id];
	if (left_table->exist == false) {
		cout << "table " << left_tb_id << " does not exist" << endl;
		return false;
	}
	if (right_table->exist == false) {
		cout << "table " << right_tb_id << " does not exist" << endl;
		return false;
	}
	int left_tuple_size = left_table->table_meta->tuple_size;
	int right_tuple_size = right_table->table_meta->tuple_size;
	if (left_table->table_meta->tuple_num == 0 || right_table->table_meta->tuple_num == 0)
			return false;

	// Tmp table
	time_t currtime = time(NULL);
	tm* p = localtime(&currtime);
	char filename[100] = {0};
	sprintf(filename,"tmp%d%d%02d%02d%02d%02d%02d",left_tb_id, right_tb_id,p->tm_mon+1,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
	int res_tuple_size = left_tuple_size + right_tuple_size;
	int left_attr_num = left_table->table_meta->attribute_num;
	int right_attr_num = right_table->table_meta->attribute_num;
	int attribute_num = left_attr_num + right_attr_num;
	char attr_names[16][MAX_ATTR_NAME_LENGTH];
	TYPE *types;
	int *attr_length;
	int *attr_offset;
	types = (TYPE*)malloc(sizeof(TYPE)*attribute_num);
	attr_length = (int*)malloc(sizeof(int)*attribute_num);
	attr_offset = (int*)malloc(sizeof(int)*attribute_num);
	int off = 0;
	if (!isReverse) {
		for (int i = 0; i < left_attr_num; i++) {
			strcpy(attr_names[i], left_table->table_meta->attr_meta[i]->attribute_name);
			types[i] = left_table->table_meta->attr_meta[i]->attribute_type;
			attr_length[i] = left_table->table_meta->attr_meta[i]->attribute_length;
			attr_offset[i] = off;
			off += attr_length[i];
		}
		off = left_tuple_size;
		for (int i = 0; i < right_attr_num; i++) {
			strcpy(attr_names[i+left_attr_num], right_table->table_meta->attr_meta[i]->attribute_name);
			types[i+left_attr_num] = right_table->table_meta->attr_meta[i]->attribute_type;
			attr_length[i+left_attr_num] = right_table->table_meta->attr_meta[i]->attribute_length;
			attr_offset[i+left_attr_num] = off;
			off += attr_length[i+left_attr_num];
		}
	} else {
		for (int i = 0; i < right_attr_num; i++) {
			strcpy(attr_names[i], right_table->table_meta->attr_meta[i]->attribute_name);
			types[i] = right_table->table_meta->attr_meta[i]->attribute_type;
			attr_length[i] = right_table->table_meta->attr_meta[i]->attribute_length;
			attr_offset[i] = off;
			off += attr_length[i];
		}
		off = right_tuple_size;
		for (int i = 0; i < left_attr_num; i++) {
			strcpy(attr_names[i+right_attr_num], left_table->table_meta->attr_meta[i]->attribute_name);
			types[i+right_attr_num] = left_table->table_meta->attr_meta[i]->attribute_type;
			attr_length[i+right_attr_num] = left_table->table_meta->attr_meta[i]->attribute_length;
			attr_offset[i+right_attr_num] = off;
			off += attr_length[i+right_attr_num];
		}
	}
	int res_tb_id = CreateTable(0, filename, res_tuple_size, attr_names, types, attr_length, attr_offset, attribute_num);

	for (int i = 0; i < right_table->table_meta->tuple_num; i++) {
		char* tuple1;
		tuple1 = (char*)malloc(sizeof(char)*right_tuple_size);
		memcpy(tuple1, this->GetTuple(right_tb_id, i, right_tuple_size), right_tuple_size);
		char* keys[10];
		for (int idx = 0; idx < cols2.size(); idx++) {
			int col1 = cols2[idx];
			keys[idx] = (char*)malloc(sizeof(char)*right_tuple_size);
			memcpy(keys[idx], tuple1+right_table->table_meta->attr_meta[col1]->attribute_offset, right_table->table_meta->attr_meta[col1]->attribute_length);
		}
		for (int j = 0; j < left_table->table_meta->tuple_num; j++) {
			char* tuple2;
			tuple2 = (char*)malloc(sizeof(char)*left_tuple_size);
			memcpy(tuple2, this->GetTuple(left_tb_id, j, left_tuple_size), left_tuple_size);
			if (this->CheckTuple(left_tb_id, tuple2, cols1, operators, keys)) {
				if (!isReverse) {
					char* res_tuple;
					res_tuple = (char*)malloc(sizeof(char)*res_tuple_size);
					memcpy(res_tuple, tuple2, left_tuple_size);
					memcpy(res_tuple+left_tuple_size, tuple1, right_tuple_size);
					this->tables[res_tb_id]->table_meta->tuple_num += 1;
					this->tables[res_tb_id]->table_meta->real_tuple_num += 1;
					this->storage_manager->Write(res_tb_id, res_tuple, res_tuple_size);
				} else {
					char* res_tuple;
					res_tuple = (char*)malloc(sizeof(char)*res_tuple_size);
					memcpy(res_tuple, tuple1, right_tuple_size);
					memcpy(res_tuple+right_tuple_size, tuple2, left_tuple_size);
					this->tables[res_tb_id]->table_meta->tuple_num += 1;
					this->tables[res_tb_id]->table_meta->real_tuple_num += 1;
					this->storage_manager->Write(res_tb_id, res_tuple, res_tuple_size);
				}
				free(tuple2);
			}
		}
		free(tuple1);
	}
	return res_tb_id;
}

bool TableManagement::NestedLoopCartesianProduct(int left_tb_id, int right_tb_id, bool isReverse) {
	cout << "ok  " << endl;
	Table* left_table = this->tables[left_tb_id];
	Table* right_table = this->tables[right_tb_id];
	if (left_table->exist == false) {
		cout << "table " << left_tb_id << " does not exist" << endl;
		return false;
	}
	if (right_table->exist == false) {
		cout << "table " << right_tb_id << " does not exist" << endl;
		return false;
	}
	int left_tuple_size = left_table->table_meta->tuple_size;
	int right_tuple_size = right_table->table_meta->tuple_size;
	if (left_table->table_meta->tuple_num == 0 || right_table->table_meta->tuple_num == 0)
		return false;
	FILE* fout;
	fout = fopen("result_nlcp", "w");
	if (!fout)
		return false;
	for (int i = 0; i < left_table->table_meta->tuple_num; i++) {
		char* tuple1;
		tuple1 = (char*)malloc(sizeof(char)*left_tuple_size);
		memcpy(tuple1, this->GetTuple(left_tb_id, i, left_tuple_size), left_tuple_size);

		for (int j = 0; j < right_table->table_meta->tuple_num; j++) {
			char* tuple2;
			tuple2 = (char*)malloc(sizeof(char)*right_tuple_size);
			memcpy(tuple2, this->GetTuple(right_tb_id, j, right_tuple_size), right_tuple_size);
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

int TableManagement::NestedLoopCartesianProductTmp(int left_tb_id, int right_tb_id, bool isReverse) {
	Table* left_table = this->tables[left_tb_id];
	Table* right_table = this->tables[right_tb_id];
	if (left_table->exist == false) {
		cout << "table " << left_tb_id << " does not exist" << endl;
		return false;
	}
	if (right_table->exist == false) {
		cout << "table " << right_tb_id << " does not exist" << endl;
		return false;
	}
	int left_tuple_size = left_table->table_meta->tuple_size;
	int right_tuple_size = right_table->table_meta->tuple_size;
	if (left_table->table_meta->tuple_num == 0 || right_table->table_meta->tuple_num == 0)
		return false;

	// Tmp table
	time_t currtime = time(NULL);
	tm* p = localtime(&currtime);
	char filename[100] = {0};
	sprintf(filename,"tmp%d%d%02d%02d%02d%02d%02d",left_tb_id, right_tb_id,p->tm_mon+1,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
	int res_tuple_size = left_tuple_size + right_tuple_size;
	int left_attr_num = left_table->table_meta->attribute_num;
	int right_attr_num = right_table->table_meta->attribute_num;
	int attribute_num = left_attr_num + right_attr_num;
	char attr_names[16][MAX_ATTR_NAME_LENGTH];
	TYPE *types;
	int *attr_length;
	int *attr_offset;
	types = (TYPE*)malloc(sizeof(TYPE)*attribute_num);
	attr_length = (int*)malloc(sizeof(int)*attribute_num);
	attr_offset = (int*)malloc(sizeof(int)*attribute_num);
	int off = 0;
	if (!isReverse) {
		for (int i = 0; i < left_attr_num; i++) {
			strcpy(attr_names[i], left_table->table_meta->attr_meta[i]->attribute_name);
			types[i] = left_table->table_meta->attr_meta[i]->attribute_type;
			attr_length[i] = left_table->table_meta->attr_meta[i]->attribute_length;
			attr_offset[i] = off;
			off += attr_length[i];
		}
		off = left_tuple_size;
		for (int i = 0; i < right_attr_num; i++) {
			strcpy(attr_names[i+left_attr_num], right_table->table_meta->attr_meta[i]->attribute_name);
			types[i+left_attr_num] = right_table->table_meta->attr_meta[i]->attribute_type;
			attr_length[i+left_attr_num] = right_table->table_meta->attr_meta[i]->attribute_length;
			attr_offset[i+left_attr_num] = off;
			off += attr_length[i+left_attr_num];
		}
	} else {
		for (int i = 0; i < right_attr_num; i++) {
			strcpy(attr_names[i], right_table->table_meta->attr_meta[i]->attribute_name);
			types[i] = right_table->table_meta->attr_meta[i]->attribute_type;
			attr_length[i] = right_table->table_meta->attr_meta[i]->attribute_length;
			attr_offset[i] = off;
			off += attr_length[i];
		}
		off = right_tuple_size;
		for (int i = 0; i < left_attr_num; i++) {
			strcpy(attr_names[i+right_attr_num], left_table->table_meta->attr_meta[i]->attribute_name);
			types[i+right_attr_num] = left_table->table_meta->attr_meta[i]->attribute_type;
			attr_length[i+right_attr_num] = left_table->table_meta->attr_meta[i]->attribute_length;
			attr_offset[i+right_attr_num] = off;
			off += attr_length[i+right_attr_num];
		}
	}

	int res_tb_id = CreateTable(0, filename, res_tuple_size, attr_names, types, attr_length, attr_offset, attribute_num);

	for (int i = 0; i < left_table->table_meta->tuple_num; i++) {
		char* tuple1;
		tuple1 = (char*)malloc(sizeof(char)*left_tuple_size);
		memcpy(tuple1, this->GetTuple(left_tb_id, i, left_tuple_size), left_tuple_size);
		for (int j = 0; j < right_table->table_meta->tuple_num; j++) {
			char* tuple2;
			tuple2 = (char*)malloc(sizeof(char)*right_tuple_size);
			memcpy(tuple2, this->GetTuple(right_tb_id, j, right_tuple_size), right_tuple_size);
			if (!isReverse) {
				char* res_tuple;
				res_tuple = (char*)malloc(sizeof(char)*res_tuple_size);
				memcpy(res_tuple, tuple1, left_tuple_size);
				memcpy(res_tuple+left_tuple_size, tuple2, right_tuple_size);
				this->tables[res_tb_id]->table_meta->tuple_num += 1;
				this->tables[res_tb_id]->table_meta->real_tuple_num += 1;
//				cout << res_tuple+left_tuple_size << endl;
				this->storage_manager->Write(res_tb_id, res_tuple, res_tuple_size);
			} else {
				char* res_tuple;
				res_tuple = (char*)malloc(sizeof(char)*res_tuple_size);
				memcpy(res_tuple, tuple2, right_tuple_size);
				memcpy(res_tuple+right_tuple_size, tuple1, left_tuple_size);
				this->tables[res_tb_id]->table_meta->tuple_num += 1;
				this->tables[res_tb_id]->table_meta->real_tuple_num += 1;
				this->storage_manager->Write(res_tb_id, res_tuple, res_tuple_size);
			}
			free(tuple2);
		}
		free(tuple1);
	}
	cout << "CartesianProduct ok" << endl;
	return res_tb_id;
}

int TableManagement::SingleIndexJoin(int right_tb_id, int col2, char* keys[], OP op, void* result[]) {
	int tuple_size = this->tables[right_tb_id]->table_meta->tuple_size;
	if (op == eq) {
		return this->SearchIndex(right_tb_id, col2, 1, keys, eq, eq, result);
	} else if (op == ge || op == gt) {
		OP op1;
		keys[1] = (char*)malloc(sizeof(char)*tuple_size);
		memcpy(keys[1], keys[0], sizeof(keys[0]));
		memcpy(keys[0], "!", sizeof("!"));
		if (op == ge) {
			op1 = le;
		} else {
			op1 = lt;
		}
		return this->SearchIndex(right_tb_id, col2, 2, keys, ge, op1, result);
	} else if (op == le || op == lt) {
		OP op2;
		if (op == le) {
			op2 = ge;
		} else {
			op2 = gt;
		}
		keys[1] = (char*)malloc(sizeof(char)*tuple_size);
		memcpy(keys[1], "~~~~~~~~~~~~~~~~~~~~~~~", sizeof("~~~~~~~~~~~~~~~~~~~~~~~"));
		return this->SearchIndex(right_tb_id, col2, 2, keys, op2, le, result);
	} else {
		return -1;
	}
	return -1;
}

bool TableManagement::IndexJoin(int left_tb_id, int right_tb_id, vector<int> cols1, vector<int> cols2, vector<OP> operators, bool isReverse) {
	Table* left_table = this->tables[left_tb_id];
	Table* right_table = this->tables[right_tb_id];
	if (left_table->exist == false) {
		cout << "table " << left_tb_id << " does not exist" << endl;
		return false;
	}
	if (right_table->exist == false) {
		cout << "table " << right_tb_id << " does not exist" << endl;
		return false;
	}
	int left_tuple_size = left_table->table_meta->tuple_size;
	int right_tuple_size = right_table->table_meta->tuple_size;
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
			tuple1 = (char*)malloc(sizeof(char)*left_tuple_size);
			memcpy(tuple1, this->GetTuple(left_tb_id, i, left_tuple_size), left_tuple_size);
			char* keys[2];
			keys[0] = (char*)malloc(sizeof(char)*left_tuple_size);
			memcpy(keys[0], tuple1+left_table->table_meta->attr_meta[col1]->attribute_offset, left_table->table_meta->attr_meta[col1]->attribute_length);
			if (operators[0] == eq) {
				void* result[4096];
				this->SearchIndex(right_tb_id, col2, 1, keys, operators[0], operators[0], result);
				char* tuple2;
				tuple2 = (char*)malloc(sizeof(char)*right_tuple_size);

				if (result[0] != NULL)
					memcpy(tuple2, result[0], left_tuple_size);
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
				keys[1] = (char*)malloc(sizeof(char)*right_tuple_size);
				memcpy(keys[1], keys[0], sizeof(keys[0]));
				memcpy(keys[0], "!", sizeof("!"));
				void* result[409600];
				OP op;
				if (operators[0] == ge) {
					op = le;
				} else {
					op = lt;
				}
				int num = this->SearchIndex(right_tb_id, col2, 2, keys, ge, op, result);
				for (int j = 0; j < num; j++) {
					if (result[j] != NULL) {
						char* tuple2;
						tuple2 = (char*)malloc(sizeof(char)*right_tuple_size);
						memcpy(tuple2, result[j], right_tuple_size);
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
				OP op;
				if (operators[0] == lt) {
					op = gt;
				} else {
					op = ge;
				}
				keys[1] = (char*)malloc(sizeof(char)*right_tuple_size);
				memcpy(keys[1], "~~~~~~~~~~~~~~~~~~~~~~~", sizeof("~~~~~~~~~~~~~~~~~~~~~~~"));
				void* result[409600];
				int num = this->SearchIndex(right_tb_id, col2, 2, keys, op, le, result);
				for (int j = 0; j < num; j++) {
					if (result[j] != NULL) {
						char* tuple2;
						tuple2 = (char*)malloc(sizeof(char)*right_tuple_size);
						memcpy(tuple2, result[j], right_tuple_size);
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
					tuple2 = (char*)malloc(sizeof(char)*right_tuple_size);
					memcpy(tuple2, result1[j], right_tuple_size);
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
				keys[0] = (char*)malloc(sizeof(char)*left_tuple_size);
				memcpy(keys[0], tuple1+left_table->table_meta->attr_meta[col1]->attribute_offset, left_table->table_meta->attr_meta[col1]->attribute_length);
				void* result2[4096];
				int num2 = this->SingleIndexJoin(right_tb_id, cols2[0], keys, operators[1], result2);
				for (int j = 0; j < num2; j++) {
					char* tuple2;
					tuple2 = (char*)malloc(sizeof(char)*right_tuple_size);
					memcpy(tuple2, result2[j], right_tuple_size);
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
			tuple1 = (char*)malloc(sizeof(char)*left_tuple_size);
			memcpy(tuple1, this->GetTuple(left_tb_id, i, left_tuple_size), left_tuple_size);
			char* keys[1];
			keys[0] = (char*)malloc(sizeof(char)*right_tuple_size);
			memcpy(keys[0], tuple1+left_table->table_meta->attr_meta[col1]->attribute_offset, right_tuple_size);
			if (operators[0] != nq) {
				void* tuples1[4096]; // result of condition 1
				int num = this->SingleIndexJoin(right_tb_id, cols2[0], keys, operators[0], tuples1);
				vector<int> cols;
				vector<OP> ops;
				for (int idx = 0; idx < cols1.size() - 1; idx++) {
					cols.insert((vector<int>::iterator)cols.begin()+idx, cols2[idx+1]);
					OP op1;
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
					ops.insert((vector<OP>::iterator)ops.begin()+idx, op1);
					if (operators[idx+1] == nq) {
						op1 = gt;
						ops.insert((vector<OP>::iterator)ops.begin()+idx+1, op1);
						cols.insert((vector<int>::iterator)cols.begin()+idx+1, cols2[idx+1]);
					}
				}
				char* other_keys[4];
				for (int idx = 1; idx < cols1.size(); idx++) {
					other_keys[idx-1] = (char*)malloc(sizeof(char)*left_tuple_size);
					memcpy(other_keys[idx-1], tuple1+left_table->table_meta->attr_meta[cols1[idx]]->attribute_offset, left_tuple_size);
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

int TableManagement::IndexJoinTmp(int left_tb_id, int right_tb_id, vector<int> cols1, vector<int> cols2, vector<OP> operators, bool isReverse) {
	Table* left_table = this->tables[left_tb_id];
	Table* right_table = this->tables[right_tb_id];
	if (left_table->exist == false) {
		cout << "table " << left_tb_id << " does not exist" << endl;
		return false;
	}
	if (right_table->exist == false) {
		cout << "table " << right_tb_id << " does not exist" << endl;
		return false;
	}
	int left_tuple_size = left_table->table_meta->tuple_size;
	int right_tuple_size = right_table->table_meta->tuple_size;
	if (left_table->table_meta->tuple_num == 0 || right_table->table_meta->tuple_num == 0) {
		return false;
	}
	if (cols1.size() != cols2.size() || cols1.size() != operators.size()) {
		return false;
	}

	// Tmp table
	time_t currtime = time(NULL);
	tm* p = localtime(&currtime);
	char filename[100] = {0};
	sprintf(filename,"tmp%d%d%02d%02d%02d%02d%02d",left_tb_id, right_tb_id,p->tm_mon+1,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
	int res_tuple_size = left_tuple_size + right_tuple_size;
	int left_attr_num = left_table->table_meta->attribute_num;
	int right_attr_num = right_table->table_meta->attribute_num;
	int attribute_num = left_attr_num + right_attr_num;
	char attr_names[16][MAX_ATTR_NAME_LENGTH];
	TYPE *types;
	int *attr_length;
	int *attr_offset;
	types = (TYPE*)malloc(sizeof(TYPE)*attribute_num);
	attr_length = (int*)malloc(sizeof(int)*attribute_num);
	attr_offset = (int*)malloc(sizeof(int)*attribute_num);
	int off = 0;
	if (!isReverse) {
		for (int i = 0; i < left_attr_num; i++) {
			strcpy(attr_names[i], left_table->table_meta->attr_meta[i]->attribute_name);
			types[i] = left_table->table_meta->attr_meta[i]->attribute_type;
			attr_length[i] = left_table->table_meta->attr_meta[i]->attribute_length;
			attr_offset[i] = off;
			off += attr_length[i];
		}
		off = left_tuple_size;
		for (int i = 0; i < right_attr_num; i++) {
			strcpy(attr_names[i+left_attr_num], right_table->table_meta->attr_meta[i]->attribute_name);
			types[i+left_attr_num] = right_table->table_meta->attr_meta[i]->attribute_type;
			attr_length[i+left_attr_num] = right_table->table_meta->attr_meta[i]->attribute_length;
			attr_offset[i+left_attr_num] = off;
			off += attr_length[i+left_attr_num];
		}
	} else {
		for (int i = 0; i < right_attr_num; i++) {
			strcpy(attr_names[i], right_table->table_meta->attr_meta[i]->attribute_name);
			types[i] = right_table->table_meta->attr_meta[i]->attribute_type;
			attr_length[i] = right_table->table_meta->attr_meta[i]->attribute_length;
			attr_offset[i] = off;
			off += attr_length[i];
		}
		off = right_tuple_size;
		for (int i = 0; i < left_attr_num; i++) {
			strcpy(attr_names[i+right_attr_num], left_table->table_meta->attr_meta[i]->attribute_name);
			types[i+right_attr_num] = left_table->table_meta->attr_meta[i]->attribute_type;
			attr_length[i+right_attr_num] = left_table->table_meta->attr_meta[i]->attribute_length;
			attr_offset[i+right_attr_num] = off;
			off += attr_length[i+right_attr_num];
		}
	}
	int res_tb_id = CreateTable(0, filename, res_tuple_size, attr_names, types, attr_length, attr_offset, attribute_num);

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
			tuple1 = (char*)malloc(sizeof(char)*left_tuple_size);
			memcpy(tuple1, this->GetTuple(left_tb_id, i, left_tuple_size), left_tuple_size);
			char* keys[2];
			keys[0] = (char*)malloc(sizeof(char)*left_tuple_size);
			memcpy(keys[0], tuple1+left_table->table_meta->attr_meta[col1]->attribute_offset, left_table->table_meta->attr_meta[col1]->attribute_length);
			if (operators[0] == eq) {
				void* result[4096];
				this->SearchIndex(right_tb_id, col2, 1, keys, operators[0], operators[0], result);
				char* tuple2;
				tuple2 = (char*)malloc(sizeof(char)*right_tuple_size);

				if (result[0] != NULL)
					memcpy(tuple2, result[0], right_tuple_size);
				if (tuple2 != NULL) {
					if (!isReverse) {
						char* res_tuple;
						res_tuple = (char*)malloc(sizeof(char)*res_tuple_size);
						memcpy(res_tuple, tuple1, left_tuple_size);
						memcpy(res_tuple+left_tuple_size, tuple2, right_tuple_size);
						this->tables[res_tb_id]->table_meta->tuple_num += 1;
						this->tables[res_tb_id]->table_meta->real_tuple_num += 1;
						this->storage_manager->Write(res_tb_id, res_tuple, res_tuple_size);

					} else {
						char* res_tuple;
						res_tuple = (char*)malloc(sizeof(char)*res_tuple_size);
						memcpy(res_tuple, tuple2, right_tuple_size);
						memcpy(res_tuple+right_tuple_size, tuple1, left_tuple_size);
						this->tables[res_tb_id]->table_meta->tuple_num += 1;
						this->tables[res_tb_id]->table_meta->real_tuple_num += 1;
						this->storage_manager->Write(res_tb_id, res_tuple, res_tuple_size);
					}
				}
			} else if (operators[0] == ge || operators[0] == gt) {
				keys[1] = (char*)malloc(sizeof(char)*right_tuple_size);
				memcpy(keys[1], keys[0], sizeof(keys[0]));
				memcpy(keys[0], "!", sizeof("!"));
				void* result[409600];
				OP op;
				if (operators[0] == ge) {
					op = le;
				} else {
					op = lt;
				}
				int num = this->SearchIndex(right_tb_id, col2, 2, keys, ge, op, result);
				for (int j = 0; j < num; j++) {
					if (result[j] != NULL) {
						char* tuple2;
						tuple2 = (char*)malloc(sizeof(char)*right_tuple_size);
						memcpy(tuple2, result[j], right_tuple_size);
						char* res_tuple;
						res_tuple = (char*)malloc(sizeof(char)*res_tuple_size);
						if (!isReverse) {
							memcpy(res_tuple, tuple1, left_tuple_size);
							memcpy(res_tuple+left_tuple_size, tuple2, right_tuple_size);
							this->tables[res_tb_id]->table_meta->tuple_num += 1;
							this->tables[res_tb_id]->table_meta->real_tuple_num += 1;
							this->storage_manager->Write(res_tb_id, res_tuple, res_tuple_size);
						} else {
							memcpy(res_tuple, tuple2, right_tuple_size);
							memcpy(res_tuple+right_tuple_size, tuple1, left_tuple_size);
							this->tables[res_tb_id]->table_meta->tuple_num += 1;
							this->tables[res_tb_id]->table_meta->real_tuple_num += 1;
							this->storage_manager->Write(res_tb_id, res_tuple, res_tuple_size);
						}
						free(tuple2);
					}
				}

			} else if (operators[0] == le || operators[0] == lt) {
				OP op;
				if (operators[0] == lt) {
					op = gt;
				} else {
					op = ge;
				}
				keys[1] = (char*)malloc(sizeof(char)*right_tuple_size);
				memcpy(keys[1], "~~~~~~~~~~~~~~~~~~~~~~~", sizeof("~~~~~~~~~~~~~~~~~~~~~~~"));
				void* result[409600];
				int num = this->SearchIndex(right_tb_id, col2, 2, keys, op, le, result);
				for (int j = 0; j < num; j++) {
					if (result[j] != NULL) {
						char* tuple2;
						tuple2 = (char*)malloc(sizeof(char)*right_tuple_size);
						memcpy(tuple2, result[j], right_tuple_size);
						char* res_tuple;
						res_tuple = (char*)malloc(sizeof(char)*res_tuple_size);
						if (!isReverse) {
							memcpy(res_tuple, tuple1, left_tuple_size);
							memcpy(res_tuple+left_tuple_size, tuple2, right_tuple_size);
							this->tables[res_tb_id]->table_meta->tuple_num += 1;
							this->tables[res_tb_id]->table_meta->real_tuple_num += 1;
							this->storage_manager->Write(res_tb_id, res_tuple, res_tuple_size);
						} else {
							memcpy(res_tuple, tuple2, right_tuple_size);
							memcpy(res_tuple+right_tuple_size, tuple1, left_tuple_size);
							this->tables[res_tb_id]->table_meta->tuple_num += 1;
							this->tables[res_tb_id]->table_meta->real_tuple_num += 1;
							this->storage_manager->Write(res_tb_id, res_tuple, res_tuple_size);
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
					tuple2 = (char*)malloc(sizeof(char)*right_tuple_size);
					memcpy(tuple2, result1[j], right_tuple_size);
					char* res_tuple;
					res_tuple = (char*)malloc(sizeof(char)*res_tuple_size);
					if (!isReverse) {
						memcpy(res_tuple, tuple1, left_tuple_size);
						memcpy(res_tuple+left_tuple_size, tuple2, right_tuple_size);
						this->tables[res_tb_id]->table_meta->tuple_num += 1;
						this->tables[res_tb_id]->table_meta->real_tuple_num += 1;
						this->storage_manager->Write(res_tb_id, res_tuple, res_tuple_size);
					} else {
						memcpy(res_tuple, tuple2, right_tuple_size);
						memcpy(res_tuple+right_tuple_size, tuple1, left_tuple_size);
						this->tables[res_tb_id]->table_meta->tuple_num += 1;
						this->tables[res_tb_id]->table_meta->real_tuple_num += 1;
						this->storage_manager->Write(res_tb_id, res_tuple, res_tuple_size);
					}
					free(tuple2);
				}
				keys[0] = (char*)malloc(sizeof(char)*left_tuple_size);
				memcpy(keys[0], tuple1+left_table->table_meta->attr_meta[col1]->attribute_offset, left_table->table_meta->attr_meta[col1]->attribute_length);
				void* result2[4096];
				int num2 = this->SingleIndexJoin(right_tb_id, cols2[0], keys, operators[1], result2);
				for (int j = 0; j < num2; j++) {
					char* tuple2;
					tuple2 = (char*)malloc(sizeof(char)*right_tuple_size);
					memcpy(tuple2, result2[j], right_tuple_size);
					char* res_tuple;
					res_tuple = (char*)malloc(sizeof(char)*res_tuple_size);
					if (!isReverse) {
						memcpy(res_tuple, tuple1, left_tuple_size);
						memcpy(res_tuple+left_tuple_size, tuple2, right_tuple_size);
						this->tables[res_tb_id]->table_meta->tuple_num += 1;
						this->tables[res_tb_id]->table_meta->real_tuple_num += 1;
						this->storage_manager->Write(res_tb_id, res_tuple, res_tuple_size);
					} else {
						memcpy(res_tuple, tuple2, right_tuple_size);
						memcpy(res_tuple+right_tuple_size, tuple1, left_tuple_size);
						this->tables[res_tb_id]->table_meta->tuple_num += 1;
						this->tables[res_tb_id]->table_meta->real_tuple_num += 1;
						this->storage_manager->Write(res_tb_id, res_tuple, res_tuple_size);
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
			tuple1 = (char*)malloc(sizeof(char)*left_tuple_size);
			memcpy(tuple1, this->GetTuple(left_tb_id, i, left_tuple_size), left_tuple_size);
			char* keys[1];
			keys[0] = (char*)malloc(sizeof(char)*right_tuple_size);
			memcpy(keys[0], tuple1+left_table->table_meta->attr_meta[col1]->attribute_offset, right_tuple_size);
			if (operators[0] != nq) {
				void* tuples1[4096]; // result of condition 1
				int num = this->SingleIndexJoin(right_tb_id, cols2[0], keys, operators[0], tuples1);
				vector<int> cols;
				vector<OP> ops;
				for (int idx = 0; idx < cols1.size() - 1; idx++) {
					cols.insert((vector<int>::iterator)cols.begin()+idx, cols2[idx+1]);
					OP op1;
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
					ops.insert((vector<OP>::iterator)ops.begin()+idx, op1);
					if (operators[idx+1] == nq) {
						op1 = gt;
						ops.insert((vector<OP>::iterator)ops.begin()+idx+1, op1);
						cols.insert((vector<int>::iterator)cols.begin()+idx+1, cols2[idx+1]);
					}
				}
				char* other_keys[4];
				for (int idx = 1; idx < cols1.size(); idx++) {
					other_keys[idx-1] = (char*)malloc(sizeof(char)*left_tuple_size);
					memcpy(other_keys[idx-1], tuple1+left_table->table_meta->attr_meta[cols1[idx]]->attribute_offset, left_tuple_size);
				}
				for (int j = 0; j < num; j++) {
					if (this->CheckTuple(right_tb_id, (char*)tuples1[j], cols, ops, other_keys)) {
						// fit other conditions
						char* res_tuple;
						res_tuple = (char*)malloc(sizeof(char)*res_tuple_size);
						if (!isReverse) {
							memcpy(res_tuple, tuple1, left_tuple_size);
							memcpy(res_tuple+left_tuple_size, tuples1[j], right_tuple_size);
							this->tables[res_tb_id]->table_meta->tuple_num += 1;
							this->tables[res_tb_id]->table_meta->real_tuple_num += 1;
							this->storage_manager->Write(res_tb_id, res_tuple, res_tuple_size);
						} else {
							memcpy(res_tuple, tuples1[j], right_tuple_size);
							memcpy(res_tuple+right_tuple_size, tuple1, left_tuple_size);
							this->tables[res_tb_id]->table_meta->tuple_num += 1;
							this->tables[res_tb_id]->table_meta->real_tuple_num += 1;
							this->storage_manager->Write(res_tb_id, res_tuple, res_tuple_size);
						}
					}
				}
			}
		}

	}
	return res_tb_id;
}

bool TableManagement::IndexCartesianProduct(int left_tb_id, int right_tb_id, bool isReverse) {
	Table* left_table = this->tables[left_tb_id];
	Table* right_table = this->tables[right_tb_id];
	if (left_table->exist == false) {
		cout << "table " << left_tb_id << " does not exist" << endl;
		return false;
	}
	if (right_table->exist == false) {
		cout << "table " << right_tb_id << " does not exist" << endl;
		return false;
	}
	int left_tuple_size = left_table->table_meta->tuple_size;
	int right_tuple_size = right_table->table_meta->tuple_size;
	if (left_table->table_meta->tuple_num == 0 || right_table->table_meta->tuple_num == 0) {
		return false;
	}
	FILE* fout;
	fout = fopen("result_productindexjoin", "w");
	if (!fout)
		return false;

	for (int i = 0; i < left_table->table_meta->tuple_num; i++) {
		char* tuple1;
		tuple1 = (char*)malloc(sizeof(char)*left_tuple_size);
		memcpy(tuple1, this->GetTuple(left_tb_id, 1, left_tuple_size), left_tuple_size);

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
	return true;
}

int TableManagement::IndexCartesianProductTmp(int left_tb_id, int right_tb_id, bool isReverse) {
	Table* left_table = this->tables[left_tb_id];
	Table* right_table = this->tables[right_tb_id];
	if (left_table->exist == false) {
		cout << "table " << left_tb_id << " does not exist" << endl;
		return false;
	}
	if (right_table->exist == false) {
		cout << "table " << right_tb_id << " does not exist" << endl;
		return false;
	}
	int left_tuple_size = left_table->table_meta->tuple_size;
	int right_tuple_size = right_table->table_meta->tuple_size;
	if (left_table->table_meta->tuple_num == 0 || right_table->table_meta->tuple_num == 0) {
		return false;
	}

	// Tmp table
	time_t currtime = time(NULL);
	tm* p = localtime(&currtime);
	char filename[100] = {0};
	sprintf(filename,"tmp%d%d%02d%02d%02d%02d%02d",left_tb_id, right_tb_id,p->tm_mon+1,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
	int res_tuple_size = left_tuple_size + right_tuple_size;
	int left_attr_num = left_table->table_meta->attribute_num;
	int right_attr_num = right_table->table_meta->attribute_num;
	int attribute_num = left_attr_num + right_attr_num;
	char attr_names[16][MAX_ATTR_NAME_LENGTH];
	TYPE *types;
	int *attr_length;
	int *attr_offset;
	types = (TYPE*)malloc(sizeof(TYPE)*attribute_num);
	attr_length = (int*)malloc(sizeof(int)*attribute_num);
	attr_offset = (int*)malloc(sizeof(int)*attribute_num);
	int off = 0;
	if (!isReverse) {
		for (int i = 0; i < left_attr_num; i++) {
			strcpy(attr_names[i], left_table->table_meta->attr_meta[i]->attribute_name);
			types[i] = left_table->table_meta->attr_meta[i]->attribute_type;
			attr_length[i] = left_table->table_meta->attr_meta[i]->attribute_length;
			attr_offset[i] = off;
			off += attr_length[i];
		}
		off = left_tuple_size;
		for (int i = 0; i < right_attr_num; i++) {
			strcpy(attr_names[i+left_attr_num], right_table->table_meta->attr_meta[i]->attribute_name);
			types[i+left_attr_num] = right_table->table_meta->attr_meta[i]->attribute_type;
			attr_length[i+left_attr_num] = right_table->table_meta->attr_meta[i]->attribute_length;
			attr_offset[i+left_attr_num] = off;
			off += attr_length[i+left_attr_num];
		}
	} else {
		for (int i = 0; i < right_attr_num; i++) {
			strcpy(attr_names[i], right_table->table_meta->attr_meta[i]->attribute_name);
			types[i] = right_table->table_meta->attr_meta[i]->attribute_type;
			attr_length[i] = right_table->table_meta->attr_meta[i]->attribute_length;
			attr_offset[i] = off;
			off += attr_length[i];
		}
		off = right_tuple_size;
		for (int i = 0; i < left_attr_num; i++) {
			strcpy(attr_names[i+right_attr_num], left_table->table_meta->attr_meta[i]->attribute_name);
			types[i+right_attr_num] = left_table->table_meta->attr_meta[i]->attribute_type;
			attr_length[i+right_attr_num] = left_table->table_meta->attr_meta[i]->attribute_length;
			attr_offset[i+right_attr_num] = off;
			off += attr_length[i+right_attr_num];
		}
	}
	int res_tb_id = CreateTable(0, filename, res_tuple_size, attr_names, types, attr_length, attr_offset, attribute_num);

	for (int i = 0; i < left_table->table_meta->tuple_num; i++) {
		char* tuple1;
		tuple1 = (char*)malloc(sizeof(char)*left_tuple_size);
		memcpy(tuple1, this->GetTuple(left_tb_id, 1, left_tuple_size), left_tuple_size);

		char* keys[2];
		keys[0] = (char*)malloc(sizeof(char)*5);
		keys[0] = "!";
		keys[1] = (char*)malloc(sizeof(char)*10);
		keys[1] = "~~~~~~~~";
		void* result1[4096000];
		int num = this->SearchIndex(right_tb_id, 0, 2, keys, ge, le, result1);
		for (int j = 0; j < num; j++) {
			char* res_tuple;
			res_tuple = (char*)malloc(sizeof(char)*res_tuple_size);
			memcpy(res_tuple, tuple1, left_tuple_size);
			memcpy(res_tuple+left_tuple_size, result1[j], right_tuple_size);
			this->tables[res_tb_id]->table_meta->tuple_num += 1;
			this->tables[res_tb_id]->table_meta->real_tuple_num += 1;
			this->storage_manager->Write(res_tb_id, res_tuple, res_tuple_size);
		}
	}
	return res_tb_id;
}

Table::Table(char* name, int db_id, int index, int tuple_size, char attr_names[][MAX_ATTR_NAME_LENGTH], TYPE *types, int *attr_length, int attribute_num, ADDR start_addr) {
	this->db_id = db_id;
	this->index = index;
	this->start_addr = start_addr;
	this->exist = true;
	TableMeta* new_table_meta = new TableMeta();
	memcpy(new_table_meta->table_name, name, MAX_TABLE_NAME_LENGTH);
	strcpy(new_table_meta->data_file_path, data_dir);
	strcat(new_table_meta->data_file_path, name);
	strcat(new_table_meta->data_file_path, ".data");
	new_table_meta->db_id = db_id;
	new_table_meta->attribute_num = attribute_num;
	new_table_meta->tuple_size = tuple_size;
	int off = 0;
	for (int i = 0; i < attribute_num; i++) {
		std::string attr_name = attr_names[i];
		if (this->attr_map.count(attr_name) != 0) {
			cout << "ERROR: Attribute name exists" << endl;
			return;
		}
		this->attr_map.insert(pair<string, int>(attr_name, i));
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

Table::Table(char* name, int db_id, int index, int tuple_size, char attr_names[][MAX_ATTR_NAME_LENGTH], TYPE *types, int *attr_length, int* attribute_offset, int attribute_num, ADDR start_addr) {
	this->db_id = db_id;
	this->index = index;
	this->start_addr = start_addr;
	this->exist = true;
	TableMeta* new_table_meta = new TableMeta();
	memcpy(new_table_meta->table_name, name, MAX_TABLE_NAME_LENGTH);
	strcpy(new_table_meta->data_file_path, data_dir);
	strcat(new_table_meta->data_file_path, name);
	strcat(new_table_meta->data_file_path, ".data");
	new_table_meta->db_id = db_id;
	new_table_meta->attribute_num = attribute_num;
	new_table_meta->tuple_size = tuple_size;
	for (int i = 0; i < attribute_num; i++) {
		std::string attr_name = attr_names[i];
		if (this->attr_map.count(attr_name) != 0) {
			cout << "ERROR: Attribute name exists" << endl;
			return;
		}
		this->attr_map.insert(pair<string, int>(attr_name, i));
		AttributeMeta* new_attr_meta = new AttributeMeta();
		new_attr_meta->attribute_index = -1;
		strcpy(new_attr_meta->attribute_name, attr_names[i]);
		new_attr_meta->attribute_type = types[i];
		new_attr_meta->attribute_length = attr_length[i];
		new_attr_meta->attribute_offset = attribute_offset[i];
		new_table_meta->attr_meta.push_back(new_attr_meta);
	}
	this->table_meta = new_table_meta;
}

void Table::dump(){
	printf("table info:\n");
	fflush(stdout);
	this->table_meta->dump();
}

int Table::GetAttrId(char* attr_name) {
	std::string attribute_name = attr_name;
	map<string, int>::iterator iter;
	iter = this->attr_map.find(attribute_name);
	if (iter == this->attr_map.end()) {
		cout << "ERROR: Attribute name doesn't exist" << endl;
		return -1;
	}
	return iter->second;
}

void TableManagement::dump(){
	printf("table management info:\n");
	fflush(stdout);	
	for(vector<Table*>::iterator iter = (this->tables).begin(); iter != (this->tables).end(); iter ++){
		(*iter)->dump();
	}
}


#include "table.h"

TableManagement::TableManagement() {
	this->storage_manager = new StorageManagement();
	this->storage_manager->InitStorage("store.txt");
	this->tables = new vector<Table>();
	this->encoder = new Encoder();
}

TableManagement::TableManagement(char* db_name) {
	this->storage_manager = new StorageManagement();
	this->storage_manager->InitStorage(db_name);
	this->tables = new vector<Table>();
	this->encoder = new Encoder();
}
TableManagement::~TableManagement() {
	delete storage_manager;
	delete encoder;
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
		   while (!feof(fp1)) {
			   fgets(buf, sizeof(buf), fp);
			   char* input = (char*)calloc(sizeof(char)*MAX_TUPLE_SIZE+1, sizeof(char));
			   char seg1[] = "|";
			   char* substr1;
			   char* part;
			   int j = 0;
			   while (j < attribute_num) {
				   substr1 = strtok(buf, seg1);
				   encoder->encode(substr1, part, attr_length[j], types[j], attr_length[j]);
				   strcat(input, part);
			   }
			   this->storage_manager->Write(input, MAX_TUPLE_SIZE);
			   free(input);
		   }
		   Table new_table = new Table(tb_name, db_id, index, seg_id, start_addr, exist, types, attr_length, attribute_num);
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
	char result[MAX_TUPLE_SIZE];
	int re = this->storage_manager->ReadBuffer(this->tables[tb_id].start_addr+index*MAX_TUPLE_SIZE, result, MAX_TUPLE_SIZE);
	if (re != 0)
	{
		return result;
	}
	else {
		return NULL;
	}
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

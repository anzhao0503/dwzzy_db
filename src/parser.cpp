#include <malloc.h>
#include <iostream>
#include <string>
#include "../include/parser.h"
using namespace std;
using std::string;

extern SelectQuery* query;
extern DeleteQuery* delete_query;

extern int attr_count;
extern char* tb_name;
extern AttrInfo attr_list[MAX_ATTR_NUM];

extern int update_col_count;
extern UpdateQuery* update_query;

extern TableManagement* table_manager;

extern int cond_count;
extern Condition cond_list[MAX_COND_NUM];

bool isTableExists(string table_name){
	cout<<"Enter isTableExists."<<endl;
	TableMedata tmp_tb_meta;
	tmp_tb_meta = MetadataManager::getInstance()->get_tablemetadata(table_name);
	
	if(tmp_tb_meta.table_name == "")
	{
		cout<<"table not exist."<<endl;
		return false;
	}
	cout<<"table exists"<<endl;
	return true;
}

bool insertIntoTableMeta(){
	string tmp_tb_name(tb_name);
	/*
	 if table already exists, error.
	 */
	if(isTableExists(tmp_tb_name)){
		cout<<"Table "<<tmp_tb_name<<" has already existed. updateTableMeta() Error."<<endl;
		return "";
	}
	TableMedata tmp_tb_meta;
	tmp_tb_meta.table_name = tmp_tb_name;
	tmp_tb_meta.table_attr_num = attr_count;
	for(int i = 0; i < attr_count; i++){
		tmp_tb_meta.Attr[i].attr_name = attr_list[i].attr_name;
		tmp_tb_meta.Attr[i].attr_datatype = attr_list[i].type;
		tmp_tb_meta.Attr[i].attr_length = attr_list[i].used_size;
		cout<<"insertIntoTableMeta COPY "<< tmp_tb_meta.Attr[i].attr_name<<tmp_tb_meta.Attr[i].attr_datatype<<tmp_tb_meta.Attr[i].attr_length<<endl;
	}

	MetadataManager::getInstance()->set_tablemetadata(tmp_tb_meta);
	cout<<"SET META."<<endl;
	return true;
}

int ExecCreate(){
	char attr_names[16][MAX_ATTR_NAME_LENGTH];
	TYPE *types;
	int *attr_length;
	int attribute_num = attr_count;
	attr_length = (int*)malloc(sizeof(int)*attribute_num);
	types = (TYPE*)malloc(sizeof(TYPE)*attribute_num);
	for(int i = 0; i<attr_count;i++){
		strcpy(attr_names[i],attr_list[i].attr_name);
		types[i] = attr_list[i].type;
		attr_length[i] = attr_list[i].used_size;
	}
	insertIntoTableMeta();
	table_manager->CreateTable(0, tb_name, MAX_TUPLE_SIZE, attr_names, types, attr_length,  attribute_num);
}

bool deleteFromMeta(string tb_name){
	TableMedata tmp_tb_meta;
	MetadataManager::getInstance()->delete_tablemetadata(tb_name);
	return true;
}

bool ExecDelete(){
	int tb_id = table_manager->GetTableId(tb_name);
	vector<int> cols;
	vector<OP> operators;
	char* keys[cond_count];
	for(int i = 0; i < cond_count; i++){
		int col_id = table_manager->tables[tb_id]->GetAttrId(delete_query->CondList[i].col_name);
		cols.push_back(col_id);
		keys[i] = (char*)malloc(sizeof(char)*256);
		memcpy(keys[i], delete_query->CondList[i].value, sizeof(delete_query->CondList[i].value));
		operators.push_back(delete_query->CondList[i].op);
	}
	return table_manager->Delete(tb_id, cols, operators, keys);
	
}
int ExecProject() {
		return 0;
}
bool ExecUpdate(){
	int tb_id = table_manager->GetTableId(update_query->tb_name);
	int col_id;
	vector<int> up_cols;
	vector<int> cols;
	char* keys[cond_count];
	vector<OP> operators;
	cout<<"cond_count "<<cond_count<<" update_col_count " << update_col_count<<endl;
	for(int i = 0; i < update_col_count; i++){
		col_id = table_manager->tables[tb_id]->GetAttrId(update_query->col_name[i]);
		up_cols.push_back(col_id);
		cout<<"col i "<< update_query->col_value[i]<<endl;
	}
	for(int i = 0; i < cond_count; i++){
		col_id = table_manager->tables[tb_id]->GetAttrId(update_query->CondList[i].col_name);
		cols.push_back(col_id);
		keys[i] = (char*)malloc(sizeof(char)*256);
		memcpy(keys[i], update_query->CondList[i].value, sizeof(update_query->CondList[i].value));
		operators.push_back(update_query->CondList[i].op);
		cout<<"cond i "<< keys[i]<<endl;
	}	
	return table_manager->Update(tb_id, up_cols, update_query->col_value, cols, operators, keys);
}

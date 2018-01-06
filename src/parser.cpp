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
/*enum OP{
	eq,nq,lt,le,gt,ge
};
*/
string GetTypeString(OP op_type){
	string type_string = " ";
	switch(op_type){
		case eq:
			type_string += "= ";
			break;
		case ge:
			type_string += ">= ";
			break;
		case gt:
			type_string +=	"> ";
			break;
		case le:
			type_string += "<= ";
			break;
		case lt:
			type_string += "< ";
			break;
		case nq:
			type_string += "!= ";
			break;
		default:
			cout<<"Invalid Operator!"<<endl;
			return "";
	}
	return type_string;
}

string GetVTypeString(TYPE type, int i){
	string tmp_string;
	if(type == 1)
		return "INTEGER";
	if(type == C){
		tmp_string = "CHAR";
		tmp_string = tmp_string+ "("+std::to_string(attr_list[i].used_size)+")";
		return tmp_string;
	}
	if(type == V){
		tmp_string = "VARCHAR";
		tmp_string = tmp_string+ "("+std::to_string(attr_list[i].used_size)+")";
		return tmp_string;
	}
	if(type == F){
		tmp_string = "FLOAT";
		tmp_string = tmp_string+ "("+std::to_string(attr_list[i].used_size)+")";
		return tmp_string;
	}
	if(type == D)
		return "DATE";
}

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
bool deleteFromMeta(string tb_name){
	TableMedata tmp_tb_meta;
	MetadataManager::getInstance()->delete_tablemetadata(tb_name);
	return true;
}

string spliceCreateStmt(){
	if((attr_count == 0) || (tb_name ==NULL)){
		cout<<"spliceCreateStmt error"<<endl;
		return "";
	}
	string tmp_stmt;
	tmp_stmt = "CREATE TABLE ";
	tmp_stmt.append(tb_name);
	tmp_stmt.append("(");
	tmp_stmt.append(attr_list[0].attr_name);
	tmp_stmt.append(" ");
	string type_string = GetVTypeString(attr_list[0].type,0);
	tmp_stmt.append(type_string);
	for (int i = 1; i < attr_count; i++)
	{
		tmp_stmt.append(", ");
		tmp_stmt.append(attr_list[i].attr_name);
		tmp_stmt.append(" ");
		string type_string = GetVTypeString(attr_list[i].type,i);
		tmp_stmt.append(type_string);
	}
	tmp_stmt.append(" );");
	cout << tmp_stmt << endl;
	return tmp_stmt;

}
string spliceDropStmt(){
	cout<<"spliceDropStmt"<<endl;
	if(NULL == tb_name){
		cout << "spliceDropStmt error"<<endl;
		return "";
	}
	string tmp_stmt;
	tmp_stmt = "DROP TABLE ";
	tmp_stmt.append(tb_name);
	tmp_stmt.append(";");
	cout<<tmp_stmt<<endl;
	return tmp_stmt;
}

string spliceCondStmt(int cond_count, Condition* cond_list){
	if((cond_count == 0)|(NULL == cond_list))
		return "";
	string cond_stmt = " WHERE ";
	// if(cond_list[0].tb_name != ""){
	// 	cout<<"ok"<<endl;
	// 	cond_stmt.append(cond_list[0].tb_name);
	// 	cond_stmt += ".";
	// }
	cond_stmt.append(cond_list[0].col_name);
	string type_string = GetTypeString(cond_list[0].op);
	cond_stmt.append(type_string);
	cond_stmt.append(cond_list[0].value);
	for(int i = 1;i < cond_count;i++){
		cond_stmt.append(" AND ");
		// if(cond_list[i].tb_name != ""){
		// 	cout<<"ok"<<endl;
		// 	cond_stmt.append(cond_list[i].tb_name);
		// 	cond_stmt += ".";
		// }
		cond_stmt.append(cond_list[i].col_name);
		string type_string = GetTypeString(cond_list[i].op);
		cond_stmt.append(type_string);
		cond_stmt.append(cond_list[i].value);
	}
	return cond_stmt;
}
string spliceDeleteStmt(){
	if(NULL == delete_query){
		cout<<"spliceDeleteStmt error. no delete stmt."<<endl;
		return "";
	}
	string tmp_stmt = "DELETE FROM ";
	tmp_stmt.append(delete_query->tb_name);
	/*
		slpice cond_list same as where_cond in select.
	 */
	string cond_stmt = spliceCondStmt(delete_query->cond_count,delete_query->CondList);
	if(cond_stmt != "")
		tmp_stmt.append(cond_stmt);
	tmp_stmt.append(";");
	cout<< tmp_stmt <<endl;
	return tmp_stmt;
}

string spliceUpdateStmt(){	
	if((NULL == update_query)|(update_query->col_count ==0)){
		cout<<"spliceUpdateStmt error. no update stmt."<<endl;
		return "";
	}
	string tmp_stmt = "UPDATE ";
	string tmp_tb_name(update_query->tb_name);
	tmp_stmt.append(tmp_tb_name);
	tmp_stmt += " SET ";
	tmp_stmt.append(update_query->col_name[0]);
	tmp_stmt += " = ";
	tmp_stmt.append(update_query->col_value[0]);
	for(int i = 1; i < update_query->col_count; i++){
		tmp_stmt += ", ";
		tmp_stmt.append(update_query->col_name[i]);
		tmp_stmt += " = ";
		tmp_stmt.append(update_query->col_value[i]);
				
	}
	string cond_stmt = spliceCondStmt(update_query->cond_count,update_query->CondList);
	tmp_stmt += cond_stmt;
	tmp_stmt += ";";
	return tmp_stmt;
}

string spliceSelectStmt(){
		cout<<"spliceSelectStmt"<<endl;
		if(NULL == query){
			cout<<"spliceSelectStmt error"<<endl;
			return "";
		}
		string tmp_stmt;

		tmp_stmt = string("SELECT ");
		//cout<<tmp_stmt<<endl;
		if(query->all == 1)
			tmp_stmt.append("* ");
		if(query->sel_count!=0){
			for(int i = 0; i<query->sel_count-1;i++){
				if(query->SelList[i].table_name!= NULL){
					tmp_stmt.append(query->SelList[i].table_name);
					tmp_stmt += ".";
				}
				tmp_stmt.append(query->SelList[i].col_name);
				tmp_stmt.append(", ");
			}
			tmp_stmt.append(query->SelList[query->sel_count-1].col_name);
			//cout<<tmp_stmt<<endl;
		}
		tmp_stmt.append(" INTO OUTFILE '/var/lib/mysql-files/select_results' FIELDS TERMINATED BY '\t'");
		tmp_stmt.append(" FROM ");
		tmp_stmt.append(query->FromList[0].tb_name);
		for(int i = 1; i < query->from_count; i++){
			tmp_stmt.append(", ");
			tmp_stmt.append(query->FromList[i].tb_name);
		}
		string cond_stmt = spliceCondStmt(query->cond_count,query->CondList);
		if(cond_stmt != "")
			tmp_stmt.append(cond_stmt);
		tmp_stmt.append(";");
		cout<<tmp_stmt<<endl;
		return tmp_stmt;
}

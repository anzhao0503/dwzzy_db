/*
 * parser.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: wcw
 *	
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <unistd.h>
#include <mysql/mysql.h>
#include "../include/parser.h"


using namespace std;
#define MAX_BUF_SIZE 1024

MYSQL *mysql_conn;
MYSQL_RES *res;
MYSQL_FIELD *fd;
MYSQL_ROW row;

extern char* tb_name;
const char *pHostName = "localhost";
const char *pUserName = "root";
const char *pPassword = " ";
const char *pDbName = "foo";
const unsigned int iDbPort = 3306;

const char* result_data_path = "/var/lib/mysql-files/select_results";


void finish_with_error(const char* msg){
	if(msg)
		cout<<"Error message "<<msg<<" : "<<mysql_error(mysql_conn)<<"."<<endl;
	else
		cout<<"Error message "<<mysql_error(mysql_conn)<<"."<<endl;
	mysql_close(mysql_conn);
	exit(-1);
}
int exe_sql(const char *sql){
	cout<<"exe_sql"<<endl;
	cout<<sql<<endl;
	int ret = mysql_real_query(mysql_conn,sql,strlen(sql));
	cout<<"ret"<<ret<<endl;
	if(ret)
		return -1;
	return 0;
}
int init_mysql(){
	mysql_conn = mysql_init(NULL);
	if(mysql_conn == NULL)
		return -1;
	if(!mysql_real_connect(mysql_conn,pHostName,pUserName,pPassword,pDbName,iDbPort,NULL,0))
		return -2;
	if(exe_sql("set names utf8"))
		return -3;
	return 0;
}
/*
	execute LOAD sql.
 */
int load_data(string tb_name){
	cout<<"load_data"<<endl;
	if(init_mysql())
		finish_with_error(NULL);
	string file_name = "'/var/lib/mysql-files/benchmark_data/"+tb_name+".tbl'";
	string load_stmt = "LOAD DATA INFILE "+ file_name +" INTO TABLE " + tb_name + " FIELDS TERMINATED BY '|' LINES TERMINATED BY '\\n'";
	const char* cLoadData = load_stmt.c_str();
	cout<<"cLoadData is "<<cLoadData<<endl;
	//cout<<"load_data end"<<endl;
	if(exe_sql(cLoadData))
		finish_with_error(NULL);
	mysql_close(mysql_conn);
	return 0;
}

string readFile(string filename){
	cout<<"enter readFile"<<endl;
	ifstream infile(filename, std::ios::in);
	cout << "Reading filename "<<filename<<endl;
	ostringstream os_buf;
	char buffer[1024];
	while(!infile.eof()){
		//cout<<"infile"<<endl;
		infile.getline(buffer,1024);
		//cout<<"buffer"<<buffer<<endl;
		os_buf << buffer;
		os_buf << "\n";
	}
	string result = os_buf.str();
	result.erase(result.size()-1, 1);
	return result;
}

void exec_select_stmt(){
	cout<<"exec_select_stmt"<<endl;
	string tmp_c_sql_stmt = spliceSelectStmt();
	const char* c_sql_stmt = tmp_c_sql_stmt.c_str();	
	if(access(result_data_path,F_OK)!=-1)
		remove(result_data_path);
	if(init_mysql())
		finish_with_error(NULL);
	if(exe_sql(c_sql_stmt))
		finish_with_error(NULL);
	mysql_close(mysql_conn);
	string result = readFile(result_data_path);
	cout<<"select results:\n"<<result<<endl;
	remove(result_data_path);
	return;
}
void exec_create_stmt(){
	cout<<"executing create sql....."<<endl;
	// if(!checkIsCStmtValid())
	// 	return;
	string tmp_c_sql_stmt = spliceCreateStmt();
	const char* c_sql_stmt = tmp_c_sql_stmt.c_str();
	if(c_sql_stmt == ""){
		cout<<"Create Error."<<endl;
		return;
	}
	if(init_mysql())
		finish_with_error(NULL);
	if(exe_sql(c_sql_stmt))
		finish_with_error(NULL);
	mysql_close(mysql_conn);

	cout<<"Updating Metadata Config....."<<endl;
	insertIntoTableMeta();
	cout<<"New Metadata Inserted!"<<endl;
	return;
}
void exec_drop_table_stmt(){
	cout<<"executing drop_table sql....."<<endl;
	// if(!checkIsDtStmtValid())
	// 	return;
	string tmp_c_sql_stmt = spliceDropStmt();
	const char* c_sql_stmt = tmp_c_sql_stmt.c_str();
	if(init_mysql())
		finish_with_error(NULL);
	if(exe_sql(c_sql_stmt))
		finish_with_error(NULL);
	mysql_close(mysql_conn);
	string table_name = tb_name;
	cout<<"deleteFromMeta "<< table_name<<endl;
	deleteFromMeta(table_name);
	return;
}
void exec_insert_stmt(){
	cout<<"executing insert sql....."<<endl;
	string tmp_c_sql_stmt = spliceInsertStmt();
	const char* c_sql_stmt = tmp_c_sql_stmt.c_str();
	if(c_sql_stmt == ""){
		cout<<"Insert Error."<<endl;
		return;
	}
	if(init_mysql())
		finish_with_error(NULL);
	if(exe_sql(c_sql_stmt))
		finish_with_error(NULL);
	mysql_close(mysql_conn);
	return;
}
void exec_delete_stmt(){
	cout<<"exec_delete_stmt"<<endl;
	// if(!checkIsDStmtValid())
	// 	return;
	string tmp_c_sql_stmt = spliceDeleteStmt();
	const char* c_sql_stmt = tmp_c_sql_stmt.c_str();
	cout<<"c_sql_stmt    "<<c_sql_stmt<<endl;
	if(init_mysql())
		finish_with_error(NULL);
	if(exe_sql(c_sql_stmt))
		finish_with_error(NULL);
	mysql_close(mysql_conn);
	return;
}
void exec_update_stmt(){
	cout<<"exec_update_stmt"<<endl;
	/*if(!checkIsUStmtValid())
		return;*/
	string tmp_c_sql_stmt = spliceUpdateStmt();
	const char* c_sql_stmt = tmp_c_sql_stmt.c_str();
	cout<<"c_sql_stmt    "<<c_sql_stmt<<endl;
	if(init_mysql())
		finish_with_error(NULL);
	if(exe_sql(c_sql_stmt))
		finish_with_error(NULL);
	mysql_close(mysql_conn);
	return;
}

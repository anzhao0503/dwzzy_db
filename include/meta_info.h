/*
 * meta_info.h
 *
 *  Created on: Nov 15, 2017
 *      Author: anzhao
 */

#ifndef META_INFO_H_
#define META_INFO_H_

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "../include/storage.h"

#define MAX_TABLE_NAME_LENGTH 20
#define MAX_ATTR_NAME_LENGTH 20
#define MAX_DB_NUM 30
#define MAX_TABLE_NUM 30
#define MAX_ATTR_NUM 20

using namespace std;

enum TYPE{
	I=1,C,V,F,D
};
enum OP{
	eq,nq,lt,le,gt,ge
};

//enum AttrType {
//	INTEGER,
//	FLOAT,
//	CHAR,
//	VARCHAR,
//	DATE
//};

class AttributeMeta {
public:
	char attribute_name[MAX_ATTR_NAME_LENGTH];
	TYPE attribute_type;
	int attribute_length;
	int attribute_index;
	int attribute_offset;
	void dump();
	AttributeMeta() {
		attribute_type = I;
		attribute_index = -1;
		attribute_length = 0;
		attribute_offset = 0;
	}
};

class TableMeta {
public:
	char table_name[MAX_TABLE_NAME_LENGTH];
	int db_id;
	ADDR start_addr;
	int attribute_num;
	int tuple_num;
	int real_tuple_num;
	int tuple_size;
	char data_file_path[128];
	vector<AttributeMeta*> attr_meta;
	void dump();
	AttributeMeta* GetAttributeMeta(int attr_index);
	TableMeta() {
		db_id = -1;
		start_addr = -1;
		attribute_num = 0;
		tuple_size = MAX_TUPLE_SIZE;
		tuple_num = 0;
		real_tuple_num = 0;
	}
};

class DBMeta {
public:
	ADDR seg_id;
	int table_num;
	vector<TableMeta*> table_meta;
	DBMeta() {
		seg_id = -1;
		table_num = 0;
	}
	~DBMeta() {
	}
};

class MetaInfo {
public:
	int db_num;
	vector<DBMeta*> db_meta;
	MetaInfo() {
		db_num = 0;
	}
	~MetaInfo() {
	}
};

int TypeMalloc(void*& p, TYPE t, int len);
// global variable
extern MetaInfo* meta_info;
#endif /* META_INFO_H_ */

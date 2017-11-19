/*
 * meta_info.cpp
 *
 *  Created on: Nov 15, 2017
 *      Author: anzhao
 */
# include "meta_info.h"

MetaInfo::MetaInfo() {
	db_meta = new DBMeta();
}

MetaInfo::~MetaInfo() {
	delete db_meta;
}

int TypeMalloc(void*& p, AttrType t, int len = 0){
	switch(t){
		case INTEGER:
			p = (int64_t*)malloc(sizeof(int64_t));
			break;
		case FLOAT:
			p = (float*)malloc(sizeof(float));
			break;
		case DATE:
			p = (int64_t*)malloc(sizeof(int64_t));
			break;
		case CHAR:
			p = (char*)malloc(sizeof(char)*len);
			break;
		case VARCHAR:
			p = (char*)malloc(sizeof(char)*len);
	}
	return 0;
}

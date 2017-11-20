#include "meta_info.h"

MetaInfo* meta_info = new MetaInfo();
int TypeMalloc(void*& p, AttrType t, int len){
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

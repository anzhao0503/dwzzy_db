#include "../include/meta_info.h"

MetaInfo* meta_info = new MetaInfo();
void AttributeMeta::dump(){
	printf("attribute info:\n");
	printf("name:%s\n", this->attribute_name);
	printf("type:%d\n", this->attribute_type);
	printf("length:%d\n", this->attribute_length);
	printf("index:%d\n", this->attribute_index);
	printf("offset:%d\n", this->attribute_offset);
	fflush(stdout);
}
void TableMeta::dump(){
	printf("table_meta info:\n");
	printf("name:%s\n", this->table_name);
	printf("attr_num:%d\n", this->attribute_num);
	printf("data_file_path:%s\n", this->data_file_path);
	for(vector<AttributeMeta*>::iterator iter = (this->attr_meta).begin(); iter != (this->attr_meta).end(); iter ++){
		(*iter)->dump();
	}
	fflush(stdout);
}

AttributeMeta* TableMeta::GetAttributeMeta(int attr_index){
	vector<AttributeMeta*>::iterator iter;
	int i = 0;
	for(iter = (this->attr_meta).begin(); i != attr_index; i++, iter ++){}
	return (*iter);
}

int TypeMalloc(void*& p, TYPE t, int len){
	switch(t){
		case I:
			p = (int64_t*)malloc(sizeof(int64_t));
			break;
		case F:
			p = (float*)malloc(sizeof(float));
			break;
		case D:
			p = (int64_t*)malloc(sizeof(int64_t));
			break;
		case C:
			p = (char*)malloc(sizeof(char)*len);
			break;
		case V:
			p = (char*)malloc(sizeof(char)*len);
	}
	return 0;
}

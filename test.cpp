#include "table.h"

int main() {
	char* tb_name = "../../db_data/supplier.tbl.data";
	TableManagement* table_manager = new TableManagement(tb_name);
	table_manager->InitTable("supplier.tbl", 0, 0 ,false);
	char* buf;
	buf = (char*)malloc(sizeof(char)*PAGE_SIZE);
	table_manager->storage_manager->ReadBuffer(1, buf, PAGE_SIZE);
	cout<<buf<<endl;
	return 0;
}

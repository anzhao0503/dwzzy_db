#include "table.h"

int main() {
	char* tb_name = "supplier.tbl.data";
	TableManagement* table_manager = new TableManagement(tb_name);
	table_manager->InitTable(tb_name, 0, 0 ,false);
	int num = 0;
	int tuple_num = 10000;
	ADDR address = tuple_num * PAGE_SIZE;
	for (ADDR addr = 0; addr < address; addr += BLOCK_SIZE * PAGE_SIZE)
	{
		char* buf[BLOCK_SIZE];
		for (int i = 0; i < BLOCK_SIZE; i++) {
			buf[i] = (char*)malloc(sizeof(char)*PAGE_SIZE);
		}
		table_manager->storage_manager->ReadBlock(addr, buf, BLOCK_SIZE*PAGE_SIZE);

		for (int i = 0; i < BLOCK_SIZE; i++) {
			if (num < tuple_num / 8) {
				cout << (char*)buf[i] << endl;
				num += 1;
			}
		}

//		free(buf);
	}
	return 0;
}

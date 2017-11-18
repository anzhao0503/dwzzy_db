#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "storage.h"
#include "meta_info.h"
#include "bpt.h"
#include "linear_hash.h"
#include "encoder.cpp"
#include "predefined.h"
#include <vector>

typedef int value_t;
enum Operator {
	eq,
	nq,
	lt,
	le,
	gt,
	ge
};

class TableManagement {
public:
	StorageManagement* storage_manager;
	vector<Table> tables;
	TableManagement();
	TableManagement(char* db_name);
	~TableManagement();
	int InitTable(char* tb_name, int db_id, int index, bool exist);

	char* GetTuple(int tb_id, int index); // get tuple by index of table
	char* GetTuple(int tb_id, ADDR addr, int tmp); // get tuple by address

	int CreateIndex(int tb_id, int col);
	int SearchIndex(FILE* fout, int tb_id, int col, char* keys[]);

	int GetCmpCondition(vector<int> cols, vector<Operator> operators, char* keys[], char*& low, char*& high);

	bool TableScan(int tb_id);
	bool SingleSelect(int tb_id, vector<int> cols, vector<Operator> operators, char* keys[]); // four types of select with one column
	bool MultiSelect(int tb_id, int condition_num, vector<int> cols, vector<Operator> operators, char* keys[]);
	bool ESelect(int tb_id, int col, key_t key); // equal or non-equal
	bool RangeSelect(int tb_id, int col, key_t left, key_t right); // range select

	bool Project(int tb_id, vector<int> cols);
	bool Project(FILE* fout, int tb_id, vector<int> cols);

	bool LoopJoin(char* left_tb_name, Table* right_tb_name, vector<int> cols); // equal an non-equal
	bool SortJoin(char* left_tb_name, Table* right_tb_name, vector<int> cols); // equal an non-equal
	bool HashJoin(char* left_tb_name, Table* right_tb_name, vector<int> cols); // equal an non-equal
	bool IndexJoin(char* left_tb_name, Table* right_tb_name, vector<int> cols); // equal an non-equal
	bool ThreeJoin(char* tb_name_1, char* tb_name_2, char* tb_name_3, vector<int> cols);
	bool ProductLoopJoin(char* left_tb_name, Table* right_tb_name,);
	bool ProductIndexJoin(char* left_tb_name, Table* right_tb_name,);
};

class Table {
public:
	int db_id; // database id
	ADDR start_addr;
	int index; // index in segment
	TableMeta *table_meta;
	Table();
	Table(char* name, int db_id, int index, ADDR seg_id, ADDR start_addr, bool exist, AttrType *types, int *attr_length, int attribute_num);
	~Table();

	bool TableScan();
	bool IndexScan();

	bool Select(vector<int> cols, vector<Operator> operators, vector<key_t> keys); // four types of select
	bool TotalSelect();
	bool ESelect(int col, key_t key); // equal or non-equal
	bool RangeSelect(int col, key_t left, key_t right); // range select

	bool Project(StorageManagement* storage_manager, vector<int> cols);

	bool LoopJoin(Table* right_table, vector<int> cols); // equal an non-equal
	bool SortJoin(Table* right_table, vector<int> cols); // equal an non-equal
	bool HashJoin(Table* right_table, vector<int> cols); // equal an non-equal
	bool IndexJoin(Table* right_table, vector<int> cols); // equal an non-equal
	bool ThreeJoin(Table* table_2, Table* table_3, vector<int> cols);
	bool ProductLoopJoin(Table* right_table);
	bool ProductIndexJoin(Table* right_table);
};

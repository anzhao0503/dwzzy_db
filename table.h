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
	int SearchIndex(FILE* fout, int tb_id, int col, char* keys[], Operator left_op, Operator right_op); // Index select

	int GetCmpCondition(vector<int> cols, vector<Operator>& operators, char* keys[], char*& low, char*& high);
	bool CheckTuple(int tb_id, char* tuple, vector<int> cols, vector<Operator> operators, char* keys[]);
	bool TableScan(int tb_id);
	bool Select(int tb_id, vector<int> cols, vector<Operator> operators, char* keys[]); // four types of select with one column

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
};

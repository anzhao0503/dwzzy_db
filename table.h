#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "bpt.h"
#include "predefined.h"
#include <vector>
#include <math.h>
#include "encoder.h"

#define EPSILON 0.00000001
#define BLOCK_SIZE 4*1024*1024
#define BLOCK_NUM 32
#define TUPLE_SIZE 512
#define OUTPUT_BUF_SIZE 32*1024
typedef unsigned long long value_t;
class Table {
public:
	int db_id; // database id
	ADDR start_addr;
	int index; // index in segment
	TableMeta *table_meta;
	Table();
	Table(char* name, int db_id, int index, char attr_names[][MAX_ATTR_NAME_LENGTH], AttrType *types, int *attr_length, int attribute_num, ADDR start_addr);
	~Table();
	void dump();
};

class TableManagement {
public:
	StorageManagement* storage_manager;
	vector<Table*> tables;
	TableManagement();
	TableManagement(vector<char*> tb_names);
	~TableManagement();
	void dump();
	int InitTable(char* tb_name, int db_id, int index, bool exist);

	char* GetTuple(int tb_id, int index); // get tuple by index of table
	char* GetTuple(int tb_id, ADDR addr, int tmp); // get tuple by address

	int CreateIndex(int tb_id, int col);
	int SearchIndex(FILE* fout, int tb_id, int col, int condition_num, char* keys[], Operator left_op, Operator right_op); // Index select
	int SearchIndex(int tb_id, int col, int condition_num, char* keys[], Operator left_op, Operator right_op, void* result[]);

	int GetCmpCondition(vector<int> cols, vector<Operator>& operators, char* keys[], char* &low, char* &high);
	bool CheckTuple(int tb_id, char* tuple, vector<int> cols, vector<Operator> operators, char* keys[]);
	bool TableScan(int tb_id);
	bool IndexScan(int tb_id);
	bool Select(int tb_id, vector<int> cols, vector<Operator> operators, char* keys[]); // four types of select with one column

	bool Project(int tb_id, vector<int> cols);
	bool Project(FILE* fout, int tb_id, vector<int> cols);

	bool NestedLoopJoin(int left_tb_id, int right_tb_id, vector<int> cols1, vector<int> cols2, vector<Operator> operators, bool isReverse);
	bool NestedLoopCartesianProduct(int left_tb_id, int right_tb_id, bool isReverse);
	bool SortJoin(int left_tb_id, int right_tb_id, vector<int> cols); // equal
	bool HashJoin(int left_tb_id, int right_tb_id, vector<int> cols); // equal

	int SingleIndexJoin(int right_tb_id, int col2, char* keys[], Operator op, void* result[]);
	bool IndexJoin(int left_tb_id, int right_tb_id, vector<int> cols1, vector<int> cols2, vector<Operator> operators, bool isReverse); // equal and non-equal
	int IndexCartesianProduct(int left_tb_id, int right_tb_id, bool isReverse);
	bool ThreeJoin(int tb_id_1, int tb_id_2, int tb_id_3, vector<int> cols);

	// not use now
	TableMeta* GetTableMeta(int table_index);
	int CartesianProduct(int* table_indexs);
	int Join(int* table_indexs, int* attr_indexs, bool equal_flag);
};



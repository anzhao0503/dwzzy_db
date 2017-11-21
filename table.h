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

typedef int value_t;
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

class TableManagement {
public:
	StorageManagement* storage_manager;
	vector<Table*> tables;
	TableManagement();
	TableManagement(char* db_name);
	~TableManagement();
	int InitTable(char* tb_name, int db_id, int index, bool exist);

	char* GetTuple(int tb_id, int index); // get tuple by index of table
	char* GetTuple(int tb_id, ADDR addr, int tmp); // get tuple by address

	int CreateIndex(int tb_id, int col);
	int SearchIndex(FILE* fout, int tb_id, int col, char* keys[], Operator left_op, Operator right_op); // Index select
	bool GetTupleIndex(int tb_id, int col, char* keys[], Operator left_op, Operator right_op, char* result[]);

	int GetCmpCondition(vector<int> cols, vector<Operator>& operators, char* keys[], char* low, char* high);
	bool CheckTuple(int tb_id, char* tuple, vector<int> cols, vector<Operator> operators, char* keys[]);
	bool TableScan(int tb_id);
	bool IndexScan(int tb_id);
	bool Select(int tb_id, vector<int> cols, vector<Operator> operators, char* keys[]); // four types of select with one column

	bool Project(int tb_id, vector<int> cols);
	bool Project(FILE* fout, int tb_id, vector<int> cols);

	bool LoopJoin(int left_tb_id, int right_tb_id, vector<int> cols); // equal and non-equal
	bool SortJoin(int left_tb_id, int right_tb_id, vector<int> cols); // equal
	bool HashJoin(int left_tb_id, int right_tb_id, vector<int> cols); // equal
	bool SingleIndexJoin(int right_tb_id, int col2, char* keys[], Operator op, char* result[]);
	bool IndexJoin(int left_tb_id, int right_tb_id, vector<int> cols1, vector<int> cols2, vector<Operator> operators, bool isReverse); // equal and non-equal
	bool ThreeJoin(int tb_id_1, int tb_id_2, int tb_id_3, vector<int> cols);
	bool ProductLoopJoin(int left_tb_id, int right_tb_id);
	bool ProductIndexJoin(int left_tb_id, int right_tb_id);
};



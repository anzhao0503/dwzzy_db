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
#define BLOCK_NUM 32
#define TUPLE_SIZE 512
#define OUTPUT_BUF_SIZE 32*1024
typedef unsigned long long value_t;
class Table {
public:
	int db_id; // database id
	ADDR start_addr;
	int index; // index in segment
	bool exist; // true for exist
	TableMeta *table_meta;
	Table();
	Table(char* name, int db_id, int index, int tuple_size, char attr_names[][MAX_ATTR_NAME_LENGTH], TYPE *types, int *attr_length, int attribute_num, ADDR start_addr);
	Table(char* name, int db_id, int index, int tuple_size, char attr_names[][MAX_ATTR_NAME_LENGTH], TYPE *types, int *attr_length, int* attribute_offset, int attribute_num, ADDR start_addr);
	~Table();
	void dump();
	int GetAttrId(char* attr_name);
	map<string, int> attr_map;
};

class TableManagement {
public:
	StorageManagement* storage_manager;
	vector<Table*> tables;
	TableManagement();
	TableManagement(vector<char*> tb_names);
	~TableManagement();
	void dump();

	char* GetTuple(int tb_id, int index, int tuple_size = MAX_TUPLE_SIZE); // get tuple by index of table
	char* GetTuple(int tb_id, ADDR addr, int tuple_size, int tmp); // get tuple by address

	char* GetPage(int tb_id, int index, ADDR &virtual_addr); // get page by tuple index of table

	int GetTableId(char* tb_name);
	string GetTableName(int tb_id);
	int InitTable(char* tb_name, int db_id);
	// return tb_id
	int CreateTable(int db_id, char* tb_name, int tuple_size, char attr_names[][MAX_ATTR_NAME_LENGTH], TYPE *types, int *attr_length, int attribute_num);
	int CreateTable(int db_id, char* tb_name, int tuple_size, char attr_names[][MAX_ATTR_NAME_LENGTH], TYPE *types, int *attr_length, int* attribute_offset, int attribute_num);
	bool DropTable(char* tb_name);

	bool Insert(int tb_id, vector<int> cols, char* values[]);
	bool Update(int tb_id, vector<int> up_cols, char* up_keys[], vector<int> cols, vector<OP> operators, char* keys[]);
	bool Delete(int tb_id, vector<int> cols, vector<OP> operators, char* keys[]);

	int CreateIndex(int tb_id, int col);
	int UpdateIndex(int tb_id, int col, char* key, value_t value);
	int RemoveIndex(int tb_id, int col, char* key);
	int InsertIndex(int tb_id, int col, char* key, value_t value);
	int SearchIndex(FILE* fout, int tb_id, int col, int condition_num, char* keys[], OP left_op, OP right_op); // Index select
	int SearchIndex(int res_tb_id, int tb_id, int col, int condition_num, char* keys[], OP left_op, OP right_op);
	int SearchIndex(int tb_id, int col, int condition_num, char* keys[], OP left_op, OP right_op, void* result[]);

	int GetCmpCondition(vector<int> cols, vector<OP>& operators, char* keys[], char* &low, char* &high);
	bool CheckTuple(int tb_id, char* tuple, vector<int> cols, vector<OP> operators, char* keys[]);
	bool TableScan(int tb_id);
	bool IndexScan(int tb_id);
	bool Select(int tb_id, vector<int> cols, vector<OP> operators, char* keys[]); // four types of select with one column
	int SelectTmp(int tb_id, vector<int> cols, vector<OP> operators, char* keys[]);

	void Project(int tb_id, vector<int> cols);
	bool Project(FILE* fout, int tb_id, vector<int> cols);
	int ProjectTmp(int tb_id, vector<int> cols);

	bool NestedLoopJoin(int left_tb_id, int right_tb_id, vector<int> cols1, vector<int> cols2, vector<OP> operators, bool isReverse);
	int NestedLoopJoinTmp(int left_tb_id, int right_tb_id, vector<int> cols1, vector<int> cols2, vector<OP> operators, bool isReverse);
	bool NestedLoopCartesianProduct(int left_tb_id, int right_tb_id, bool isReverse);
	int NestedLoopCartesianProductTmp(int left_tb_id, int right_tb_id, bool isReverse);

	bool NestedLoopJoinByThree(int tb_id_1, int tb_id_2, int tb_id_3, vector<int> cols1, vector<int> cols2, vector<int> cols3, vector<OP> operators);

	bool SortJoin(int left_tb_id, int right_tb_id, vector<int> cols); // equal
	bool HashJoin(int left_tb_id, int right_tb_id, vector<int> cols); // equal

	int SingleIndexJoin(int right_tb_id, int col2, char* keys[], OP op, void* result[]);
	bool IndexJoin(int left_tb_id, int right_tb_id, vector<int> cols1, vector<int> cols2, vector<OP> operators, bool isReverse); // equal and non-equal
	int IndexJoinTmp(int left_tb_id, int right_tb_id, vector<int> cols1, vector<int> cols2, vector<OP> operators, bool isReverse);
	bool IndexCartesianProduct(int left_tb_id, int right_tb_id, bool isReverse);
	int IndexCartesianProductTmp(int left_tb_id, int right_tb_id, bool isReverse);

	TableMeta* GetTableMeta(int table_index);
	// not use now
	int CartesianProduct(int* table_indexs);
	int Join(int* table_indexs, int* attr_indexs, bool equal_flag);

private:
	int table_count = 0;
	map<string, int> table_map;
	map<int, string> idx_name_map;
};



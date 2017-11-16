#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "storage.h"
#include "meta_info.h"
#include "bpt.h"
#include "linear_hash.h"
#include <vector>


enum Operator {
	eq,
	nq,
	lt,
	le,
	gt,
	ge
};



class Table {
public:
	int db_id; // database id
	ADDR start_addr;
	int index; // index in segment
	TableMeta *table_meta;
	Table(char* name, int db_id, int index, ADDR seg_id, ADDR start_addr, bool exist, AttrType *types, int *attr_length, int attribute_num);
	~Table();

	bool TableScan();
	bool IndexScan();

	bool Select(vector<int> cols, vector<Operator> operators, vector<key_t> keys); // four types of select
	bool TotalSelect();
	bool ESelect(int col, key_t key); // equal or non-equal
	bool RangeSelect(int col, key_t left, key_t right); // range select

	bool Project(vector<int> cols);

	bool LoopJoin(Table* right_table, vector<int> cols); // equal an non-equal
	bool SortJoin(Table* right_table, vector<int> cols); // equal an non-equal
	bool HashJoin(Table* right_table, vector<int> cols); // equal an non-equal
	bool IndexJoin(Table* right_table, vector<int> cols); // equal an non-equal
	bool ThreeJoin(Table* table_2, Table* table_3, vector<int> cols);
	bool ProductLoopJoin(Table* right_table);
	bool ProductIndexJoin(Table* right_table);
};

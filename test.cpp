#include "table.h"


int main() {
	char* tb_name_1 = "nation.tbl.data";
	char* tb_name_2 = "region.tbl.data";


	vector<char*> tb_name;
	tb_name.push_back(tb_name_1);
	tb_name.push_back(tb_name_2);
	TableManagement* table_manager = new TableManagement(tb_name);
	for (int i = 0; i < tb_name.size(); i++) {
		table_manager->InitTable(tb_name[i], 0, i ,false);
	}
	cout << "load ok" << endl;
	table_manager->CreateIndex(0, 2);
	table_manager->CreateIndex(1, 0);
	cout << "create index ok" << endl;

//	table_manager->IndexScan(1);
//	table_manager->TableScan(1);
//
//	vector<int> cols;
//	cols.push_back(0);
//	cols.push_back(0);
//	vector<Operator> operators;
//	operators.push_back(gt);
//	operators.push_back(le);
//	char* keys[2];
//	keys[0] = (char*)malloc(sizeof(char)*200);
//	keys[1] = (char*)malloc(sizeof(char)*200);
//	memcpy(keys[0], "5", sizeof("5"));
//	memcpy(keys[1], "10", sizeof("10"));
//	table_manager->Select(0, cols, operators, keys);

//	vector<int> cols;
//	cols.push_back(1);
//	cols.push_back(3);
//	table_manager->Project(0, cols);


//	vector<int> cols1;
//	cols1.push_back(2);
//	cols1.push_back(1);
//	vector<int> cols2;
//	cols2.push_back(0);
//	cols2.push_back(1);
//	vector<Operator> operators;
//	operators.push_back(lt);
//	operators.push_back(gt);
//	table_manager->IndexJoin(0, 1, cols1, cols2, operators, false);

//	table_manager->NestedLoopCartesianProduct(0, 1, false);

	vector<int> cols1;
	cols1.push_back(2);
	cols1.push_back(1);
	vector<int> cols2;
	cols2.push_back(0);
	cols2.push_back(1);
	vector<Operator> operators;
	operators.push_back(lt);
	operators.push_back(gt);
	table_manager->NestedLoopJoin(0, 1, cols1, cols2, operators, false);

	return 0;
}

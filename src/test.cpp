// #include "../include/table.h"
// ////#include "yacc.tab.h"
// ////#include "parser.h"
// //
// //
// int main() {
// 	TableManagement* table_manager = new TableManagement();
// 	char* tb_name = "test";
// 	char attr_names[16][20];
// 	TYPE* types;
// 	int* attr_length;
// 	types = (TYPE*)malloc(sizeof(TYPE)*3);
// 	attr_length = (int*)malloc(sizeof(TYPE)*3);
// 	int attribute_num = 3;
// 	for (int i = 0; i < 3; i++) {
// 		types[i] = I;
// 		attr_length[i] = 24;
// 	}
// 	types[2] = C;
// 	attr_length[2] = 256;
// 	strcpy(attr_names[0], "col1");
// 	strcpy(attr_names[1], "col2");
// 	strcpy(attr_names[2], "col3");
// 	int tb_id = table_manager->CreateTable(0, tb_name, MAX_TUPLE_SIZE, attr_names, types, attr_length, attribute_num);
// 	vector<int> cols;
// 	char* values[3];
// 	for (int i = 0; i < 3; i++) {
// 		values[i] = (char*)malloc(256);
// 	}
// 	memcpy(values[0], "0", 24);
// 	values[1] = "1";
// 	memcpy(values[2], "'WANG'", 256);
// 	table_manager->Insert(tb_id, cols, values);
// 	table_manager->Project(tb_id, cols);
// //////	table_manager->DropTable(tb_name);
// //////	table_manager->Project(tb_id, cols);
// //	char* tb_name_1 = "nation.tbl.data";
// //	char* tb_name_2 = "region.tbl.data";
// //	char* tb_name_3 = "supplier.tbl.data";
// //
// //
// //	vector<char*> tb_name;
// //	tb_name.push_back(tb_name_1);
// //	tb_name.push_back(tb_name_2);
// ////	tb_name.push_back(tb_name_3);
// //	TableManagement* table_manager = new TableManagement(tb_name);
// //	for (int i = 0; i < tb_name.size(); i++) {
// //		table_manager->InitTable(tb_name[i], 0);
// //	}
// //	cout << "load ok" << endl;
// //	table_manager->CreateIndex(0, 0);
// //	table_manager->CreateIndex(1, 0);
// //	cout << "create index ok" << endl;
// ////
// ////	vector<int> cols1;
// ////	vector<Operator> operators;
// ////	char* keys[1];
// ////	keys[0] = (char*)malloc(sizeof(char)*10);
// ////	keys[0] = "1";
// ////	operators.push_back(lt);
// ////	cols1.push_back(0);
// ////	table_manager->Delete(1, cols1, operators, keys);
// //////	char* up_keys[1];
// //////	up_keys[0] = (char*)malloc(sizeof(char)*10);
// //////	up_keys[0] = "5";
// //////	table_manager->Update(1, cols1, up_keys, cols1, operators, keys);
// ////	table_manager->IndexScan(1);
// //////
// //////	vector<int> cols1;
// //////	vector<Operator> operators;
// //////	char* keys[1];
// //////	keys[0] = (char*)malloc(sizeof(char)*10);
// //////	keys[0] = "1";
// //////	operators.push_back(lt);
// //////	cols1.push_back(0);
// //////	table_manager->Delete(1, cols1, operators, keys);
// //////	vector<int> cols;
// //////	table_manager->Project(1, cols);
// ////
// //////	vector<int> up_cols;
// //////	up_cols.push_back(1);
// //////	char* up_keys[1];
// //////	up_keys[0] = (char*)malloc(sizeof(char)*20);
// //////	memcpy(up_keys[0], "ADC", sizeof("111"));
// //////	vector<int> cols;
// //////	cols.push_back(0);
// //////	vector<Operator> operators;
// //////	operators.push_back(eq);
// //////	char* keys[1];
// //////	keys[0] = (char*)malloc(sizeof(char)*20);
// //////	memcpy(keys[0], "2", sizeof("2"));
// //////	table_manager->Update(0, up_cols, up_keys, cols, operators, keys);
// //////	vector<int> ccl;
// //////	table_manager->Project(0, ccl);
// ////
// //////	vector<int> cols;
// //////	char* values[8];
// //////	for (int i = 0; i < 7; i++) {
// //////		values[i] = (char*)malloc(sizeof(char)*100);
// //////		memcpy(values[i], "324", sizeof("324"));
// //////	}
// //////	table_manager->Insert(2, cols, values);
// //////	table_manager->Project(2, cols);
// ////
// //////	vector<int> cols;
// //////	cols.push_back(0);
// //////	cols.push_back(0);
// //////	vector<Operator> operators;
// //////	operators.push_back(gt);
// //////	operators.push_back(le);
// //////	char* keys[2];
// //////	keys[0] = (char*)malloc(sizeof(char)*200);
// //////	keys[1] = (char*)malloc(sizeof(char)*200);
// //////	memcpy(keys[0], "5", sizeof("5"));
// //////	memcpy(keys[1], "10", sizeof("10"));
// ////
// //////	int res_tb_id = table_manager->SelectTmp(0, cols, operators, keys);
// ////
// //////	vector<int> colss;
// //////	colss.push_back(0);
// //////	colss.push_back(1);
// //////	colss.push_back(3);
// //////	int res_tb_id =  table_manager->ProjectTmp(0, colss);
// //////	vector<int> cols;
// //////	cols.push_back(0);
// //////	cols.push_back(0);
// //////	vector<Operator> operators;
// //////	operators.push_back(gt);
// //////	operators.push_back(le);
// //////	char* keys[2];
// //////	keys[0] = (char*)malloc(sizeof(char)*200);
// //////	keys[1] = (char*)malloc(sizeof(char)*200);
// //////	memcpy(keys[0], "5", sizeof("5"));
// //////	memcpy(keys[1], "10", sizeof("10"));
// //////	table_manager->Select(res_tb_id, cols, operators, keys);
// ////
// //////	vector<int> cols;
// //////	cols.push_back(1);
// //////	cols.push_back(3);
// //////	table_manager->Project(0, cols);
// ////
// ////
// //////	vector<int> cols1;
// //////	cols1.push_back(2);
// //////	cols1.push_back(1);
// //////	vector<int> cols2;
// //////	cols2.push_back(0);
// //////	cols2.push_back(1);
// //////	vector<Operator> operators;
// //////	operators.push_back(lt);
// //////	operators.push_back(gt);
// //////	int res_tb_id = table_manager->IndexJoinTmp(0, 1, cols1, cols2, operators, false);
// //////	cout << res_tb_id << endl;
// //////	vector<int> cols;
// //////	table_manager->Project(res_tb_id, cols);
// ////
// //////	table_manager->NestedLoopCartesianProduct(0, 1, false);
// ////
// //////	vector<int> cols1;
// //////	cols1.push_back(2);
// //////	cols1.push_back(1);
// //////	vector<int> cols2;
// //////	cols2.push_back(0);
// //////	cols2.push_back(1);
// //////	vector<Operator> operators;
// //////	operators.push_back(lt);
// //////	operators.push_back(gt);
// //////	int res_tb_id = table_manager->NestedLoopCartesianProductTmp(0, 1, false);
// //////	int res_tb_id_2 = table_manager->NestedLoopCartesianProductTmp(res_tb_id, 2, false);
// //////	cout << res_tb_id_2 << endl;
// //////	vector<int> col;
// //////	table_manager->Project(res_tb_id_2, col);
// ////
// 	return 0;
// }

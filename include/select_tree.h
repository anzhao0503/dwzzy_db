#ifndef _SELECT_TREE_
#define _SELECT_TREE_

void print_select(char* tbl, vector<char*> cols, vector<OP> ops, char** keys);
void print_project(char* tbl, vector<char*> cols);
void print_join(char* tb1, char* tb2, vector<char*> cols1, vector<char*> cols2, vector<OP> ops);
void print_kashi(char* tb1, char* tb2);
int select_tree();


#endif
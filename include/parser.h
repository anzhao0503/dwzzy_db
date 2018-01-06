/*
 * paser.h *
 *  Created on: Nov 30, 2017
 *      Author: gpadmin
 */
#define MAX_SELITEM_NUM 20
#define MAX_ATTR_NUM 20
#define MAX_FROM_NUM 20
#define MAX_COND_NUM 20
#define MAX_JOIN_NUM 20
#define MAX_ORDER_BY 20
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include "../include/table.h"
using namespace std;

/*
 * for create, store table meta data info
 * create table_name
 * 					attr1 type1 size1
 * 					attr2 type2 size2
 * 					...;
 */
struct AttrInfo{
	char* table_name;
	char* attr_name;
	TYPE type;
	int used_size;
};

/*
 * select sellist from fromlist where condlist orderby orrderlist;
 */
struct SelItem{
	char* table_name;
	char* col_name;
	int col_id;
};


struct FromItem{
	//Relname
	char* tb_name;
	int tb_id;
//	struct FromList *next;
};

struct Condition{
	/*
	 * cond1:tb1.col_name1 op tb2.col_name2
	 * cond2:tb1.col_name1 op value;
	 */
	OP op;
	char* tb_name;
	int tb_id;
	char* col_name;
	char* value;
	TYPE value_type;
//	struct Condition* next;
};

struct Join{
	OP op;
	char* tb_name1;
	char* tb_name2;
	char* col_name1;
	char* col_name2;

//	struct Join* next;
};
struct Orderby{
	char* col_name;
	int   col_id;
};

struct SelectQuery{
	int distinct;
	int all;
	SelItem		SelList[MAX_SELITEM_NUM];
	FromItem 	FromList[MAX_FROM_NUM];
	Join 		JoinList[MAX_JOIN_NUM];
	Condition 	CondList[MAX_COND_NUM];
	Orderby 	OrderbyList[MAX_ORDER_BY];
	SelectQuery* next;
};


struct DeleteQuery{
	char* tb_name;
	Condition	CondList[MAX_JOIN_NUM];
};

struct UpdateQuery{
	char* tb_name;
	char* col_name[256];
	char* col_value[256];
	Condition	CondList[MAX_COND_NUM];
};

 /* if necessary, query stack for nested query.*/

//enum TYPE{
//	I=1,C,V,F,D
//};
//enum OP{
//	E=1,GE,G,LE,L,NE
//};

int PrintSelectQuery();
int PrintAttrList();
int ExecCreate();
bool ExecDelete();
bool ExecUpdate();
int Printdmy();
int PrintCondList();
int ExecProject();
void PrintSpace(int n);
void PrintTree();
int SaveSelItem(char* tb_name, char* col_name);
int SaveFromItem(char* tb_name);
int SaveCondition(char* tb_name, char* col_name, char* value, TYPE value_type, OP op);
int SaveJoin(char* tb_name1, char* col_name1, char* tb_name2, char* col_name2, OP op);
int SaveOrderbyItem(char *col_name);
int SaveAttributeInfo(char* attr_name, TYPE type, int size);
int FillSelectCond();
int FillDeleteCond();
int FillUpdateCond();


void InitQuery();
void DestoryQuery();
void parser_init();
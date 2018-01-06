%{
#include <string.h>
#include "../include/parser.h"
#include "../include/BST.h"
extern "C"{
	extern int yylex(void);
	extern int lex_init();
	extern int yyerror(char *s);
}
/*
  	functions
 */
int PrintSelectQuery();
int PrintAttrList();
int Printdmy();
int Printdmy();
int PrintCondList();
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

static char errmsg[4096];
OP Operator(char* opstr);
TYPE GetType(char* type_str);
static char recordstr[4096];
TableManagement* table_manager;

/*
	variables
 */

char* tb_name;
/*
	for update query.
 */
int update_col_count=0;
UpdateQuery* update_query;
/*
	for insert query.
 */
char* insert_record[MAX_TUPLE_SIZE];
int insert_count = 0;
/*
	for create query.
 */
int attr_count = 0;
AttrInfo attr_list[MAX_ATTR_NUM];

/*
	for conditions.
 */
int cond_count = 0;
Condition cond_list[MAX_COND_NUM];
/*
	for delete query.
 */
DeleteQuery* delete_query;
/*
	for select query.
 */
int join_count = 0;
int sel_count = 0;
int from_count = 0;
int orderby_count = 0;
SelectQuery* query;
int curPos = 0;
int funcRnt;

%}

%union{
	int intval;
	char* strval;
}

%start sql_start

%token <strval> NAME
%token <strval> STRING
%token <strval> NUMBER
%token <strval> COMPARISION

	/* operator */
%left	 AND
%left COMPARISION /* < <= > >= <> = */
%left '+' '-'
%left '*' '/'

	/* reserved keywords */
%token SELECT FROM WHERE ORDER BY ASC DESC
%token ALL UNIQUE DISTINCT
%token CREATE TABLE DROP INDEX LOAD
%token INSERT INTO VALUES DELETE UPDATE SET
%token CHARACTER INTEGER DATE FLOAT VARCHAR
%token SHOW TABLES
%token EXIT

%%

sql_start:
		sql_func
		{
			if(funcRnt == 0)
			{
				cout<<"should new query here."<<endl;
				cout << "Success" <<endl;
			}
			else if(funcRnt < 0)
			{
				cout << "Failure："<<funcRnt<<errmsg<<endl; 
			}
			return 0;
		}
	|	EXIT
		{
			cout<<"Should Flush Table Here.\n"<<endl;
		}
	;
sql_func:
		';'
		{
			funcRnt = 100;
		}
	|	table_load
	|	table_def
	|	table_drop
	|	insert_stat
	|	update_stat
	|	delete_stat
	|	select_stat
	;
/*load_data*/
table_load:
		LOAD STRING INTO NAME ';'
		{
			tb_name = $4;
			cout<<"LOAD " << $2 <<" INTO "<<$4<<" "<<endl;
			string tmp_name(tb_name);
			load_data(tmp_name);
		}
	;
/* create table */
table_def:
		CREATE TABLE table '(' table_attr_list ')' ';'
		{
			cout<<"Create Table "<< tb_name << endl;
			PrintAttrList();
			exec_create_stmt();	
		}
	;

table:
		NAME
		{
			tb_name = $1;
			attr_list[attr_count].table_name = $1;
			//printf("tb_name %s \n",tb_name);
		}
	;
table_attr_list:
		column_def
	|	table_attr_list ',' column_def
	;
column_def:
		column data_type
		{
			attr_count++;
			
		}
	;
column:
		NAME
		{
			attr_list[attr_count].attr_name = $1;
		}
	;
data_type:
		CHARACTER '(' NUMBER ')'
		{
			attr_list[attr_count].type = C;
			attr_list[attr_count].used_size = (int)atoi($3);
		}
	|	INTEGER
		{
			attr_list[attr_count].type= I;
			attr_list[attr_count].used_size = MAX_INT_ASCII_LENGTH;
		}
	|	DATE
		{
			attr_list[attr_count].type= D;
			attr_list[attr_count].used_size = MAX_DATE_ASCII_LENGTH;
		}
	|
		VARCHAR '(' NUMBER ')'
		{
			attr_list[attr_count].type= V;
			attr_list[attr_count].used_size = (int)atoi($3);
		}
	|
		FLOAT '(' NUMBER ')'
		{
			attr_list[attr_count].type= F;
			attr_list[attr_count].used_size = (int)atoi($3);
		}
	;
/* drop table */
table_drop:
		DROP TABLE table ';'
		{
			cout<<"DROP TABLE"<< tb_name << endl;
			exec_drop_table_stmt();
		}
	;
/* insert statements */
insert_stat:
		INSERT INTO table VALUES '(' insert_list ')' ';'
		{
			int tb_id = table_manager->GetTableId(tb_name);
			vector<int> cols;
			table_manager->Insert(tb_id, cols, insert_record);
			cout << "INSERT INTO " << tb_name << " " << recordstr <<endl;
		}
	; 	
insert_list:
		NUMBER
		{
			insert_record[insert_count] = (char*)malloc(sizeof(int)*MAX_INT_ASCII_LENGTH);
			memcpy(insert_record[insert_count],$1, MAX_INT_ASCII_LENGTH);
			insert_count++;
			strcpy(recordstr+curPos, $1);
			curPos+=strlen($1);
		}
	|	STRING
		{
			insert_record[insert_count] = (char*)malloc(256);
			memcpy(insert_record[insert_count],$1, 256);
			insert_count++;
			strcpy(recordstr+curPos, $1);
			curPos+=strlen($1);
		}
	|	insert_list ',' NUMBER
		{
			insert_record[insert_count] = (char*)malloc(sizeof(int)*MAX_INT_ASCII_LENGTH);
			memcpy(insert_record[insert_count],$3, MAX_INT_ASCII_LENGTH);
			insert_count++;
			
			strcpy(recordstr+curPos, ",");
			curPos++;

			strcpy(recordstr+curPos, $3);
			curPos += strlen($3);
		}
	|	insert_list ',' STRING
		{
			insert_record[insert_count] = (char*)malloc(256);
			memcpy(insert_record[insert_count],$3,256);
			insert_count++;
			
			strcpy(recordstr+curPos, ",");
			curPos++;

			strcpy(recordstr+curPos, $3);
			curPos += strlen($3);
		}
	;
/*update statement*/
update_stat:
		UPDATE NAME SET set_cond  where_clause ';'
		{
			cout<<"Update";
			update_query->tb_name = $2;
			cout<<"tb_name:"<<update_query->tb_name<<endl;
			FillUpdateCond();
			cout<<"Update Cond:"<<endl;
			exec_update_stmt();
		}
	;
set_cond:

		set_expr

	|	set_cond AND set_expr
	;
set_expr:
		NAME COMPARISION STRING
		{
			if(strcmp("=",$2)==0){
			cout << "string comp"<<endl;
			cout << "update_count"<<update_col_count<<endl;
			update_query->col_name[update_col_count] = (char*)malloc(20);
			memcpy(update_query->col_name[update_col_count],$1,20);
			update_query->col_value[update_col_count]=(char*)malloc(256);
			memcpy(update_query->col_value[update_col_count],$3,256);
			cout<<update_query->col_name[update_col_count]<<" = "<<update_query->col_value[update_col_count]<<endl;
			update_col_count++;
			}
			else{
				cout<<"syntax error"<<endl;
			}
			
		}
	|	NAME COMPARISION NUMBER
		{
			if(strcmp("=",$2)==0){
			cout << "comp"<<endl;
			update_query->col_name[update_col_count] = (char*)malloc(20);
			memcpy(update_query->col_name[update_col_count],$1,20);
			update_query->col_value[update_col_count]=(char*)malloc(sizeof(int)*8);
			memcpy(update_query->col_value[update_col_count],$3,sizeof(int)*8);
			cout<<update_query->col_name[update_col_count]<<" = "<<" number "<<update_query->col_value[update_col_count] << endl;
			update_col_count++;			
			}
			else{
				cout<<"syntax error"<<endl;
			}
		}
	;
	/* delete statement */
delete_stat:
		DELETE FROM table where_clause ';'
		{
			cout << "DELETE FROM\n"<<endl;
			delete_query->tb_name = tb_name;
			cout << delete_query->tb_name <<endl;
			FillDeleteCond();
			PrintCondList();
			cout << "Call delete() function here."<<endl;
			exec_delete_stmt();
			
		}
	;


/* select statements */
select_stat:
		select_seg ';'
		{
		}
	;
select_seg:
		select_clause FROM fromlist where_clause orderby_clause
		{
			FillSelectCond();
			exec_select_stmt();			
		}
	;
select_clause:
		selectbegin unique sellist
		{
			query->all = 0;
			cout<<"all "<<query->all<<endl;
		}
	|	selectbegin unique '*'
		{
			query->all = 1;
			cout<<"all "<<query->all<<endl;
		}
	;
selectbegin:
		SELECT
		{
			printf("-----one sub selection begin----\n");
		}
	;
unique:
		/* empty */
		{
			query->distinct = 0;
			cout<<"distinct "<<query->distinct<<endl;
		}
	|	ALL
		{
			query->all = 1;
			cout<<"all "<<query->distinct<<endl;
		}
	|	DISTINCT
		{
			query->distinct = 1;
			cout<<"distinct "<<query->distinct<<endl;
		}
	|	UNIQUE
		{
			query->distinct = 1;
			cout<<"distinct "<<query->distinct<<endl;
		}
	;
sellist:
		sel_column
	|	sellist ',' sel_column
	;
sel_column:
		NAME
		{
			SaveSelItem(NULL,$1);
		}
	|	NAME '.' NAME
		{
			SaveSelItem($1,$3);
		}
	;		
fromlist:
		sel_table
	|	fromlist ',' sel_table
	;
sel_table:
		NAME
		{	
			SaveFromItem($1);
			
		}
		/* sub selection */
	|	'(' select_seg ')' /* +empty */			
		{	
			cout << "Sorry, Our DB Cannnot Support Nested Select Now."<<endl;
		}
	|	'(' select_seg ')' NAME			
		{	
			cout << "Sorry, Our DB Cannnot Support Nested Select Now."<<endl;
		}
		;	
where_clause:
		/* empty */
	|	WHERE condition
	;
condition:
		expr
	|	condition AND expr
	;
expr:
		NAME '.' NAME COMPARISION NAME '.' NAME
		{
			SaveJoin($1, $3, $5, $7, Operator($4));	
		}
	|	NAME COMPARISION NUMBER
		{
			SaveCondition("", $1, $3, I, Operator($2));	
		}
	|	NAME COMPARISION STRING
		{
			SaveCondition("", $1, $3, V, Operator($2));
		}
	|	NAME '.' NAME COMPARISION NUMBER
		{
			SaveCondition($1, $3, $5, I, Operator($4));
		}
	|	NAME '.' NAME COMPARISION STRING
		{
			SaveCondition($1, $3, $5, V, Operator($4));
		}
	;
orderby_clause:
	/*empty*/
	|	ORDER BY orderlist
	;
orderlist:
		NAME
		{
			SaveOrderbyItem($1);
		}
	| 	orderlist ',' NAME
	;
%%

void parser_init()
{
	lex_init();
	tb_name = NULL;
	funcRnt = 0;
	curPos = 0;

	for(int i = 0; i<insert_count;i++)
		memset(insert_record[i],0,MAX_TUPLE_SIZE);
	insert_count = 0;

	attr_count = 0;
	memset(attr_list,0,sizeof(AttrInfo)*MAX_ATTR_NUM);

	cond_count = 0;
	memset(cond_list,0,sizeof(Condition)*MAX_COND_NUM);

	join_count = 0;	
	sel_count = 0;
	from_count = 0;
	memset(query,0,sizeof(SelectQuery));
	memset(delete_query,0,sizeof(DeleteQuery));

	update_col_count = 0;
	memset(update_query,0,sizeof(UpdateQuery));
	return;
}

void InitQuery(){
	update_query = (UpdateQuery*)malloc(sizeof(UpdateQuery));
	delete_query = (DeleteQuery*)malloc(sizeof(DeleteQuery));
	query = (SelectQuery*)malloc(sizeof(SelectQuery));
	query->distinct = 0;
	query->all = 0;
}
void DestoryQuery(){
	free(delete_query);
	free(update_query);
	free(query);
}
int SaveCondition(char* tb_name, char* col_name, char* value, TYPE value_type, OP op){
	if(cond_count > MAX_COND_NUM){
		return -1;
	}
	cond_list[cond_count].col_name = col_name;
	
	cond_list[cond_count].tb_name = tb_name;
	cond_list[cond_count].value = value;
	
	cond_list[cond_count].value_type = value_type;
	
	cond_list[cond_count].op = op;
	
	cond_count++;
	
	return 0;
}
int SaveJoin(char* tb_name1, char* col_name1, char* tb_name2, char* col_name2, OP op){
	if(join_count > MAX_JOIN_NUM){
			return -1;
		}
	query->JoinList[join_count].col_name1 = col_name1;
	query->JoinList[join_count].col_name2 = col_name2;
	query->JoinList[join_count].op = op;
	query->JoinList[join_count].tb_name1 = tb_name1;
	query->JoinList[join_count].tb_name2 = tb_name2;
	join_count++;
	return 0;

}
int SaveAttributeItem(char* table_name, char* attr_name, TYPE type, int size){
	if(attr_count > MAX_ATTR_NUM){
				return -1;
	}
	attr_list[attr_count].table_name = table_name;
	attr_list[attr_count].attr_name = attr_name;
	attr_list[attr_count].type = type;
	attr_list[attr_count].used_size = size;
	attr_count++;
	return 0;
}
int SaveSelItem(char* tb_name, char* col_name){
	query->SelList[sel_count].col_name = col_name;
	query->SelList[sel_count].table_name = tb_name;
	sel_count ++;
	return 0;
}
int SaveFromItem(char* tb_name){
	query->FromList[from_count].tb_name = tb_name;
	from_count++;
	return 0;
}
int SaveOrderbyItem(char *col_name){
	query->OrderbyList[orderby_count].col_name = col_name;
	orderby_count ++;
	return 0;
}
int FillSelectCond(){
	query->cond_count = cond_count;
	query->from_count = from_count;
	query->sel_count = sel_count;
	query->join_count = join_count;
	memcpy(query->CondList,cond_list,cond_count * sizeof(Condition));
	return 0;
}
int FillDeleteCond(){
	delete_query->cond_count = cond_count;
	memcpy(delete_query->CondList,cond_list,cond_count * sizeof(Condition));
	return 0;
}
int FillUpdateCond(){
	update_query->cond_count = cond_count;
	update_query->col_count = update_col_count;
	memcpy(update_query->CondList,cond_list,cond_count * sizeof(Condition));

	return 0;
}

/*
 * attr_list: attributes iostreamfor a table
 */
int PrintAttrList(){
	int i;
	for(i=0;i<attr_count;i++){
			cout<<"attr "<<i<<": "<<attr_list[i].attr_name<<" type "<<attr_list[i].type<<" size "<<attr_list[i].used_size<<endl;
		}
		return 0;
}
int PrintCondList(){
	int i;
	for(i = 0; i < cond_count; i++){
		cout << "AND "<<endl;	
		if(cond_list[i].tb_name != "")
			cout<<"\t"<<cond_list[i].tb_name<<"."<<cond_list[i].col_name<<" op "<<cond_list[i].op<<" "<< cond_list[i].value<<endl;
		else
			cout << " op " << query->CondList[i].op << endl;
			cout<<"\t"<<cond_list[i].col_name<<" op "<<cond_list[i].op<<" "<< cond_list[i].value<<endl;		
	}
}
void print_select(char* tbl, vector<char*> cols, vector<OP> ops, char** keys){
  cout<<"σ "<<tbl<<" ";
  for_each(cols.begin(),cols.end(),print_order);
  for_each(ops.begin(),ops.end(),print_order_int);
  for(int i=0; i< 10;i++){
    if(keys[i] != NULL){
      cout<<keys[i]<<" ";
    }
    else
      break;
  }
  cout<<endl;
}
void print_project(char* tbl, vector<char*> cols){
  cout <<"π "<<tbl<<" ";
  for_each(cols.begin(),cols.end(),print_order);
  cout<<endl;
}
void print_join(char* tb1, char* tb2, vector<char*> cols1, vector<char*> cols2, vector<OP> ops){
  cout <<"⋈ " << tb1 << " "<<tb2<<" ";
  for_each(cols1.begin(),cols1.end(),print_order);
  for_each(cols2.begin(),cols2.end(),print_order);
  for_each(ops.begin(),ops.end(),print_order_int);
  cout<<endl;
}
void print_kashi(char* tb1, char* tb2){
  cout << "x " << tb1<<" "<<tb2<<endl;
}

int PrintSelectQuery(){
	int i = 0;
	if(from_count!=0)
		cout << "SELECT "<< endl;
	if(query->all != 0)
		cout<< "*" << endl;
	if(sel_count!=0){
		cout << "SEL_LIST" <<endl;
		for(i=0; i < sel_count; i++){
			cout<<"\t"<<query->SelList[i].col_name<<endl;
		}
	}	
	cout << "FROMLIST" << endl;
	for(i = 0; i < from_count; i++){
		cout<<"\t"<<query->FromList[i].tb_name<<endl;
	}
	if(cond_count!=0){
		cout <<"WHERECLAUSE"<< endl;
	}
	PrintTree();
/*
	for(i = 0; i < cond_count; i++){
			
		if(query->CondList[i].tb_name != "")
			cout<<"\t"<<query->CondList[i].tb_name<<"."<<query->CondList[i].col_name<<" op "<<query->CondList[i].op<<" "<< query->CondList[i].value<<endl;
		else
			//cout << " op " << query->CondList[i].op << endl;
			cout<<"\t"<<query->CondList[i].col_name<<" op "<<query->CondList[i].op<<" "<< query->CondList[i].value<<endl;	
		cout << "AND "<<endl;	
	}
	for(i=0;i < join_count; i++){
		cout<<"\t"<<query->JoinList[i].tb_name1<<"."<<query->JoinList[i].col_name1<<" op "<<query->JoinList[i].op<<" "<<query->JoinList[i].tb_name2<<"."<<query->JoinList[i].col_name2<<endl;
		cout << "AND "<<endl;
	}*/	
	if(attr_count != 0)
		cout<<"CREATE TABLE "<<endl;
	for(i=0;i<attr_count;i++){
		cout<<attr_list[i].table_name<<"attr_name "<<attr_list[i].attr_name<<"type "<<attr_list[i].type<<"size "<<attr_list[i].used_size<<endl;
	}
	if(orderby_count!=0)
		cout<<"ORDER BY"<< endl;
	for(i=0;i<orderby_count;i++)
		cout<<query->OrderbyList[i].col_name<<endl;
	
	return 0;
}

void PrintTree(){
	int i;
	if(cond_count == 1 && join_count == 0){
		if(query->CondList[i].tb_name != "")
			cout<<"\t"<<query->CondList[0].tb_name<<"."<<query->CondList[0].col_name<<" op "<<query->CondList[0].op<<" "<< query->CondList[0].value<<endl;
		else
			cout<<"\t"<<query->CondList[0].col_name<<" op "<<query->CondList[0].op<<" "<< query->CondList[0].value<<endl;
		return;
	}//end if cond_count 1
	if(join_count == 1 && cond_count == 0){
		cout<<"\t"<<query->JoinList[0].tb_name1<<"."<<query->JoinList[0].col_name1<<" op "<<query->JoinList[0].op<<" "<<query->JoinList[0].tb_name2<<"."<<query->JoinList[0].col_name2<<endl;
		return;
	}//end if join_count 1
	else{
		cout<<"AND"<<endl;
		cout<<"| \t\t \\"<<endl;
		// for join_count + cond_count >= 3
		for(i=1;i<(join_count+cond_count)-1;i++){
			PrintSpace(i-1);
			PrintSpace(i-1);
			if(i<=cond_count){
				cout<<" op "<<query->CondList[i-1].op<<"\t\tAND"<<endl;
				PrintSpace(i-1);
				PrintSpace(i-1);
				cout<<"|\t\\"<<endl;
				PrintSpace(i-1);
				PrintSpace(i-1);
				if(query->CondList[i-1].tb_name != "")
					cout<<query->CondList[i-1].tb_name<<"."<<query->CondList[i-1].col_name<<" "<< query->CondList[i-1].value<<endl;
				else
				//cout << " op " << query->CondList[i].op << endl;
					cout<<query->CondList[i-1].col_name<<" "<< query->CondList[i-1].value<<endl;
			}
			if(i>cond_count){
				cout<<" op "<<query->JoinList[i-cond_count-1].op<<"\t\tAND"<<endl;
				PrintSpace(i-1);
				PrintSpace(i-1);
				cout<<"|\t\\"<<endl;
				PrintSpace(i-1);
				PrintSpace(i-1);
				cout<<query->JoinList[i-cond_count-1].tb_name1<<"."<<query->JoinList[i-cond_count-1].col_name1<<" "<<query->JoinList[i-cond_count-1].tb_name2<<"."<<query->JoinList[i-cond_count-1].col_name2<<endl;
			}
			//cout<<"cond"<<i-1<<"\tAND"<<endl;
			PrintSpace(i);
			PrintSpace(i);
			cout<<"| \t\t \\"<<endl;
		}//end for
		PrintSpace(join_count+cond_count-2);
		PrintSpace(join_count+cond_count-2);
		if((join_count == 1)&(cond_count>=2)){
			cout<<" op "<<query->CondList[cond_count-1].op<<"\t\t\t"<<" op "<<query->JoinList[0].op<<endl;
			PrintSpace(join_count+cond_count-2);
			PrintSpace(join_count+cond_count-2);
			cout<<"| \\\t\t\t| \\"<<endl;
			PrintSpace(join_count+cond_count-2);
			PrintSpace(join_count+cond_count-2);
			if(query->CondList[cond_count-1].tb_name != "")
				cout<<query->CondList[cond_count-1].tb_name<<"."<<query->CondList[cond_count-1].col_name<<" "<< query->CondList[cond_count-1].value<<"\t\t\t";
			else
				cout<<query->CondList[cond_count-1].col_name<<" "<< query->CondList[cond_count-1].value<<"\t\t\t";
			cout<<query->JoinList[join_count-1].tb_name1<<"."<<query->JoinList[join_count-1].col_name1<<" "<<query->JoinList[join_count-1].tb_name2<<"."<<query->JoinList[join_count-1].col_name2<<endl;
			return;			
		}
		if(join_count >=2 ){
			cout<<" op "<<query->JoinList[join_count-2].op<<"\t\t"<<" op "<<query->JoinList[join_count-1].op<<endl;
			PrintSpace(join_count+cond_count-2);
			PrintSpace(join_count+cond_count-2);
			cout<<"| \\\t\t\t| \\"<<endl;
			PrintSpace(join_count+cond_count-2);
			PrintSpace(join_count+cond_count-2);
			cout<<query->JoinList[join_count-2].tb_name1<<"."<<query->JoinList[join_count-2].col_name1<<" "<<query->JoinList[join_count-2].tb_name2<<"."<<query->JoinList[join_count-2].col_name2<<"\t"<<query->JoinList[join_count-1].tb_name1<<"."<<query->JoinList[join_count-1].col_name1<<" "<<query->JoinList[join_count-1].tb_name2<<"."<<query->JoinList[join_count-1].col_name2<<endl;
			return;
		}//end if join_count >= 2
		if (join_count==0 & cond_count >= 2){
			cout<<" op "<<query->CondList[cond_count-2].op<<"\t\t\t"<<" op "<<query->CondList[cond_count-1].op<<endl;
			PrintSpace(join_count+cond_count-2);
			PrintSpace(join_count+cond_count-2);
			cout<<"| \\\t\t\t| \\"<<endl;
			PrintSpace(join_count+cond_count-2);
			PrintSpace(join_count+cond_count-2);
			if(query->CondList[cond_count-2].tb_name != "")
				cout<<query->CondList[cond_count-2].tb_name<<"."<<query->CondList[cond_count-2].col_name<<" "<< query->CondList[cond_count-2].value<<"\t";
			else
				cout<<query->CondList[cond_count-2].col_name<<" "<< query->CondList[cond_count-2].value<<"\t";
			if(query->CondList[cond_count-1].tb_name != "")
				cout<<query->CondList[cond_count-1].tb_name<<"."<<query->CondList[cond_count-1].col_name<<" "<< query->CondList[cond_count-1].value<<endl;
			else
				cout<<query->CondList[cond_count-1].col_name<<" "<< query->CondList[cond_count-1].value<<endl;
			return;
		}//end if join = 0 & cond >= 2
	}//end else	
}
void PrintSpace(int n){
	int i;
	for(i=0;i<n;i++){
		cout<<"\t";	
	}
}

OP Operator(char* opstr)
{
	OP op;
	if (strcmp(opstr, "=") == 0){
		op = eq;
		return op;
	}
	else if (strcmp(opstr, ">=") == 0) {
		op = ge;
		return op;
	}	
	else if (strcmp(opstr, "<=") == 0){
		op = le;
		return op;
	}
	else if (strcmp(opstr, ">") == 0) {
		op = gt;
		return op;
	}
	else if (strcmp(opstr, "<") == 0) {
		op = lt;
		return op;
	}
	else if (strcmp(opstr, "<>") == 0) {
		op = nq;
		return op;
	}
	return eq;
}

TYPE GetType(char* type_str)
{
	TYPE type;
	if (strcmp(type_str, "INTEGER") == 0){
		type = I;
		return type;
	}
	else if (strcmp(type_str, "CHARACTER") == 0) {
		type = C;
		return type;
	}	
	else if (strcmp(type_str, "VARCHAR") == 0){
		type = V;
		return type;
	}
	else if (strcmp(type_str, "FLOAT") == 0) {
		type = F;
		return type;
	}
	else if (strcmp(type_str, "DATE") == 0) {
		type = D;
		return type;
	}
	return I;
}
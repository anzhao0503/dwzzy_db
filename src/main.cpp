/*
 * parser.cpp
 *
 *  Created on: Nov 30, 2017
 *      Author: wcw
 *	
 */
#include <string.h>
#include <iostream>
#include "../include/yacc.tab.h"
#include "../include/parser.h"
// #include "../include/yacc.tab.h"
// #include "../include/parser.h"
// #include "../rpc_sql/rpc_sql.h"
using namespace std;

int main(){
	FILE *fp = fopen("sql.input","r");
	if(fp==NULL){
		cout<<"no such file."<<endl;
		return -1;
	}
	extern FILE* yyin;
	yyin = fp;
	cout<<"---------------A SIMPLE TEST VERSION.---------------"<<endl;
	InitQuery();
	while(1) {
		cout<<"---------------Please Input SQL.--------------------"<<endl;
	    parser_init();
	    int rnt = yyparse();
	    if(rnt==-1)
	    	break;
	    cout<<"---------------Finished.----------------------------"<<endl;
	}
	DestoryQuery();
	return 0;
}

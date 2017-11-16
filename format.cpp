/*
 * format.cpp
 *
 *  Created on: Oct 24, 2017
 *      Author: wcw
 */
#include "format.h"
char* encode(char* input, string dtyp, int length) {
	char* res = (char*)malloc(sizeof(char)*length+1);
	if (dtyp == "int") {
		memcpy(res, input, strlen(input));
	} else if (dtyp == "float") {
		memcpy(res, input, strlen(input));
	} else if (dtyp == "char") {
		memcpy(res, input, strlen(input));
	} else if (dtyp == "varchar") {
		// 1-3 bit means length of varchar
//		if (strlen(input) < 10) {
//			res[0] = '0';
//			res[1] = '0';
//		} else if (strlen(input) < 100) {
//			res[0] = '0';
//		}
//		cout<<res<<endl;
//		char tmp[sizeof(int)+1];
//		sprintf(tmp, "%d", strlen(input));
//		strcat(res, tmp);
//
//		strcat(res, input);
		memcpy(res, input, strlen(input));
	} else {
		cout << "False data type" << endl;
		return NULL;
	}
	for (int j = strlen(res); j < length; j++) {
		res[j] = '*';
	}
	res[length] = '\0';
	return res;
}

char* decode(char* input, int address) {
	address = address % 4096;
	char* res = (char*)malloc(sizeof(char)*512);
	int i = 0;
	for(int num = 0; num < 8; num ++){
		int j = 0;

		while(i % 512 < 5 && input[i]!= '*') {
			res[j] = input[i];
			i++;
			j++;
		}
		res[j]='|';
		j++;
		i=5 + num*512;
		while(i % 512 < 23 && input[i]!='*') {
			res[j] = input[i];
			i++;
			j++;
		}
		i=23 + num*512;
		res[j]='|';
		j++;
		while(i % 512 < 123 && input[i]!='*') {
			res[j] = input[i];
			i++;
			j++;
		}
		i=123 + num*512;
		res[j]='|';
		j++;
		while(i % 512 < 126 && input[i]!='*') {
			res[j] = input[i];
			i++;
			j++;
		}
		i=126 + num*512;
		res[j]='|';
		j++;
		while(i % 512 < 141 && input[i]!='*') {
			res[j] = input[i];
			i++;
			j++;
		}
		i=141 + num*512;
		res[j]='|';
		j++;
		while(i % 512 < 156 && input[i]!='*') {
			res[j] = input[i];
			i++;
			j++;
		}
		i=156 + num*512;
		res[j]='|';
		j++;
		while(i % 512 < 306 && input[i]!='*') {
			res[j] = input[i];
			i++;
			j++;
		}
		i=306 + num*512;
/*		res[j]='|';
		j++;
		while(i % 512 < 512 && input[i]!='*') {
			res[j] = input[i];
			i++;
			j++;
		}*/
		i=512 + num*512;

		res[j-1] = '\0';
		address -= 512;
		if(address < 0){
			return res;
		}
	}	
}


char* decode_index(char* input, int address, int index) {
	address = address % 4096;
	char* res = (char*)malloc(sizeof(char)*512);
	int i = 0;
	int index_bak = index;
	for(int num = 0; num < 8; num ++){
		int j = 0;
		index = index_bak;
		while(i % 512 < 5 && input[i]!= '*') {
			res[j] = input[i];
			i++;
			j++;
		}
		res[j]='\0';
		j = 0;
		index--;
		if(index == 0 && address - num * 512 - 512 < 0){
			return res;
		}
		i=5 + num*512;
		while(i % 512 < 23 && input[i]!='*') {
			res[j] = input[i];
			i++;
			j++;
		}
		i=23 + num*512;
		res[j]='\0';
		j = 0;
		index--;
		if(index == 0 && address - num * 512 - 512 < 0){
			return res;
		}
		while(i % 512 < 123 && input[i]!='*') {
			res[j] = input[i];
			i++;
			j++;
		}
		i=123 + num*512;
		res[j]='\0';
		j = 0;
		index--;
		if(index == 0 && address - num * 512 - 512 < 0){
			return res;
		}
		while(i % 512 < 126 && input[i]!='*') {
			res[j] = input[i];
			i++;
			j++;
		}
		i=126 + num*512;
		res[j]='\0';
		j = 0;
		index--;
		if(index == 0 && address - num * 512 - 512 < 0){
			return res;
		}
		while(i % 512 < 141 && input[i]!='*') {
			res[j] = input[i];
			i++;
			j++;
		}
		i=141 + num*512;
		res[j]='\0';
		j = 0;
		index--;
		if(index == 0 && address - num * 512 - 512 < 0){
			return res;
		}
		while(i % 512 < 156 && input[i]!='*') {
			res[j] = input[i];
			i++;
			j++;
		}
		i=156 + num*512;
		res[j]='\0';
		j = 0;
		index--;
		if(index == 0 && address - num * 512 - 512 < 0){
			return res;
		}
		while(i % 512 < 306 && input[i]!='*') {
			res[j] = input[i];
			i++;
			j++;
		}
		i=306 + num*512;
		res[j]='\0';
		j = 0;
		index--;
		if(index == 0 && address - num * 512 - 512 < 0){
			return res;
		}
/*		res[j]='|';
		j++;
		while(i % 512 < 512 && input[i]!='*') {
			res[j] = input[i];
			i++;
			j++;
		}*/
		i=512 + num*512;
	}	
}
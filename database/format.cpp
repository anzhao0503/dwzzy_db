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

char* decode(char* input) {
	char* res = (char*)malloc(sizeof(char));
	int j = 0;
	int i = 0;
	while(i < 512) {
		while(i < 5 && input[i]!= '*') {
			res[j] = input[i];
			i++;
			j++;
		}
		res[j]='|';
		j++;
		i=5;
		while(i < 23 && input[i]!='*') {
			res[j] = input[i];
			i++;
			j++;
		}
		i=23;
		res[j]='|';
		j++;
		while(i < 123 && input[i]!='*') {
			res[j] = input[i];
			i++;
			j++;
		}
		i=123;
		res[j]='|';
		j++;
		while(i < 126 && input[i]!='*') {
			res[j] = input[i];
			i++;
			j++;
		}
		i=126;
		res[j]='|';
		j++;
		while(i < 141 && input[i]!='*') {
			res[j] = input[i];
			i++;
			j++;
		}
		i=141;
		res[j]='|';
		j++;
		while(i < 156 && input[i]!='*') {
			res[j] = input[i];
			i++;
			j++;
		}
		i=156;
		res[j]='|';
		j++;
		while(i < 306 && input[i]!='*') {
			res[j] = input[i];
			i++;
			j++;
		}
		i=306;
		res[j]='|';
		j++;
		while(i < 512 && input[i]!='*') {
			res[j] = input[i];
			i++;
			j++;
		}
		i=512;
	}

	res[j] = '\0';
	return res;
}

/*
 * create_index.cpp
 *
 *  Created on: Nov 1, 2017
 *      Author: dmy
 */
#include "storage.h"
#include "format.h"
#include <iostream>
#include <fstream>
#include "bpt.h"


//ofstream outputfile("data.txt");
int find_item(StorageManagement *storage_manager, int address){
	char* buf = (char*)calloc(sizeof(char)*PAGE_SIZE, sizeof(char));
	int retu = storage_manager->ReadBuffer(address, buf, PAGE_SIZE);
	if (retu != 0)
	{
		char* final = (char*)calloc(sizeof(char)*MAX_TUPLE_SIZE, sizeof(char));
		final = decode(buf,address);
		//outputfile<<final<<'	'<<address<<endl;
		free(final);
	}
	free(buf);
}


int main(int argc, char *argv[]) {
	StorageManagement *storage_manager = new StorageManagement();
	char* name="tmp.txt";
	int ret = storage_manager->InitStorage(name);
	if (ret == -1) return ret;
	FILE* fp;
	char buffer[MAX_TUPLE_SIZE+1];
	if ((fp = fopen("supplier.tbl", "r")) == NULL) {
		cout<<"error"<<endl;
		return -1;
	}
	int j = 0;
	while(j<10000) {
	   fgets(buffer, sizeof(buffer), fp);
	   char* input = (char*)calloc(sizeof(char)*MAX_TUPLE_SIZE+1, sizeof(char));
	   char seg[] = "|";
	   char* substr;
	   substr = strtok(buffer, seg);
	   char* part = encode(substr, "int", 5);
	   memcpy(input, part, 5);
	   substr = strtok(NULL, seg);
	   part = encode(substr, "char", 18);
	   strcat(input, part);

	   substr = strtok(NULL, seg);
	   part = encode(substr, "varchar", 100);
	   strcat(input, part);

	   substr = strtok(NULL, seg);
	   part = encode(substr, "int", 3);
	   strcat(input, part);

	   substr = strtok(NULL, seg);
	   part = encode(substr, "char", 15);
	   strcat(input, part);

	   substr = strtok(NULL, seg);
	   part = encode(substr, "float", 15);
	   strcat(input, part);

	   substr = strtok(NULL, seg);
	   part = encode(substr, "varchar", 150);
	   strcat(input, part);

	   for (int i = strlen(input); i < MAX_TUPLE_SIZE; i++)
		   input[i] = '*';
	   input[MAX_TUPLE_SIZE] = '\0';

	   storage_manager->Write(input, MAX_TUPLE_SIZE);
	   j++;
	   free(input);
	}
	fclose(fp);
/*
	char* buf = (char*)malloc(sizeof(char)*PAGE_SIZE);
	int retu = storage_manager->ReadBuffer(513, buf, PAGE_SIZE);
	if (retu != 0)
	{
		char* final = (char*)calloc(sizeof(char)*MAX_TUPLE_SIZE, sizeof(char));
		final = decode(buf,513);
		cout<<final<<endl;
		free(final);
	}
	free(buf);
*/
	char index_name[16];
	strcpy(index_name, argv[1]);
	strcat(index_name, ".index");
    bpt::bplus_tree database(index_name, true);
    char init[16] = "init";
    database.insert(init, -1);

	int index = atoi(argv[1]);
	for (int i=0; i<5120000; ){
		//find_item(storage_manager, i);
		char* buf = (char*)calloc(sizeof(char)*PAGE_SIZE, sizeof(char));
		int retu = storage_manager->ReadBuffer(i, buf, PAGE_SIZE);
		if (retu != 0)
		{
			char* final = (char*)calloc(sizeof(char)*MAX_TUPLE_SIZE, sizeof(char));
			final = decode_index(buf,i,index);
			cout<<final<<"	"<<i<<endl;
			database.insert(final, i);
			free(final);
		}
		free(buf);
		i += 512;
	}
	printf("done\n");
	//outputfile.close();
	delete storage_manager;
	return 0;
}


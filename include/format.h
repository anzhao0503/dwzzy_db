/*
 * format.h
 *
 *  Created on: Oct 24, 2017
 *      Author: wcw
 */
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

char* encode(char* input, string dtyp, int length);
char* decode(char* input, int address);
char* decode_index(char* input, int address, int index);
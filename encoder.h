#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <stdint.h>
#include <time.h>
#include "meta_info.h"
#define MAX_INT_ASCII_LENGTH 24
#define MAX_FLOAT_ASCII_LENGTH 24
#define MAX_DATE_ASCII_LENGTH 12
#define MAX_VARCHAR_LENGTH 256

using namespace std;

class Encoder {
public:
	static int decode(const char* buf, uint32_t len, void* out, AttrType type, uint32_t* strLen = NULL);
	static int encode(const void* value, char* out, uint32_t* strLen, AttrType type, uint32_t len = 0);
private:
	static int decode_int(const char* buf, uint32_t len, int64_t* out);
	static int decode_float(const char* buf, uint32_t len, float* out);
	static int decode_char(const char* buf, uint32_t len, char* out, uint32_t* strLe);
	static int decode_varchar(const char* buf, uint32_t len, char* out, uint32_t* strLen);
	static int decode_date(const char* buf, uint32_t len, int64_t* out);
	static int encode_int(const int64_t* value, char* out, uint32_t* strLen);
	static int encode_float(const float* value, char* out, uint32_t* strLen);
	static int encode_char(const char* value, char* out, uint32_t* strLen, uint32_t len);
	static int encode_varchar(const char* value, char* out, uint32_t* strLen, uint32_t len);
	static int encode_date(const int64_t* value, char* out, uint32_t* strLen);
};

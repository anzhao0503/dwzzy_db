#include "encoder.h"

int Encoder::decode(const char* buf, uint32_t len, void* out, AttrType type, uint32_t* strLen = NULL){
    //Todo
    //if(...)return -1
    switch(type){
        case INTEGER:
            return decode_int(buf, len, (int64_t*)out);
        case FLOAT:
            return decode_float(buf, len, (float*)out);
        case CHAR:
            return decode_char(buf, len, (char*)out);
        case VARCHAR:
            return decode_varchar(buf, len, (char*)out, strLen);
        case DATE:
            return decode_date(buf, len, (int64_t*)out);
    }
    return -1;
}
int Encoder::encode(const void* value, char* out, uint32_t* strLen, AttrType type, uint32_t len = 0){
    //Todo
    //if(...)return -1
    switch(type){
        case INTEGER:
            return encode_int((int64_t*)value, out, strLen);
        case FLOAT:
            return encode_float((float*)value, out, strLen);
        case CHAR:
            return encode_char((char*)value, out, strLen);
        case VARCHAR:
            return encode_varchar((char*)value, out, strLen, len);
        case DATE:
            return encode_date((int64_t*)value, out, strLen);
    }
    return -1;
}
int Encoder::decode_int(const char* buf, uint32_t len, int64_t* out){
    if(len >= MAX_INT_ASCII_LENGTH){
        return -1;
    }
    char asc_str[MAX_INT_ASCII_LENGTH];
    strncpy(asc_str, buf, len);
    asc_str[len] = '\0';
    *out = (int64_t)atol(asc_str);
    return 0;
}
int Encoder::decode_float(const char* buf, uint32_t len, float* out){
    if(len >= MAX_FLOAT_ASCII_LENGTH){
        return -1;
    }
    char asc_str[MAX_FLOAT_ASCII_LENGTH];
    strncpy(asc_str, buf, len);
    asc_str[len] = '\0';
    *out = (float)atof(asc_str);
    return 0;
}
int Encoder::decode_char(const char* buf, uint32_t len, char* out){
    if(len != 1){
        return -1;
    }
    *out = *buf;
    return 0;
}
int Encoder::decode_varchar(const char* buf, uint32_t len, char* out, uint32_t* strLen){
    if(len >= MAX_VARCHAR_LENGTH){
        return -1;
    }
    *strLen = len;
    strncpy(out, buf, len);
    out[len] = '\0';
    return 0;
}
int Encoder::decode_date(const char* buf, uint32_t len, int64_t* out){
    if(len >= MAX_DATE_ASCII_LENGTH){
        return -1;
    }
    char asc_str[MAX_DATE_ASCII_LENGTH];
    strncpy(asc_str, buf, len);
    asc_str[len] = '\0';
    struct tm time;
    strptime(asc_str, "%Y-%m-%d", &time);
    *out = (int64_t)mktime(&time);
    return 0;
}
int Encoder::encode_int(const int64_t* value, char* out, uint32_t* strLen){
    *strLen = sprintf(out, "%ld", *value);
    return 0;
}
int Encoder::encode_float(const float* value, char* out, uint32_t* strLen){
    *strLen = sprintf(out, "%f", *value);
    return 0;
}
int Encoder::encode_char(const char* value, char* out, uint32_t* strLen){
    *out = *value;
    *strLen = 1;
    return 0;
}
int Encoder::encode_varchar(const char* value, char* out, uint32_t* strLen, uint32_t len){
    *strLen = len;
    strncpy(out, value, len);
    out[len] = '\0';
    return 0;
}
int Encoder::encode_date(const int64_t* value, char* out, uint32_t* strLen){
    struct tm* ptime;
    ptime = gmtime((time_t*)value);
    *strLen = strftime(out, MAX_DATE_ASCII_LENGTH, "%y-%m-%d" ,ptime) - 1 ;
    return 0;
}

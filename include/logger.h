#ifndef LOGGER_H_
#define LOGGER_H_
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<ctime>
#include<cstring>  
#include<pthread.h>  //互斥锁
#include<sys/stat.h>
#include<sys/types.h>
#include<stdarg.h>
#include<sstream>
#include<fstream>


using namespace std;

static const int MAX_STR_LEN = 1024;
static const char * KEYINFOPREFIX   = " Key: \t";
static const char * ERRORPREFIX		= " Error: \t";
static const char * WARNINGPREFIX   = " Warning: \t";
static const char * INFOPREFIX      = " Info: \t";

typedef enum EnumLogLevel
{
	LogLevelAll = 0,    //所有信息都写日志
	LogLevelMid,        //写错误、警告信息
	LogLevelNormal,     //只写错误信息
	LogLevelStop        //不写日志
}EnumLogLevel;

class Logger{
private:
	//写日志文件流
	FILE * m_pFileStream;
	//写日志级别
	EnumLogLevel m_nLogLevel;
	//日志的路径
	char m_strLogPath[MAX_STR_LEN];
	//日志的名称
	char m_strCurLogName[MAX_STR_LEN];
	//线程同步的临界区变量
	//pthread_mutexattr_t m_cs;

public:
	Logger();
	Logger(const char * strLogPath, EnumLogLevel nLogLevel = EnumLogLevel::LogLevelNormal);
	virtual ~Logger();

public:
	//写关键信息
	void TraceKeyInfo(const char * strInfo, ...);
	//写错误信息
	void TraceError(const char* strInfo, ...);
	//写警告信息
	void TraceWarning(const char * strInfo, ...);
	//写一般信息
	void TraceInfo(const char * strInfo, ...);
	//设置写日志级别
	void SetLogLevel(EnumLogLevel nLevel);

private:
	//写文件操作
	void Trace(const char * strInfo);
	//获取当前系统时间
	char * GetCurrentTime();
	//创建日志文件名称
	void GenerateLogName();
	//创建日志路径
	void CreateLogPath();		
};



#endif
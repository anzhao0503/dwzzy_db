#include "../include/logger.h"



Logger::Logger(){
	//初始化
	memset(m_strLogPath, 0, MAX_STR_LEN);
	memset(m_strCurLogName, 0, MAX_STR_LEN);
	m_pFileStream = NULL;
	//设置默认的写日志级别
	m_nLogLevel = EnumLogLevel::LogLevelNormal;
	//初始化临界区变量
	//pthread_mutexattr_init(&m_cs);
	//创建日志文件名
	GenerateLogName();
}

//构造函数
Logger::Logger(const char * strLogPath, EnumLogLevel nLogLevel):m_nLogLevel(nLogLevel)
{
	//初始化
	m_pFileStream = NULL;
	strcpy(m_strLogPath, strLogPath);
	//pthread_mutexattr_init(&m_cs);
	CreateLogPath();
	GenerateLogName();
}

//析构函数
Logger::~Logger()
{
	//释放临界区
	//pthread_mutexattr_destroy(&m_cs);
	//关闭文件流
	if(m_pFileStream)
		fclose(m_pFileStream);
}

//设置写日志级别
void Logger::SetLogLevel(EnumLogLevel nLevel)
{
	m_nLogLevel = nLevel;
}

//获取系统当前时间
char * Logger::GetCurrentTime()
{
	time_t curTime;
	struct tm * pTimeInfo = NULL;
	time(&curTime);
	pTimeInfo = localtime(&curTime);
	char temp[MAX_STR_LEN] = {0};
	sprintf(temp, "%04d-%02d-%02d %02d:%02d:%02d", pTimeInfo->tm_year + 1900, pTimeInfo->tm_mon + 1, pTimeInfo->tm_mday,pTimeInfo->tm_hour, pTimeInfo->tm_min, pTimeInfo->tm_sec);
	char * pTemp = temp;
	return pTemp;	
}

//创建日志文件的名称
void Logger::GenerateLogName()
{
	time_t curTime;
	struct tm * pTimeInfo = NULL;
	time(&curTime);
	pTimeInfo = localtime(&curTime);
	char temp[1024] = {0};
	//日志的名称如：2013-01-01.log
	sprintf(temp, "%04d-%02d-%02d.log", pTimeInfo->tm_year+1900, pTimeInfo->tm_mon + 1, pTimeInfo->tm_mday);
	if(0 != strcmp(m_strCurLogName, temp))
	{
		strcpy(m_strCurLogName,temp);
		if(m_pFileStream)
			fclose(m_pFileStream);
		char temp[1024] = {0};
		strcat(temp, m_strLogPath);
		strcat(temp, m_strCurLogName);
		//以追加的方式打开文件流
		m_pFileStream = fopen(temp, "a+");
	}
}

//创建日志文件的路径
void Logger::CreateLogPath()
{
	if(0 != strlen(m_strLogPath))
	{
		strcat(m_strLogPath, "/");
	}
	fstream _file;
	_file.open(m_strLogPath,ios::in);
	if(!_file)
	{
		int isCreate = mkdir(m_strLogPath,S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
		if(! isCreate)
	 		printf("create path:%s\n",m_strLogPath);
		else
			printf("create path %s failed! error code : %d \n",isCreate,m_strLogPath);	
	}
	else
	{
		cout<<m_strLogPath<<" already exist!\n";
	}

}

//写关键信息接口
void Logger::TraceKeyInfo(const char * strInfo, ...)
{
	if(!strInfo)
		return;
	char pTemp[MAX_STR_LEN] = {0};
	strcpy(pTemp, GetCurrentTime());
	strcat(pTemp, KEYINFOPREFIX);
	//获取可变形参
	va_list arg_ptr;
	va_start(arg_ptr, strInfo);
	vsprintf(pTemp + strlen(pTemp), strInfo, arg_ptr);
	va_end(arg_ptr);
	//写日志文件
	Trace(pTemp);

}

//写错误信息
void Logger::TraceError(const char* strInfo, ...)
{
	//判断当前的写日志级别，若设置为不写日志则函数返回
	if(m_nLogLevel >= EnumLogLevel::LogLevelStop)
		return;
	if(!strInfo)
		return;
	char pTemp[MAX_STR_LEN] = {0};
	strcpy(pTemp, GetCurrentTime());
	strcat(pTemp, ERRORPREFIX);
	va_list arg_ptr;
	va_start(arg_ptr, strInfo);
	vsprintf(pTemp + strlen(pTemp), strInfo, arg_ptr);
	va_end(arg_ptr);
	Trace(pTemp);
}

//写警告信息
void Logger::TraceWarning(const char * strInfo, ...)
{
	//判断当前的写日志级别，若设置为只写错误信息则函数返回
	if(m_nLogLevel >= EnumLogLevel::LogLevelNormal)
		return;
	if(!strInfo)
		return;
	char pTemp[MAX_STR_LEN] = {0};
	strcpy(pTemp, GetCurrentTime());
	strcat(pTemp, WARNINGPREFIX);
	va_list arg_ptr;
	va_start(arg_ptr, strInfo);
	vsprintf(pTemp + strlen(pTemp), strInfo, arg_ptr);
	va_end(arg_ptr);
	Trace(pTemp);
}


//写一般信息
void Logger::TraceInfo(const char * strInfo, ...)
{
	//判断当前的写日志级别，若设置只写错误和警告信息则函数返回
	if(m_nLogLevel >= EnumLogLevel::LogLevelMid)
		return;
	if(!strInfo)
		return;
	char pTemp[MAX_STR_LEN] = {0};
	strcpy(pTemp, GetCurrentTime());
	strcat(pTemp,INFOPREFIX);
	va_list arg_ptr;
	va_start(arg_ptr, strInfo);
	vsprintf(pTemp + strlen(pTemp), strInfo, arg_ptr);
	va_end(arg_ptr);
	Trace(pTemp);
}


void Logger::Trace(const char * strInfo)
{
	if(!strInfo)
		return;
	try
	{
		//进入临界区
		//pthread_mutex_lock(&m_cs);
		//若文件流没有打开，则重新打开
		if(!m_pFileStream)
		{
			char temp[1024] = {0};
			strcat(temp, m_strLogPath);
			strcat(temp, m_strCurLogName);
			m_pFileStream = fopen(temp, "a+");
			if(!m_pFileStream)
			{
				return;
			}
		}
		//写日志信息到文件流
		fprintf(m_pFileStream, "%s\n", strInfo);
		fflush(m_pFileStream);
		//离开临界区
		//pthread_mutex_unlock(&m_cs);
	}
	//若发生异常，则先离开临界区，防止死锁
	catch(...)
	{
		//pthread_mutex_unlock(&m_cs);
	}
}
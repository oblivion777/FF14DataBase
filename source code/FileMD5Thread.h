#pragma once
#include <mutex>
#include <map>
#include "md5.h"
#include "ffdatabase.h"
//#include "mysql/jdbc.h"
//#pragma execution_character_set("utf-8")


#ifndef FILEMD5THREAD_H
#define FILEMD5THREAD_H
using namespace std;
class FileMD5Thread {
private://成员变量
    char* listFile;
    char* outMD5File;
    unsigned short int threadCount = 14;//线程数 
    static int errors;
    static time_t now;
    static unsigned int timeCount;//时间戳计数
    ifstream inFile;
    ofstream outLog;
    //wifstream wInFile;
    //wofstream wOutLog;
    static std::mutex logLock;//日志锁
    std::mutex* sqlLock;//默认所有对象使用日志锁
    
public:  
    //文件类型
    enum class FileType {
        UNKONW, MOD, PICTURE, OTHER
    };
private:/*==========成员函数,对象=========*/
    int fileMD5SumToMySQL(sql::Statement*);
    std::string timeTag(tm*);
    static map<string, FileType>* pFileTypeMap;
public:
    FileMD5Thread(char* in = MODS_LIST_FILE, char* out = OPERATE_MYSQL_LOG_FILE);
    //判断文件类型
    FileType bpFileType(char*);
    //初始化map
    static void initializeFileTypeMap(void);
    //释放map
    static bool releaseFileTypeMap(void);
    //判断文件类型
    //int md5ToFile(void);//MD5输出到文件
    
    //多线程计算MD5
    int run(sql::Connection*);//传入Connection对象写入MySQL数据库
    static void endResetZero(char*, int);
    static void endResetZero(wchar_t*, int);
    void openIoFile();
    void closeIoFile();

    int close() {
        inFile.close();
        outLog.close();
        return 0;
    }
    int setLock(std::mutex* lock) {
        /*设定锁*/
        sqlLock = lock;
        return 0;
    }
    static int getErrors() {
        return errors;
    }
    FileMD5Thread& setThreadCount(int threads) {
        if (threads < 1 || threads > 512) {
            return *this;
        }
        threadCount = threads;
        return *this;
    }
    int getThreadCount() {
        return threadCount;
    }
};
#endif
#pragma once
#pragma once
#include <mutex>
#include "md5.h"
#include "ffdatabase.h"
//#include "mysql/jdbc.h"
//#pragma execution_character_set("utf-8")


#ifndef FILEMD5THREAD_H
#define FILEMD5THREAD_H
using namespace std;
class FileMD5Thread {
private:
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
    std::mutex* sqlLock;//默认所有对象使用相同的锁
    char* FileMD5Thread::modsExtensionName[2] = { "ttmp2","ttmp"};
    char* FileMD5Thread::picsExtensionName[6] = { "jpg","png","gif","bmp","PNG","webp"};
public:  
    enum class FileType//文件类型
    {
        UNKONW, MOD, PICTURE, OTHER
    };
private:
    int fileMd5Sum(sql::Statement*);
    std::string timeTag(tm*);
public:
    FileMD5Thread(char* in = MODS_LIST_FILE, char* out = OPERATE_MYSQL_LOG_FILE);
    FileType bpFileType(char*);
    FileMD5Thread::FileType bpFileType(char* fileName, FileType* fileType);
    //判断文件类型
    //int md5ToFile(void);//MD5输出到文件
    
    int run();
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
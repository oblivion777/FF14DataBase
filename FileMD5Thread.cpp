#pragma once
#include "FileMD5Thread.h"

#define FILE_NAME_PATH_SIZE 512

int FileMD5Thread::fileMd5Sum(sql::Statement* state, ThreadsAction action)
{
    char* buff = new char[FILE_NAME_PATH_SIZE*2];
    char buffMD5[128] = { 0 };
    char fileName[FILE_NAME_PATH_SIZE] = { 0 };
    char filePath[FILE_NAME_PATH_SIZE] = { 0 };

    while (TRUE)
    {
        {
            std::lock_guard<std::mutex> lockguard(*plck);//读取文件
            if (!inFile.getline(buff, FILE_NAME_PATH_SIZE)) {
                return errors;
            }
        }
        try
        {// 捕捉getFileMD5抛出的错误
            strcpy(buffMD5, getFileMD5(buff).c_str());
        }
        catch (...)
        {
            this->endResetZero(buffMD5, 128);
            std::lock_guard<std::mutex> lockguard(logLock);
            errors++;
            outLog << "无法定位文件: " << buff << endl;
            cout << "无法定位文件: " << buff << endl;
        }
        cutStr(buff, filePath, fileName, '\\');
        if (action == ThreadsAction::TO_MYSQL) 
        {   /*写入数据库*/
            sprintf(buff, "insert into mods_test(md5,filename,path) value(\"%s\",\"%s\",\"%s\")", buffMD5, fileName, filePath);
            gbkToUTF8(buff, FILE_NAME_PATH_SIZE);
            try
            {
                std::lock_guard<std::mutex> lockguard(*plck);
                state->executeUpdate(buff);
            }
            catch (...)
            {
                std::lock_guard<std::mutex> lockguard(logLock);
                errors++;
                outLog << buff << endl;
            }
        }
        else if (action == ThreadsAction::TO_FILE)
        {   /*写入文件*/
            std::lock_guard<std::mutex> lockguard(*plck);
            //outFile << buff << endl << "[MD5]" << buffMD5 << endl;//写入文件
            outLog << fileName << " " << filePath << endl;
            outLog << buff << endl << endl;
        }
        else
        {
            cout << "别乱搞!" << endl;
            return 404;
        }
        this->endResetZero(buff, FILE_NAME_PATH_SIZE);
        this->endResetZero(fileName, FILE_NAME_PATH_SIZE);
        this->endResetZero(filePath, FILE_NAME_PATH_SIZE);
    }
    delete[] buff;
    return errors;
}

int FileMD5Thread::run(sql::Connection* conn)
{
    /*传入Connection对象时,写入MySQL数据库
    */
    clock_t start_time = clock();//计时开始

    openIoFile();
    std::mutex lckSQL;//SQL写入锁
    this->plck = &lckSQL;
    sql::Statement* state = conn->createStatement();
    thread* pth = new thread[threadCount];
    if (pth == NULL) {
        return 404;
    }
    int i;
    for (i = 0; i < threadCount; i++) {
        pth[i] = thread(&FileMD5Thread::fileMd5Sum, this, state, ThreadsAction::TO_MYSQL);
    }
    for (i = 0; i < threadCount; i++) {
        pth[i].join();
    }
    //计时结束
    clock_t end_time = clock();
    outLog << "elapsed time:" << (double)clock() / CLK_TCK << "s\n"
        << "error count: " << errors;
    //收尾
    state->close();
    delete state;
    delete[] pth;
    closeIoFile();
    return errors;
}

int FileMD5Thread::run() {
    //clock_t start_time = clock();//计时开始
        //打开保存文件列表的文件
    openIoFile();
    sql::Statement* state = NULL;
    plck = &(this->logLock);
    thread* pth = new thread[threadCount];
    if (pth == NULL) {
        return 404;
    }
    int i;
    for (i = 0; i < threadCount; i++) {
        pth[i] = thread(&FileMD5Thread::fileMd5Sum, this, state, ThreadsAction::TO_FILE);//危险行为!!!!!!
    }
    for (i = 0; i < threadCount; i++) {
        pth[i].join();
    }
    //计时结束
    //clock_t end_time = clock();
    //cout << (double)clock() / CLK_TCK << "s" << endl;
    //outFile << endl << "耗时:" << (double)clock() / CLK_TCK << "s" << endl;
    closeIoFile();
    delete[] pth;
    return errors;
}

void FileMD5Thread::endResetZero(char* str,int strSize)
{
    for (int i = 0; i < strSize; i++) {
        str[i] = '\0';
    }
    /*
    for (int i = strSize - 1; i > strlen(str) - 1; i--) {
        str[i] = '\0';
    }
    */
}

void FileMD5Thread::openIoFile()
{
    this->inFile.open(listFile, ios::in);
    if (!(inFile.is_open())) {
        cout << "读取文件失败!" << endl;
        throw "File does not exist!";
    }
    //输出文件的路径
    this->outLog.open(outMD5File, ios::out);
    if (!(outLog.is_open())) {
        cout << "打开文件失败!" << endl;
        throw "Failed to open file";
    }
}

void FileMD5Thread::closeIoFile()
{
    this->inFile.close();
    this->outLog.close();
}

#undef FILE_NAME_PATH_SIZE

/*初始化*/
int FileMD5Thread::errors = 0;
std::mutex FileMD5Thread::logLock;

FileMD5Thread::FileMD5Thread( char* listFile,  char* outMD5File)
{
    this->listFile = listFile;
    this->outMD5File = outMD5File;
    plck = &(this->logLock);
}


/*
int FileMD5Thread::md5ToFile(void) {
    char buff[FILE_NAME_PATH_SIZE] = { 0 };
    char buffMD5[128] = { 0 };
    char fileName[FILE_NAME_PATH_SIZE] = { 0 };
    char filePath[FILE_NAME_PATH_SIZE] = { 0 };
    while (TRUE)
    {
        {
            std::lock_guard<std::mutex> lockguard(*plck);
            if (!inFile.getline(buff, FILE_NAME_PATH_SIZE)) {
                return errors;
            }
        }
        //this->endResetZero(buff, FILE_NAME_PATH_SIZE);
        cutStr(buff, filePath, fileName, '\\');

        try
        {// 捕捉getFileMD5抛出的错误
            strcpy(buffMD5, getFileMD5(buff).c_str());
        }
        catch (...)
        {
            std::lock_guard<std::mutex> lockguard(*plck);
            errors++;
            cout << "无法定位文件: " << buff << endl;
        }
        {
            std::lock_guard<std::mutex> lockguard(*plck);
            //outFile << buff << endl << "[MD5]" << buffMD5 << endl;//写入文件
            outLog << fileName << " " << filePath << endl;
            outLog << buff << endl << endl;
        }
        this->endResetZero(buff, FILE_NAME_PATH_SIZE);
        this->endResetZero(fileName, FILE_NAME_PATH_SIZE);
        this->endResetZero(filePath, FILE_NAME_PATH_SIZE);
    }

    return errors;
}
*/
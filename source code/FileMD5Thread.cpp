#include "FileMD5Thread.h"
//#pragma once


int FileMD5Thread::fileMD5SumToMySQL(sql::Statement* state)
{
    typedef char MYSQL_CHAR;
    constexpr int FILE_NAME_PATH_SIZE = 256;
    //char* buff = new char[FILE_NAME_PATH_SIZE*2];
    MYSQL_CHAR buff[FILE_NAME_PATH_SIZE * 2] = { 0 };
    wstring wstrFullFilePath;
    string pathWithFileMD5;
    MYSQL_CHAR buffMD5[128] = { 0 };
    MYSQL_CHAR fileName[FILE_NAME_PATH_SIZE] = { 0 };
    MYSQL_CHAR filePath[FILE_NAME_PATH_SIZE] = { 0 };
    tm* ltm = new tm;
    FileType fileType = FileType::UNKONW;
    while (inFile.getline(buff, FILE_NAME_PATH_SIZE))
    {
        //wcstombs(buff,wstrFullFilePath, FILE_NAME_PATH_SIZE*2);
        try
        {// 获取文件MD5
            wstrFullFilePath = StrConvertor::utf8ToUnicode(buff);
            strcpy(buffMD5, getFileMD5W(wstrFullFilePath.c_str()).c_str());
        }
        catch (...)
        {
            this->endResetZero(buffMD5, 128);
            std::lock_guard<std::mutex> lockguard(logLock);
            errors++;
            outLog << "无法定位文件: " << buff << "\n";
            cout << "无法定位文件: " << buff << endl;
            continue;
        }

        StrConvertor::cutStr(buff, filePath, fileName, '\\');

        bpFileType(fileName, &fileType);//判断文件类型
        pathWithFileMD5.assign(filePath).append(buffMD5);
        pathWithFileMD5.assign(md5::digestString(pathWithFileMD5.c_str()));

        /*写入数据库*/
        try
        {
            std::lock_guard<std::mutex> lockguard(*sqlLock);
            switch (fileType)
            {
            case FileMD5Thread::FileType::MOD: {
                sprintf(buff, "INSERT INTO mods(id,filename,path,md5,path_with_file_md5) VALUE(\"%s\",\"%s\",\"%s\",\"%s\",\"%s\")"\
                    , timeTag(ltm).c_str(), fileName, filePath, buffMD5, pathWithFileMD5.c_str());
                state->executeUpdate(buff);
                break;
            }
            case FileMD5Thread::FileType::PICTURE: {
                sprintf(buff, "INSERT INTO preview_pics(id,filename,path,pic_md5) VALUE(\"%s\",\"%s\",\"%s\",\"%s\")"\
                    , timeTag(ltm).c_str(), fileName, filePath, buffMD5);
                state->executeUpdate(buff);
                break;
            }
            case FileMD5Thread::FileType::OTHER: {
                sprintf(buff, "INSERT INTO other(id,filename,path,md5) VALUE(\"%s\",\"%s\",\"%s\",\"%s\")"\
                    , timeTag(ltm).c_str(), fileName, filePath, buffMD5);
                state->executeUpdate(buff);
                break;
            }
            default:
                break;
            }
        }
        catch (...)
        {
            std::lock_guard<std::mutex> lockguard(logLock);
            errors++;
            outLog << "SQL syntax error: " << buff << endl;
        }

        this->endResetZero(buff, FILE_NAME_PATH_SIZE * 2);
        this->endResetZero(fileName, FILE_NAME_PATH_SIZE);
        this->endResetZero(filePath, FILE_NAME_PATH_SIZE);
        fileType = FileType::UNKONW;
    }
    //delete[] buff;
    delete ltm;
    return errors;
}




int FileMD5Thread::run(sql::Connection* conn)
{
    /*传入Connection对象时,写入MySQL数据库
    */
    clock_t start_time = clock();//计时开始

    openIoFile();
    std::mutex lckSQL;//SQL写入锁
    this->sqlLock = &lckSQL;
    sql::Statement* state = conn->createStatement();
    thread* pth = new thread[threadCount];
    if (pth == NULL) {
        return -404;
    }
    int i;
    for (i = 0; i < threadCount; i++) {
        pth[i] = thread(&FileMD5Thread::fileMD5SumToMySQL, this, state);
    }
    for (i = 0; i < threadCount; i++) {
        pth[i].join();
    }
    //计时结束
    clock_t end_time = clock();
    outLog << "elapsed time: " << (double)clock() / CLK_TCK << "s\n"
        << "error count: " << errors;
    //收尾
    state->close();
    delete state;
    delete[] pth;
    closeIoFile();
    return errors;
}

void FileMD5Thread::endResetZero(char* str, int strSize)
{
    for (int i = 0; i < strSize; i++) {
        str[i] = '\0';
    }
}

void FileMD5Thread::endResetZero(wchar_t* str, int strSize)
{
    for (int i = 0; i < strSize; i++) {
        str[i] = L'\0';
    }
}

void FileMD5Thread::openIoFile()
{
    this->inFile.open(listFile, ios::in);
    //this->wInFile.open(listFile, ios::in);
    if (!(inFile.is_open()/*&& wInFile.is_open()*/)) {
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
    //this->wInFile.close();
}

std::string FileMD5Thread::timeTag(tm* ltm) {
    (now == time(0)) ? (timeCount++) : (timeCount = 0);
    now = time(0);

    //tm* ltm = new tm;
    constexpr int TIME_STR_LEN = 30;
    char timeStr[TIME_STR_LEN] = { 0 };
    now = time(0);
    localtime_s(ltm, &now);
    sprintf_s<TIME_STR_LEN>(timeStr, "%d%02d%02d-%02d%02d%02d-%04x",
        1900 + ltm->tm_year, ltm->tm_mon + 1, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec, timeCount);
    return std::string(timeStr);
}



/***********初始化***********/
int FileMD5Thread::errors = 0;
unsigned int FileMD5Thread::timeCount = 0;
time_t FileMD5Thread::now = 0;
std::mutex FileMD5Thread::logLock;



FileMD5Thread::FileMD5Thread(char* listFile, char* outMD5File)
{
    this->listFile = listFile;
    this->outMD5File = outMD5File;
    sqlLock = &(this->logLock);
}

FileMD5Thread::FileType FileMD5Thread::bpFileType(char* fileName)
{
    FileMD5Thread::FileType fileType = FileType::UNKONW;
    for (int i = 0; i < sizeof(this->modsExtensionName) / sizeof(char*); i++) {
        if (!(strcmp(modsExtensionName[i], StrConvertor::getExtensionName(fileName)))) {
            fileType = FileType::MOD;
            break;
        }
    }
    for (int i = 0; i < sizeof(this->picsExtensionName) / sizeof(char*); i++) {
        if (!(strcmp(picsExtensionName[i], StrConvertor::getExtensionName(fileName)))) {
            fileType = FileType::PICTURE;
            break;
        }
    }
    return fileType;
}

FileMD5Thread::FileType FileMD5Thread::bpFileType(char* fileName, FileType* fileType)
{
    for (int i = 0; i < sizeof(this->modsExtensionName) / sizeof(char*); i++) {
        if (!(strcmp(modsExtensionName[i], StrConvertor::getExtensionName(fileName)))) {
            *fileType = FileType::MOD;
            return FileType::MOD;
        }
    }
    for (int i = 0; i < sizeof(this->picsExtensionName) / sizeof(char*); i++) {
        if (!(strcmp(picsExtensionName[i], StrConvertor::getExtensionName(fileName)))) {
            *fileType = FileType::PICTURE;
            return FileType::PICTURE;
        }
    }
    *fileType = FileType::OTHER;
    return FileType::OTHER;
}

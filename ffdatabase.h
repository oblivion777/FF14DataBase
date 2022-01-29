#include <iostream>
#include <windows.h>
#include <string>
#include <time.h>
#include <thread>
#include <fstream>
#include <atomic>

#include "mysql/jdbc.h"
//#pragma execution_character_set("utf-8")
#pragma once
#ifndef FFDATABASE_H
#define FFDATABASE_H

void listFilesCurrent(const char* dir);
void listFilesCurrentW(wchar_t* dir);
void listFiles(const char* dir, std::ofstream&);
bool cutStr(char* full, char* front, char* back, char flag);
void gbkToUTF8(char*, int);
void toUTF8(char* target, int targetCapacity, char* flag);
#endif

#pragma once
#ifndef FF14_DATABASE_OPERATE_FILES
#define FF14_DATABASE_OPERATE_FILES

#define MODS_LIST_FILE "_log/file_list.txt"
#define OPERATE_MYSQL_LOG_FILE "_log/mysql_log.txt"
#endif

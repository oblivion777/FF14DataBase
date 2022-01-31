#include <iostream>
#include <windows.h>
#include <string>
#include <time.h>
#include <thread>
#include <fstream>
#include <atomic>
/*==================================================*/
#include "FileMD5Thread.h"
#include "mysql/jdbc.h"
#include "StrConvertor.h"
#pragma execution_character_set("utf-8")

#pragma once
#ifndef FFDATABASE_H
#define FFDATABASE_H

//constexpr char* MODS_LIST_FILE = "_log/file_list.txt";
constexpr char* MODS_LIST_FILE = "_log/fileList-utf8.txt";
constexpr char* OPERATE_MYSQL_LOG_FILE = "_log/mysql_log.txt";
#endif

#define LISTFILES_IN_FFDATABASE_H_
#ifndef LISTFILES_IN_FFDATABASE_H_
void listFilesCurrent(const char* dir);
void listFilesCurrentW(wchar_t* dir);
void listFiles(const char* dir, std::ofstream&);
#endif
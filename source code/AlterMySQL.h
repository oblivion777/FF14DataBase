#pragma once
#include "ffdatabase.h"

class AlterMySQL
{
public:
    //����driver��ָ��
    static sql::Connection* connect(sql::mysql::MySQL_Driver* = nullptr);
    static void setTableModType(sql::Connection* conn);
};


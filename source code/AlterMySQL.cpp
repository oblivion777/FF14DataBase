#include "AlterMySQL.h"

sql::Connection* AlterMySQL::connect(sql::mysql::MySQL_Driver* driver) {
    //³õÊ¼»¯Çý¶¯
    sql::Connection* con = nullptr;
    ifstream loginInfo;
    constexpr int loginInfoLen = 256;
    std::string url;
    std::string username;
    std::string password;
    char loginInfoBuff[loginInfoLen] = { 0 };
    loginInfo.open("_log/login_info.txt", ios::in);
    while (loginInfo.getline(loginInfoBuff, loginInfoLen))
    {
        if ((strstr(loginInfoBuff, "url: "))) {
            url.assign(loginInfoBuff + strlen("url: "));
        }
        else if ((strstr(loginInfoBuff, "username: "))) {
            username.assign(loginInfoBuff + strlen("username: "));
        }
        else if ((strstr(loginInfoBuff, "password: "))) {
            password.assign(loginInfoBuff + strlen("password: "));
        }
    }
    try
    {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect(url, username, password);
    }
    catch (...)
    {
        cout << "connect failed!" << endl;
        system("pause");
        exit(1);
    }
    cout << "connect suceess!" << endl;
    return con;
}

 void AlterMySQL::setTableModType(sql::Connection* conn) {
     sql::Statement* state = conn->createStatement();
     ifstream sqlSyntax;
     constexpr int buffLen = 256;
     char sqlSyntaxBuff[buffLen];
     sqlSyntax.open("_log/set_mods_type.sql", ios::in);
     while (sqlSyntax.getline(sqlSyntaxBuff, buffLen)) {
         state->execute(sqlSyntaxBuff);
     }
     state->close();
     sqlSyntax.close();
 }
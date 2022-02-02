#include "ffdatabase.h"
#include "mysql/jdbc.h"

using namespace std;
//void fileList1();
sql::Connection* connect();
void setTableModType(sql::Connection* conn);
int main(int argc,char *argv[]) {

    fileListAll(L"E:\\Games\\FFXIVMODS");

#define TEST_MYSQL
#ifdef TEST_MYSQL
    //system("D:/FF14DataBase/PythonProgram/Python-listFile.py");
    FileMD5Thread sqlTest = FileMD5Thread();
    sql::Connection* conn = connect();
    sqlTest.run(conn);
    //sqlTest.run();
    setTableModType(conn);
    conn->close();
#endif // TEST_MYSQL


#ifdef _DEBUG
    system("pause");
#endif // DEBUG
    return 0;
}


sql::Connection* connect() {
    //初始化驱动
    sql::mysql::MySQL_Driver* driver = NULL;
    sql::Connection* con = NULL;
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
            url.append(loginInfoBuff + strlen("url: "));
        }
        else if ((strstr(loginInfoBuff, "username: "))) {
            username.append(loginInfoBuff + strlen("username: "));
        }
        else if ((strstr(loginInfoBuff, "password: "))) {
            password.append(loginInfoBuff + strlen("password: "));
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

void setTableModType(sql::Connection* conn) {
    sql::Statement* state = conn->createStatement();
    ifstream sqlSyntax;
    constexpr int buffLen = 256;
    char sqlSyntaxBuff[buffLen];
    sqlSyntax.open("_log/set_mods_type.sql",ios::in);
    while (sqlSyntax.getline(sqlSyntaxBuff, buffLen)) {
        state->execute(sqlSyntaxBuff);
    }
    state->close();
    sqlSyntax.close();
}


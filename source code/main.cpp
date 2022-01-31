#include "ffdatabase.h"
#include "mysql/jdbc.h"

using namespace std;
//void fileList1();
sql::Connection* connect();

int main(int argc,char *argv[]) {
    //fileList1();
    //listFilesCurrent("E:\\Games\\MOD\\*.*");
    FileMD5Thread sqlTest = FileMD5Thread();
    sql::Connection* conn = connect();
    sqlTest.run(conn);
    //sqlTest.run();

    //conn->createStatement()->executeUpdate("insert into mods_test(filename) value('安东风安赛飞东方安赛飞')");

    conn->close();
    //wprintf(L"Kräuter Body 2.0");
    //listFilesCurrentW(L"E:/Games/MOD/[Gear NSFW]/[Bizu]/*");

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




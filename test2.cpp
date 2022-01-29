#include <iostream>
#include <windows.h>
#include <string>
#include <time.h>
#include <fstream>
#include <mutex>

#include "FileMD5Thread.h"
#include "ffdatabase.h"

#include <icu.h>



using namespace std;
void fileList1();
sql::Connection* connect();

locale loc("chs");//windows下ok
int main(int argc,char *argv[]) {
    fileList1();
    //listFilesCurrent("E:\\Games\\MOD\\*.*");
    FileMD5Thread sqlTest = FileMD5Thread();
    sql::Connection* conn = connect();
    //sqlTest.run(conn);
    //sqlTest.run();
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

    loginInfo.open("_log/login_info.txt",ios::in);
    while (loginInfo.getline(loginInfoBuff, loginInfoLen))
    { 
        if ((strstr(loginInfoBuff, "url:\t"))) {
            url.append(loginInfoBuff + strlen("url:\t"));
        }
        else if ((strstr(loginInfoBuff, "username:\t"))) {
            username.append(loginInfoBuff + strlen("username:\t"));
        }    
        else if ((strstr(loginInfoBuff, "password:\t"))) {
            password.append(loginInfoBuff + strlen("password:\t"));
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
        return NULL;
    }
    cout << "connect suceess!" << endl;
    return con;
}

void fileList1() {
    //char dir[] = "D:\\Games\\MODconfig";
    //char dir[] = "E:\\Games\\Final Fantasy XIV\\最终幻想XIV\\game\\sqpack\\ffxiv";
    char dir[] = "F:\\[FFXIV]MODS\\MOD";

    ofstream outFile;
    outFile.open(MODS_LIST_FILE, ios::out);
    if (!(outFile.is_open())) {
        cout << "打开文件失败!" << endl;
        return;
    }
    listFiles(dir, outFile);
    outFile.close();
    return;
}
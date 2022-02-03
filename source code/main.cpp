#include "ffdatabase.h"
#include "mysql/jdbc.h"

using namespace std;
//void fileList1();

int main(int argc,char *argv[]) {

    fileListAll(L"E:\\Games\\FFXIVMODS");

#define TEST_MYSQL
#ifdef TEST_MYSQL
    //system("D:/FF14DataBase/PythonProgram/Python-listFile.py");
    FileMD5Thread sqlTest = FileMD5Thread();
    sql::mysql::MySQL_Driver* driver = nullptr;
    sql::Connection* conn = AlterMySQL::connect();
    
    sqlTest.run(driver);
    //sqlTest.run();
    AlterMySQL::setTableModType(conn);
    conn->close();
    //cout << sqlTest.close() << sqlTest.close() << sqlTest.close() << endl;

#endif // TEST_MYSQL

    
#ifdef _DEBUG
    system("pause");
#endif // DEBUG
    return 0;
}





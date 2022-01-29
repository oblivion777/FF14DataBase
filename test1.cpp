#include <iostream>
#include <windows.h>
#include <string>
#include <time.h>

#include "ffdatabase.h"


void listFilesCurrent(const char* dir);
void listFiles(const char* dir, std::ofstream&);


int main233() {
    using namespace std;
   

    char dir[]= "D:\\Games\\MODconfig";

    ofstream outFile;
    outFile.open("temp.txt", ios::out);

    clock_t start_time = clock();//计时开始
    listFiles(dir, outFile);
    clock_t end_time = clock();//计时结束

    
    char tmp[20];
    sprintf(tmp, "\nTime Used:%.4fs", (double)(end_time - start_time) / CLOCKS_PER_SEC);
    outFile << tmp ;
    outFile.close();
    //system("pause");
    return 0;
}



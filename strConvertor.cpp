#pragma once
#include <iostream>
#include <string.h>
#include <icu.h>

#ifndef CUT_STR
#define CUT_STR
bool cutStr(char* full, char* front, char* back, char flag) {
    /*
       输入字符串且flag为'/':  /question/53762109
       front=/question/
       back=53762109
    */
    char* pBack = strrchr(full, flag);
    for (int i = 0; i < (strlen(pBack)-1); i++) {
        back[i] = pBack[i+1];
    }

    for (int i = 0; i < (strlen(full)-strlen(back)); i++) {
        if (full[i] == '\\') {
            front[i] = '/';//将'\'改为'/'
        }
        else
        {
            front[i] = full[i];
        }
        
    }
    return true;
}
#endif

#ifndef DEFAULT_TO_TF8_
#define DEFAULT_TO_TF8_
void gbkToUTF8(char* target,int targetCapacity) {
    using namespace std;
    UErrorCode err = U_ZERO_ERROR;
    UConverter* cnvt = ucnv_open(NULL, &err);

    ucnv_toAlgorithmic(UCNV_UTF8, cnvt, target, targetCapacity, target, strlen(target), &err);
    //cout << strlen(target) << endl << target << endl;
}
#endif

#ifndef ANY_CHAR_SET_TO_TF8_
#define ANY_CHAR_SET_TO_TF8_
void toUTF8(char* target, int targetCapacity,char* flag) {
    //char tmp[1024] = { 0 };
    using namespace std;
    UErrorCode err = U_ZERO_ERROR;
    UConverter* cnvt = ucnv_open(NULL, &err);

    ucnv_toAlgorithmic(UCNV_UTF8, cnvt, target, targetCapacity, target, strlen(target), &err);
    //cout << strlen(target) << endl << target << endl;
}
#endif
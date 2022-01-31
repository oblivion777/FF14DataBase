#pragma once
#include <iostream>
#include <string.h>
#include <icu.h>
#include <codecvt>
#ifndef STR_CONVERTOR_H
#define STR_CONVERTOR_H
class StrConvertor {
public:
    static bool cutStr(char* full, char* front, char* back, char flag) {
        /*
           输入字符串且flag为'/':  /question/53762109
           front=/question/
           back=53762109
        */
        char* pBack = strrchr(full, flag);
        for (int i = 0; i < (strlen(pBack) - 1); i++) {
            back[i] = pBack[i + 1];
        }

        for (int i = 0; i < (strlen(full) - strlen(back)); i++) {
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

    static bool cutStr(wchar_t* full, wchar_t* front, wchar_t* back, wchar_t flag) {
        /*
           输入字符串且flag为'/':  /question/53762109
           front=/question/
           back=53762109
        */
        wchar_t* pBack = wcsrchr(full, flag);
        for (int i = 0; i < (wcslen(pBack) - 1); i++) {
            back[i] = pBack[i + 1];
        }

        for (int i = 0; i < (wcslen(full) - wcslen(back)); i++) {
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


    static void gbkToUTF8(char* target, int targetCapacity) {
        using namespace std;
        UErrorCode err = U_ZERO_ERROR;
        UConverter* cnvt = ucnv_open(NULL, &err);

        ucnv_toAlgorithmic(UCNV_UTF8, cnvt, target, targetCapacity, target, strlen(target), &err);
        //cout << strlen(target) << endl << target << endl;
    }


    static void toUTF8(char* target, int targetCapacity, char* flag) {
        //char tmp[1024] = { 0 };
        using namespace std;
        UErrorCode err = U_ZERO_ERROR;
        UConverter* cnvt = ucnv_open(NULL, &err);

        ucnv_toAlgorithmic(UCNV_UTF8, cnvt, target, targetCapacity, target, strlen(target), &err);
        //cout << strlen(target) << endl << target << endl;
    }



    static std::wstring UTF8ToUnicode(const std::string& str)
    {
        std::wstring ret;
        try {
            std::wstring_convert< std::codecvt_utf8<wchar_t> > wcv;
            ret = wcv.from_bytes(str);
        }
        catch (...) {
            return nullptr;
        }
        return ret;
    }
};

#endif
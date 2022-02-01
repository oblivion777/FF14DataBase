#include <stdlib.h>
#include <fstream>
#include <windows.h>
#include <codecvt>
#include <iostream>
#include <fstream>
#include "md5.h"

#include <sstream>
#include <memory>
#include <iomanip>
#include <ctime>
//#pragma execution_character_set("utf-8")

std::wstring UTF8ToUnicode(const std::string& str);
std::string timeTag(unsigned int);
using namespace std;



int main() {
	
	/*
	ofstream ofs;
	ofs.open(L"Krauter.txt");

	ofs << "Kräuter赛烦死安东风" << endl;
	ofs << "Kräuter☣☤✘☒♛▼♫⌘爱扥a" << endl;
	ofs.close();
	*/
	string timesss;
	timesss.assign(timeTag(556));
	cout<<timesss << endl<<strlen(timesss.c_str());


	return 0;
}

#include <codecvt>
std::wstring UTF8ToUnicode(const std::string& str)
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

//时间戳
std::string timeTag(unsigned int timeCount) {
	time_t now = time(0);
	tm* ltm = new tm;
	char timeStr[100] = { 0 };
		now = time(0);
		localtime_s(ltm, &now);
		sprintf_s<100>(timeStr, "%d%02d-%02d%02d-%02d%02d-%04x",
			1900 + ltm->tm_year, ltm->tm_mon + 1,ltm->tm_mday ,ltm->tm_hour, ltm->tm_min, ltm->tm_sec, timeCount);
	return std::string(timeStr);
}


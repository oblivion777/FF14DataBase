#include <stdlib.h>

#include <codecvt>
#include <iostream>
#include <fstream>
#include "md5.h"

#pragma execution_character_set("utf-8")

std::wstring UTF8ToUnicode(const std::string& str);
using namespace std;
int main() {

	ofstream ofs;
	ofs.open(L"Krauter.txt");
	
	ofs << "Kräuter赛烦死安东风" << endl;
	ofs << "Kräuter☣☤✘☒♛▼♫⌘爱扥a" << endl;
	ofs.close();

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
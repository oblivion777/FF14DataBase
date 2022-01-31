#include <stdlib.h>

#include <codecvt>
#include <iostream>
#include <fstream>
#include "md5.h"

#pragma execution_character_set("utf-8")

std::wstring UTF8ToUnicode(const std::string& str);
using namespace std;
int main() {
	cout << getFileMD5("Krauter.txt") << endl;
	cout << getFileMD5W(L"Kräuter.txt") << endl;
	ifstream ifs;
	ifs.open(L"Kräuter.txt");
	//ifs.imbue(locale("", locale::ctype));
	char aaa[50];
	ifs.getline(aaa,50);
	printf(aaa);
	

	ofstream ofs;
	ofs.open(L"Krauter.txt");
	
	//ofs << aaa << endl;
	char bbb[] = "Kräuter啊风";
	//ofs << aaa;
	ofs << bbb << endl << bbb << endl;
	ofs << aaa << endl << aaa << endl;
	ofs.close();
	wstring* pccc=nullptr;
	wstring ccc;
	ccc = UTF8ToUnicode(aaa);
	ofs.open(ccc);
	ofs.imbue(locale("", locale::ctype));
	ofs << ccc.c_str() << endl;


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
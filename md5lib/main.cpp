/*

#include <iostream>
#include <fstream>
#include "md5.h"
#pragma execution_character_set("utf-8")

using namespace std;
int main() {
	cout << getFileMD5("Krauter.txt") << endl;
	cout << getFileMD5W(L"Kräuter.txt") << endl;
	wifstream ifs;
	ifs.open(L"Kräuter.txt");
	//ifs.is_open();

	wchar_t tmp[77];
	wofstream ofs;
	ofs.open("Krauter.txt");
	
	while (ifs.getline(tmp, 77)) {
		ofs << tmp << L"\n";
	}


	return 0;
}

*/
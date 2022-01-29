#include "ffdatabase.h"
#include <mutex>
#include "md5.h"



using namespace std;
mutex mLock;
void writeToFile(const char* s1, ofstream& outFile) {
    char tmp[500];
    outFile << s1 << endl;
    printf("\n%s %d", s1,(int)strlen(s1));
    return;
}


void listFiles(const char* dir, ofstream& outFile)
{
    using namespace std;

    HANDLE hFind;
    WIN32_FIND_DATA findData;
    LARGE_INTEGER size;
    char dirNew[MAX_PATH];
    char filePath[MAX_PATH];

    thread t;
    //char filePath[MAX_PATH];
    // 向目录加通配符，用于搜索第一个文件 
    strcpy(dirNew, dir);
    strcat(dirNew, "\\*.*");

    hFind = FindFirstFile(dirNew, &findData);
    do
    {
        // 是否是文件夹，并且名称不为"."或".." 
        if ((findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            && strcmp(findData.cFileName, ".")
            && strcmp(findData.cFileName, ".."))
        {
            // 将dirNew设置为搜索到的目录，并进行下一轮搜索 
            strcpy(dirNew, dir);
            strcat(dirNew, "\\");
            strcat(dirNew, findData.cFileName);
            listFiles(dirNew, outFile);
        }
        else if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
            && strcmp(findData.cFileName, ".")
            && strcmp(findData.cFileName, ".."))
        {
            size.LowPart = findData.nFileSizeLow;
            size.HighPart = findData.nFileSizeHigh;
            //cout << findData.cFileName << "\t" << size.QuadPart << " bytes\n";

            /*
            strcpy(filePath, dir);
            strcat(filePath, "\\");
            strcat(filePath, findData.cFileName);
            writeToFile(filePath, outFile);
            */
            outFile << dir << "\\" << findData.cFileName << endl;
            //cout << dir << "\\" << findData.cFileName << endl;
        }
    } while (FindNextFile(hFind, &findData));
    FindClose(hFind);

    return;
}

void listFilesCurrent(const char* dir)
{
    using namespace std;
    HANDLE hFind;
    WIN32_FIND_DATA findData;
    LARGE_INTEGER size;
    hFind = FindFirstFile(dir, &findData);

    ofstream oft;
    oft.open("temppp.txt", ios::out);
    char filePath[MAX_PATH];
    string path(dir, strlen(dir) - 3);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        cout << "Failed to find first file!\n";
        return;
    }
    do
    {
        // 忽略"."和".."两个结果 
        if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)
            continue;
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)    // 是否是目录 
        {
            cout << findData.cFileName << "\t<dir>\n";
        }
        else if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
        {
            size.LowPart = findData.nFileSizeLow;
            size.HighPart = findData.nFileSizeHigh;
            cout << findData.cFileName << "\t" << size.QuadPart << " bytes\n";

            //toUTF8(findData.cFileName, 260, findData.cFileName);
            oft << findData.cFileName << endl;
            //cout << path << findData.cFileName << endl;


            //strcpy(filePath, path.c_str());
            //strcat(filePath, findData.cFileName);
            //printf("%s", filePath);
            //cout << "\n" << getFileMD5(filePath) << endl;
            //thread t(getFileMD5, filePath);
        }
    } while (FindNextFile(hFind, &findData));
    cout << "\nDone!\n";
}

void listFilesCurrentW(wchar_t* dir)
{
    using namespace std;
    HANDLE hFind;
    LPWIN32_FIND_DATAW findData;
    findData = new WIN32_FIND_DATAW;
    LARGE_INTEGER size;
    hFind = FindFirstFileW(dir, findData);
    wofstream woft("temppp.txt",ios::out);
    //woft.open(L"temppp.txt", ios::out);

    woft.imbue(std::locale("chs"));
    char filePath[MAX_PATH];
    //string path(dir, strlen(dir) - 3);//路径
    if (hFind == INVALID_HANDLE_VALUE)
    {
        cout << "Failed to find first file!\n";
        return;
    }
    do
    {
        // 忽略"."和".."两个结果 
        if (wcscmp(findData->cFileName, L".") == 0 || wcscmp(findData->cFileName, L"..") == 0)
            continue;
        if (findData->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)    // 是否是目录 
        {
            //cout << findData->cFileName << "\t<dir>\n";
        }
        else if (!(findData->dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
        {
            size.LowPart = findData->nFileSizeLow;
            size.HighPart = findData->nFileSizeHigh;
            //cout << *(findData->cFileName) << "\t" << size.QuadPart << " bytes\n";

            //toUTF8(findData.cFileName, 260, findData.cFileName);
            //oft << findData->cFileName << endl;
            //cout << findData->cFileName << endl;

            wprintf(findData->cFileName); printf("\n");
            woft << findData->cFileName << endl;
            //woft << endl << (findData->cFileName) << endl;
            
            //cout << endl;
            //strcpy(filePath, path.c_str());
            //strcat(filePath, findData.cFileName);
            //printf("%s", filePath);
            //cout << "\n" << getFileMD5(filePath) << endl;
            //thread t(getFileMD5, filePath);
        }
    } while (FindNextFileW(hFind, findData));
    cout << "\nDone!\n";
}
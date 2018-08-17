// BigReader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//#define NULL = 0
#define BUFF_SIZE 4096*1024
//#define OFFSET 97;

namespace fs = std::experimental::filesystem;

class Collector
{
public:
	std::list<fs::path> BooksList;

	void CollectBooksRecursively(std::string patch)
	{
		fs::path Patch = patch;
		for (auto & p : fs::recursive_directory_iterator(Patch))
		{
			if(p.path().extension() == ".txt")
			{
				BooksList.push_back(p.path());
			}
		}
	}
};

//class Collector
//{
//public:
//	std::vector<fs::path> BooksList;
//
//	void CollectBooksRecursively(LPCTSTR lpFolder)
//	{
//		TCHAR szFullPattern[MAX_PATH];
//
//		PathCombine(szFullPattern, lpFolder, _T("*"));
//
//		WIN32_FIND_DATA findFileData;
//		HANDLE handle = FindFirstFile(szFullPattern, &findFileData);
//
//		if(handle != INVALID_HANDLE_VALUE)
//		{
//			do
//			{
//				PathCombine(szFullPattern, lpFolder, findFileData.cFileName);
//
//				if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
//				{
//					CollectBooksRecursively(szFullPattern);
//				}
//				if (findFileData.cFileName == L"*.txt")
//				{
//					BooksList.push_back(szFullPattern);
//				}
//			} while (FindNextFile(handle, &findFileData));
//
//			FindClose(handle);
//		}
//	}
//};


static char st_tolmap[127];
void init()
{
	for(int i = 'A'; i < 'Z'; i++)
	{
		st_tolmap[i] = tolower(i);
	}
	for (int i = 'a'; i < 'z'; i++)
	{
		st_tolmap[i] = i;
	}
}
inline char tol(char ch)
{
	return st_tolmap[ch];

}
inline bool alpha(unsigned char ch)
{
	return  !(ch < 65 || (ch > 91 && ch < 97) || ch > 122);
}
int main(int argc, char* argv[])
{
	Collector* collector = new Collector;
	//const wchar_t* path  = L"//vmware-host/Shared Folders/Gut/aleph.gutenberg.org/";
	//const wchar_t* fileMask;
	std::string path  = "//vmware-host/Shared Folders/Gut/aleph.gutenberg.org/";

	collector->CollectBooksRecursively(path);

	init();
	const int OFFSET = 97;
	
	std::unordered_map<std::string, int> ::iterator it;
	std::unordered_map<std::string, int> wordHashMap;
	std::unordered_map<std::string, int> AlphabetBuckets[26];

	size_t readedSymbols = 0;
	size_t counter = 0;

	unsigned char *buff = new unsigned char[BUFF_SIZE];

	FILE *pFile = fopen("../BigReader/data/bb.txt", "r");

	if(pFile == 0)
	{
		std::cout << "Can't open file\n";
		return -1;
	}


	std::string rwS;
	char resultWord[255];
	int rwC = 0;
	std::unordered_map<std::string, int> ::iterator it_end = wordHashMap.end();
	while(true)
	{
		//(ch = fr.GetChar()) != 0
		if (counter == readedSymbols)
		{
			readedSymbols = fread(buff, 1, BUFF_SIZE, pFile);

			if (readedSymbols == 0)
				break;

			counter = 0;
		}

		char symbol = buff[counter++];


		//if ((unsigned char)symbol > 127 /*|| !isalpha(symbol)*/)
		unsigned char ch = (unsigned char)symbol;
		//if (ch < 65 || (ch > 91 && ch < 97) || ch > 122) 
		if(!alpha(symbol))
		{
			if(rwC == 0)
			{
				continue;
			}
			rwS.assign(resultWord, rwC);
			it = wordHashMap.find(rwS);

			if (it != it_end)
			{
				it->second++;
			}
			else 
			{

				wordHashMap.insert(std::make_pair(rwS, 1));
			}

			rwC = 0;

			continue;
		}
		//TODO: Maybe use char array?
		resultWord[rwC++] = st_tolmap[symbol];
	}
	printf("%d", (int)wordHashMap.size());
}







// BigReader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//#define NULL = 0
#define string  std::string
#define unordered_map std::unordered_map
#define BUFF_SIZE 4096*1024
//#define OFFSET 97;

namespace fs = std::experimental::filesystem;

static char st_tolmap[127];
void init()
{
	for (int i = 'A'; i < 'Z'; i++)
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


class Book
{
public:
	int HappyScore;
	string Title;
	string Autor;
	fs::path Path;
	unordered_map<string, int> ::iterator it;
	unordered_map<string, int> wordHashMap;

	bool ReadBook()
	{
		size_t readedSymbols = 0;
		size_t counter = 0;

		unsigned char *buff = new unsigned char[BUFF_SIZE];

		FILE *pFile = fopen("../BigReader/data/bb.txt", "r");

		if (pFile == 0)
		{
			std::cout << "Can't open file\n";
			return false;
		}


		string rwS;
		char resultWord[255];
		int rwC = 0;
		unordered_map<string, int> ::iterator it_end = this->wordHashMap.end();
		while (true)
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
			if (!alpha(symbol))
			{
				if (rwC == 0)
				{
					continue;
				}
				rwS.assign(resultWord, rwC);
				this->it = this->wordHashMap.find(rwS);

				if (this->it != it_end)
				{
					this->it->second++;
				}
				else
				{
					this->wordHashMap.insert(std::make_pair(rwS, 1));
					//todo add fill autor
					if(rwS == "author" && this->Autor == "")
					{
						size_t localCounter = counter;
						//local ReadLine and trim
						//TODO check \r
						int i = 0;
						while(buff[localCounter] != '\n')
						{
							localCounter++;
						}

						while(!alpha(buff[localCounter]))
						{
							localCounter--;
						}

						string author = nullptr;
						//TODO check index
						for(size_t j = counter; j < localCounter; j++)
						{
							author.assign(buff[j], 1);
						}
						
					}
					if (rwS == "title" && this->Title == "")
					{
						size_t localCounter = counter;
						//local ReadLine and trim
						//TODO check \r
						int i = 0;
						while (buff[localCounter] != '\n')
						{
							localCounter++;
						}

						while (!alpha(buff[localCounter]))
						{
							localCounter--;
						}

						string title = nullptr;
						//TODO check index
						for (size_t j = counter; j < localCounter; j++)
						{
							title.assign(buff[j], 1);
						}
					}

				}

				rwC = 0;

				continue;
			}
			//TODO: Maybe use char array?
			resultWord[rwC++] = st_tolmap[symbol];
		}

	}

};

class Collector
{
public:
	std::vector<Book> BooksList;

	void CollectBooksRecursively(string patch)
	{
		fs::path Patch = patch;
		for (auto & p : fs::recursive_directory_iterator(Patch))
		{
			if(p.path().extension() == ".txt")
			{
				//TODO check why all objects must be *;
				Book* book = new Book;
				book->Path = p.path();
				//TODO check
//				BooksList.push_back(book);
			}
		}
	}
};



class ScoreTable : unordered_map<string, int>
{
	void init()
	{
		this->insert(std::make_pair("smile", 1));
		this->insert(std::make_pair("laught", 1));
		this->insert(std::make_pair("love", 1));
		this->insert(std::make_pair("freedom", 1));
		this->insert(std::make_pair("liberty", 1));
		this->insert(std::make_pair("tranquillity", 1));
		this->insert(std::make_pair("peace", 1));
		this->insert(std::make_pair("sunshine", 1));
		this->insert(std::make_pair("enthusiasm", 1));
		this->insert(std::make_pair("hope", 1));
		this->insert(std::make_pair("cute", 1));
		this->insert(std::make_pair("cosy", 1));
		this->insert(std::make_pair("butterfly", 1));
		this->insert(std::make_pair("hilarious", 1));
	}

	void CalculateScore(Book* book)
	{
		for (auto it = this->begin(); it != this->end(); ++it)
		{
			auto itWord = book->wordHashMap.find(it->first);
			if(itWord != book->wordHashMap.end())
			{
				book->HappyScore += it->second * itWord->second;
			}
		}

		//for (const auto &it : this->cbegin())
		//{
		//	
		//}
		
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


int main(int argc, char* argv[])
{
	Collector* collector = new Collector;
	ScoreTable* st = new ScoreTable;
	//const wchar_t* path  = L"//vmware-host/Shared Folders/Gut/aleph.gutenberg.org/";
	//const wchar_t* fileMask;
	string path  = "//vmware-host/Shared Folders/Gut/aleph.gutenberg.org/";

	collector->CollectBooksRecursively(path);

	init();
	//const int OFFSET = 97;

	for(Book& book : collector->BooksList)
	{
		book.ReadBook();
	//	st.CalculateScore(&book);
	}

	//std::unordered_map<std::string, int> ::iterator it;
	//std::unordered_map<std::string, int> wordHashMap;

	//printf("%d", (int)book->wordHashMap.size());
}







// BigReader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
//#define NULL = 0
#define BUFF_SIZE 4085*8
//#define OFFSET 97;

class FileReader
{
	//FILE * pFile = nullptr;
	//std::ifstream ifs;

public:

	

	//bool open(const char *file)
	//{
	//	pFile = fopen(file, "r");
	//	
	//	if (pFile == nullptr)
	//		return false;
	//	//ifs = std::ifstream(file);
	//	return true;
	//}

	//size_t read(void *pBuff, int count)
	//{
	//	
	//	//ifs.read((char *)pBuff, count);
	//	//return ifs.gcount();
	//	return ;
	//}


	//char GetChar()
	//{
	//	pFile = fopen(file, "r");

	//	if (pFile == nullptr)
	//		return false;

	//	if (counter == readedSymbols)
	//	{
	//		readedSymbols = fread(buff, 1, BUFF_SIZE, pFile);

	//		if (readedSymbols == 0)
	//			return 0x00;

	//		counter = 0;
	//	}
	//			
	//	return buff[counter++];
	//};
};


int main(int argc, char* argv[])
{
	const int OFFSET = 97;
	
	std::unordered_map<std::string, int> ::iterator it;
	std::unordered_map<std::string, int> wordHashMap;
	std::unordered_map<std::string, int> AlphabetBuckets[26];

	size_t readedSymbols = 0;
	size_t counter = 0;

	unsigned char buff[BUFF_SIZE] = { 0 };

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
	char ch;
	while(true)
	{
		//(ch = fr.GetChar()) != 0
		if (counter == readedSymbols)
		{
			readedSymbols = fread(buff, 1, BUFF_SIZE, pFile);

			if (readedSymbols == 0)
				return 0;

			counter = 0;
		}

		buff[counter++];

		if ((unsigned char)buff[counter] > 127 || !isalpha(buff[counter]))
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
		resultWord[rwC++] = tolower(buff[counter]);

	}
}



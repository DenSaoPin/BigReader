// BigReader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#define NULL = 0
#define BUFF_SIZE 4085*8
//#define OFFSET 97;

class FileReader
{

	std::ifstream ifs;
	unsigned char buff[BUFF_SIZE] = { 0 };

public:

	size_t readedSymbols = 0;
	int counter = 0;

	bool open(const char *file)
	{
		ifs = std::ifstream(file);
		return ifs.is_open();
	}

	size_t read(void *pBuff, int count)
	{
		ifs.read((char *)pBuff, count);
		return ifs.gcount();
	}

	bool eof() const
	{
		return  ifs.eof();
	}

	size_t getReadedCounter() const
	{
		return ifs.gcount();
	}
	
	char GetChar()
	{
		if (counter == readedSymbols || readedSymbols == 0)
		{
			readedSymbols = read(buff, BUFF_SIZE);
			counter = 0;

			if (readedSymbols == 0)
				return 0x00;
		}
				
		return buff[counter++];
	};
};





int main(int argc, char* argv[])
{
	const int OFFSET = 97;
	
	std::unordered_map<std::string, int> ::iterator it;
	
	std::unordered_map<std::string, int> wordHashMap;


	std::unordered_map<std::string, int> AlphabetBuckets[26];

	
	FileReader fr;
	
	if(!fr.open("../BigReader/data/BigText.txt"))
	{
		std::cout << "Файл не может быть открыт!\n";
		return -1;
	}

	std::string resultWord(255, 0);
	resultWord.clear();

	while(true)
	{
		char ch = fr.GetChar();

		ch = tolower(ch);

		if ((unsigned char)ch > 127 || !isalpha(ch))
		{
			if (ch == 0x00)
			{
				std::cout << "End file reading";
				return 0;
			}
	
			if(resultWord.empty())
			{
				continue;
			}
			
			it = wordHashMap.find(resultWord);

			if (it != wordHashMap.end())
			{
				it->second++;
			}
			else 
			{

				wordHashMap.insert(std::make_pair(resultWord, 1));
			}



			//char firstLetter = resultWord.front() - OFFSET;

			//it = AlphabetBuckets[firstLetter].find(resultWord);

			//if (it != AlphabetBuckets[firstLetter].end())
			//{
			//	it->second++;
			//}
			//else 
			//{

			//	AlphabetBuckets[firstLetter].insert(std::make_pair(resultWord, 1));
			//}

			resultWord.clear();

			continue;
		}
		//TODO: Maybe use char array?
		resultWord += ch;

	}
}



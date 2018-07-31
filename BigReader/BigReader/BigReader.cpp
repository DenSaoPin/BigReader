// BigReader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <map>
#define NULL = 0
#define BUFF_SIZE 4085
void CheckValidChar(char *buff []);

void CheckAndAddWord(const std::string& cs);

class FileReader
{
	std::ifstream ifs;

public:
	bool open(const char *)
	{
		ifs = std::ifstream("../BigReader/data/BigText.txt");
		return ifs.is_open();
	}
	size_t read(void *pBuff, int count)
	{
		ifs.read((char *)pBuff, count);
		return ifs.gcount();
	}
	bool eof()
	{
		return  ifs.eof();
	}
};

int main(int argc, char* argv[])
{
	//English word of maximum length - 1909 letters (this is a special chemical term);
	const int longestWord = 2000;

	//const int buffSize = 4085;
	char buff[BUFF_SIZE] = {0};

	std::map<std::string, int> wordMap;
	std::map<std::string, int> ::iterator it;


	FileReader ifs;

	if(!ifs.open("../BigReader/data/BigText.txt"))
	{
		std::cout << "Файл не может быть открыт!\n";
		return -1;
	}

	char lastCut[longestWord] = { 0 };
	
	std::string cuttedWord;

	while (!ifs.eof())
	{
		
		size_t readed = ifs.read(buff, BUFF_SIZE);
		


		//ifs.seekg(0, ifs.end);
		//int buffLength = ifs.tellg();
		//ifs.seekg(0, ifs.beg);

	//	CheckValidChar(buff);
		for (std::streamsize i = 0; i < readed; i++)
		{
			unsigned char &ch = (unsigned char &)buff[i];
			if(ch > 127)
			{
				std::cout << "Only english symbols approved, Symbol " << ch << " switch to \" \" \r\n" ;
				ch = ' ';
			}
		}

		for(std::streamsize i = 0; i < readed; i++)
		{
						
			char wordBuff[longestWord] = { 0 };
			int j = 0;

			while (i < BUFF_SIZE && isalpha(buff[i]))
			{
				wordBuff[j] = tolower(buff[i]);
				j++;
				i++;
			}
			std::string resultWord = wordBuff;

			if (lastCut[0] && isalpha((unsigned char)buff[0]))
			{
				cuttedWord = std::string(lastCut) + wordBuff;
				
				//CheckAndAddWord(cuttedWord);
				it = wordMap.find(cuttedWord);

				if(it != wordMap.end())
				{
					it->second++;
				}
				else
				{
					wordMap.insert(std::make_pair(cuttedWord, 1));
				}
				memset(lastCut, 0, sizeof(char) * longestWord);
			}
			else if(!resultWord.empty())
			{
				//CheckAndAddWord(cuttedWord);
				it = wordMap.find(resultWord);

				if (it != wordMap.end())
				{
					it->second++;
				}
				else
				{
					wordMap.insert(std::make_pair(wordBuff, 1));
				}

			}					
		}
/*
		if (isalpha(buff[4085]))
		{
			ifs.seekg(0, ifs.end - 1);

			int i = 0;
			while (isalpha(ifs.peek()))
			{
				ifs.seekg(0, ifs.end - 1);
				lastCut[i] = ifs.peek();
				i++;
			}
		}*/
	}
	if(ifs.eof())
	{
	/*	ifs.seekg(0, ifs.end);
		int buffLength = ifs.tellg();
		ifs.seekg(0, ifs.beg);*/
	}
    return 0;
}
//void CheckValidChar(char buff[])
//{
//	//TODO error
//	//for (char& ch : buff)
//	//{
//	//	if (ch > 127 || ch < 0)
//	//	{
//	//		std::cout << "Only english symbols approved, Symbol " << ch << " switch to \" \" \r\n";
//	//		ch = ' ';
//	//	}
//	//}
//}

//void CheckAndAddWord(const std::string & cs)
//{
//	it = wordMap.find(cuttedWord);
//
//	if (it != wordMap.end())
//	{
//		it->second++;
//	}
//	else
//	{
//		wordMap.insert(std::make_pair(cuttedWord, 1));
//	}
//}

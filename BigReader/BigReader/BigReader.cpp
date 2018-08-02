// BigReader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <map>
#define NULL = 0
#define BUFF_SIZE 4085*8

class FileReader
{

	std::ifstream ifs;
	char buff[BUFF_SIZE] = { 0 };

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
	//TODO: const?
	{
		return ifs.gcount();
	}
	
	char GetChar()
	{
		unsigned char ch;
		if (counter == readedSymbols || readedSymbols == 0)
		{
			readedSymbols = read(buff, BUFF_SIZE);
			counter = 0;

			if (readedSymbols == 0)
				return 0x00;
		}
				
		return buff[counter++];
	};
	//bool CheckNextChar(char *pBuff, int counter)
	//{
	//	
	//	return 0;
	//}
};





int main(int argc, char* argv[])
{
	//English word of maximum length - 1909 letters (this is a special chemical term);
	const int longestWord = 2000;
	
	//const int buffSize = 4085;
	//TODO: check unsigned
	
	std::map<std::string, int> wordMap;
	std::map<std::string, int> ::iterator it;
	
	
	FileReader fr;
	
	if(!fr.open("../BigReader/data/BigText.txt"))
	{
		std::cout << "Файл не может быть открыт!\n";
		return -1;
	}

	// size_t textLenght = fr.read(buff, BUFF_SIZE);

	unsigned char wordBuff[longestWord];
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

			//std::map<std::string, int> AlphabetBuckets[26];

			//it = AlphabetBuckets[ch - 97].find(resultWord);

			it = wordMap.find(resultWord);

			if (it != wordMap.end())
			{
				it->second++;
			}
			else 
			{

				wordMap.insert(std::make_pair(resultWord, 1));
			}

			resultWord.clear();

			continue;
		}
		//TODO: Maybe use char array?
		resultWord += ch;

	}
}


//size_t counter = fr.getReadedCounter();
//for (int i = 0; i < counter;
//	if (isalpha(buff[i]))
//	{
//		wordBuff[i] = buff[i];
//			i++;
	


//
//	char lastCut[longestWord] = { 0 };
//	
//	std::string cuttedWord;
//
//	while (!ifs.eof())
//	{
//		
//		size_t readed = ifs.read(buff, BUFF_SIZE);
//		
//
//
//		//ifs.seekg(0, ifs.end);
//		//int buffLength = ifs.tellg();
//		//ifs.seekg(0, ifs.beg);
//
//	//	CheckValidChar(buff);
//		for (std::streamsize i = 0; i < readed; i++)
//		{
//			unsigned char &ch = (unsigned char &)buff[i];
//			if(ch > 127)
//			{
//				std::cout << "Only english symbols approved, Symbol " << ch << " switch to \" \" \r\n" ;
//				ch = ' ';
//			}
//		}
//
//		for(std::streamsize i = 0; i < readed; i++)
//		{
//						
//			char wordBuff[longestWord] = { 0 };
//			int j = 0;
//
//			while (i < BUFF_SIZE && isalpha(buff[i]))
//			{
//				wordBuff[j] = tolower(buff[i]);
//				j++;
//				i++;
//			}
//			std::string resultWord = wordBuff;
//
//			if (lastCut[0] && isalpha((unsigned char)buff[0]))
//			{
//				cuttedWord = std::string(lastCut) + wordBuff;
//				
//				//CheckAndAddWord(cuttedWord);
//				it = wordMap.find(cuttedWord);
//
//				if(it != wordMap.end())
//				{
//					it->second++;
//				}
//				else
//				{
//					wordMap.insert(std::make_pair(cuttedWord, 1));
//				}
//				memset(lastCut, 0, sizeof(char) * longestWord);
//			}
//			else if(!resultWord.empty())
//			{
//				//CheckAndAddWord(cuttedWord);
//				it = wordMap.find(resultWord);
//
//				if (it != wordMap.end())
//				{
//					it->second++;
//				}
//				else
//				{
//					wordMap.insert(std::make_pair(wordBuff, 1));
//				}
//
//			}					
//		}
///*
//		if (isalpha(buff[4085]))
//		{
//			ifs.seekg(0, ifs.end - 1);
//
//			int i = 0;
//			while (isalpha(ifs.peek()))
//			{
//				ifs.seekg(0, ifs.end - 1);
//				lastCut[i] = ifs.peek();
//				i++;
//			}
//		}*/
//	}
//	if(ifs.eof())
//	{
//	/*	ifs.seekg(0, ifs.end);
//		int buffLength = ifs.tellg();
//		ifs.seekg(0, ifs.beg);*/
//	}
//    return 0;
//}
////void CheckValidChar(char buff[])
////{
////	//TODO error
////	//for (char& ch : buff)
////	//{
////	//	if (ch > 127 || ch < 0)
////	//	{
////	//		std::cout << "Only english symbols approved, Symbol " << ch << " switch to \" \" \r\n";
////	//		ch = ' ';
////	//	}
////	//}
////}
//
////void CheckAndAddWord(const std::string & cs)
////{
////	it = wordMap.find(cuttedWord);
////
////	if (it != wordMap.end())
////	{
////		it->second++;
////	}
////	else
////	{
////		wordMap.insert(std::make_pair(cuttedWord, 1));
////	}
////}


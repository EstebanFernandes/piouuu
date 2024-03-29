#pragma once
#include<string>
#include<vector>
#include<iostream>
#include <fstream>
//Classe qui sert à lire un fichier .csv et extraire toutes les infos
class CParserCSV
{
private:

	std::string sFileName;
	unsigned int imaxRow;
	unsigned int imaxCol;
	std::string sCurrentLine;
	std::vector<std::vector<std::string>> fileElements;
	void parseFile();
	void lineAnalysis();
public:
	CParserCSV();
	CParserCSV(std::string fileName);
	void displayInfo() {
		for (unsigned int i = 0; i < imaxRow; i++)
		{
			for (unsigned int j = 0; j < imaxCol; j++)
			{
				std::cout << fileElements[i][j] << "  ";
			}
			std::cout<<std::endl;
		}
	}
	std::vector<std::vector<std::string>> getElements() {
		return fileElements;
	}
	bool isEmpty() {
		for (int i = 0; i < fileElements.size(); i++)
		{
			for (int j = 0; j < fileElements[i].size(); j++)
			{
				if (!fileElements[i][j].empty())
					return false;
			}
		}
		return true;
	}
};


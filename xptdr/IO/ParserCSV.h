#pragma once
#include<string>
#include<vector>
#include<iostream>
#include <fstream>

namespace IO {
//Classe qui sert à lire un fichier .csv et extraire toutes les infos

	bool isEmpty(std::vector<std::vector<std::string>>& matrix);

class ParserCSV
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
		ParserCSV();
		ParserCSV(std::string fileName, bool display = false);
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
	};

	//function that provide a matrix of 
std::vector< std::vector<std::string>> retrieveCSVFile(std::string filePath);
}
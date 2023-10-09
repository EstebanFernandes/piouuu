#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
struct object {
	int numeroligne;
	int index;
	std::string valeur;
};
class CFile
{ 
private:
	std::vector<object> valueList;
	std::vector<std::string> keyWords;
	std::string fileName;
	unsigned int uicurrentLine;
	std::string currentLine;
public :
	CFile(){}
	CFile(std::string filename);
	//On peut ajouter tous les keyword à la suite en les séparants d'une virgule
	void addKeyWords(std::string kw);
	void addKeyWords(std::string kw,char separator);
	std::vector<object> getValues() {
		return valueList;
	}
	void FileAnalysis();
	object Value();
	void setCurrentLine(std::string ligne) {
		currentLine = ligne;
	}
	void showValueList() {
		for (int i = 0; i < valueList.size(); i++)
		{
			std::cout << valueList[i].valeur << std::endl;
		}
	}
	void setFileName(std::string r)
	{
		fileName = r;
	}
};


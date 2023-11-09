#pragma once
#include "CParserCSV.h"
//Cette classe sert à décrypter le fichier csv, on peut ajouter des mots clés et ça nous ressort un graphe selon les mots vus
class CHugoDecrypte
{
private:
	//CGraphe 
	//les mots clés sont écrit
	std::vector<std::string> keyWords;
	std::vector<std::vector<std::string>> fileContent;
	//CGraphe a;
	void parseFile();
public:
	CHugoDecrypte(std::string fileName);
};


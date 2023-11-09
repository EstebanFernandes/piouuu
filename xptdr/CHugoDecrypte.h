#pragma once
#include "CParserCSV.h"
//Cette classe sert � d�crypter le fichier csv, on peut ajouter des mots cl�s et �a nous ressort un graphe selon les mots vus
class CHugoDecrypte
{
private:
	//CGraphe 
	//les mots cl�s sont �crit
	std::vector<std::string> keyWords;
	std::vector<std::vector<std::string>> fileContent;
	//CGraphe a;
	void parseFile();
public:
	CHugoDecrypte(std::string fileName);
};


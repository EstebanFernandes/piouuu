#pragma once
#include "../IO/ParserCSV.h"
#include"GrapheUpdate.h"
#include"SommetUpgrade.h"
#include"SFML/Graphics.hpp"
//Cette classe sert à décrypter le fichier csv, on peut ajouter des mots clés et ça nous ressort un graphe selon les mots vus
class CHugoDecrypte
{
private:
	//Graphe 
	//les mots clés sont écrit
	std::vector<std::vector<std::string>> fileContent;
	std::vector<GrapheUpdate> GraphList;
	std::vector<std::string> const keywords{ "<id>","<previd>","<var>"};
	void parseFile();
	int matchWordKW(std::string r)
	{
		if (r == "<endLine>")
			return -1;
		for (int i = 0; i < keywords.size(); i++)
		{
			if ( r.find(keywords[i]) != std::string::npos)
			{
				return i;
			}
		}
		return -2;
	}
	void VertexCreation(std::vector<std::string> motclefs,int i,int j, GrapheUpdate& G);
public:
	CHugoDecrypte() {

	}
	CHugoDecrypte(std::string fileName);
	std::vector<GrapheUpdate> returnGraphs()
	{
		return GraphList;
	}
};	


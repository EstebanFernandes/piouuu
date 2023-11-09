#include "CHugoDecrypte.h"
//Cette fonction sert à décrypter les mots clés, je vais faire une liste qu'on augmentera au fur et à mesur de truc de mot clé de base important,
void CHugoDecrypte::parseFile()
{
	int i = 0;
	int j = 0;
	bool trouve = false;
	while (trouve == false)
	{
		//On commence forcément par voir s'il y a un <start>, ensuite en dessous on a des mots clés qui correspondent au différentes catégories, les mots clés.
		//Ensuite on remplit la liste des mots clés présent, cela nous sera utile pour remplir les sommets du graphe
		if (std::find(fileContent[i].begin(), fileContent[i].end(), "<start>") != fileContent[i].end())
		{

		}
		else
			i++;
	}
}

CHugoDecrypte::CHugoDecrypte(std::string fileName)
{
CParserCSV temp(fileName);
fileContent = temp.getElements();
}

#include "CHugoDecrypte.h"
//Cette fonction sert � d�crypter les mots cl�s, je vais faire une liste qu'on augmentera au fur et � mesur de truc de mot cl� de base important,
void CHugoDecrypte::parseFile()
{
	int i = 0;
	int j = 0;
	bool trouve = false;
	while (trouve == false)
	{
		//On commence forc�ment par voir s'il y a un <start>, ensuite en dessous on a des mots cl�s qui correspondent au diff�rentes cat�gories, les mots cl�s.
		//Ensuite on remplit la liste des mots cl�s pr�sent, cela nous sera utile pour remplir les sommets du graphe
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

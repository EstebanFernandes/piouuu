#include "CHugoDecrypte.h"
//Cette fonction sert � d�crypter les mots cl�s, je vais faire une liste qu'on augmentera au fur et � mesur de truc de mot cl� de base important,
void CHugoDecrypte::parseFile()
{
	int currentGraph = 0;
	int i = 0;
	int j = 0;
	bool fini = false;
	while (fini == false)
	{
		//On commence forc�ment par voir s'il y a un <start>, ensuite en dessous on a des mots cl�s qui correspondent au diff�rentes cat�gories, les mots cl�s.
		//Ensuite on remplit la liste des mots cl�s pr�sent, cela nous sera utile pour remplir les sommets du graphe

		std::vector<std::string>::iterator temp = std::find(fileContent[i].begin(), fileContent[i].end(), "<start>");
		if (temp != fileContent[i].end())
		{
			//Si on est ici c'est que l'on a detect� un start
			int maxColumn;
			int maxRow;
			std::vector<std::string> orderkw;
			sf::Vector2i starter;
			starter = sf::Vector2i(std::distance(fileContent[i].begin(),temp),i);
			CGrapheUpdate Graphe;
			int currentX = starter.x;
			int currentY = starter.y;
			bool grapheconstruit = false;
			std::size_t pos = fileContent[currentY][currentX + 1].find("<name>")+6;
			Graphe.Name = fileContent[currentY][currentX + 1].substr(pos);
			currentY++;
 			if (fileContent[currentY][currentX] == "<column>")
			{
				int tempI = currentX +1;
				bool coronel = false;
				while (!coronel)
				{
					int result = -2;
						result = matchWordKW(fileContent[currentY][tempI]);
					if (result == -1)
					{
						coronel = true;
						maxColumn = tempI;
					}
					else if(result!=-2)
					{
						orderkw.push_back(fileContent[currentY][tempI]);
					}
					tempI++;
				}
			}
			else {
				//C'est pas bon l�
				throw("CHEFFf");
			}
			//Ici on a la liste des mots cl�s dans le bonne ordre
			currentX++;
			currentY++;
			while (fileContent[currentY][currentX] != "<endColumn>")
			{
				VertexCreation(orderkw, currentX, currentY,Graphe);
				currentY++;
			}
			maxRow = currentY;
			for (int q = 0; q < orderkw.size(); q++)
			{
				if (orderkw[q] == "<id>" || orderkw[q] == "<previd>")
				{
					orderkw.erase(orderkw.begin() + q);
						q--;
				}
				else {
					orderkw[q] = orderkw[q].substr(5);
				}
			}
			Graphe.ListeType = orderkw;
			GraphList.push_back(Graphe);
			currentGraph++;
			//Maintenant que l'on a cr�e le graphe on va supprimer du fileContent
			for (int ii = starter.y; ii <= maxRow; ii++)
			{
				fileContent[ii].erase(fileContent[ii].begin() + starter.x, fileContent[ii].begin() + maxColumn);
			}
		}
		else
		{
			if (i >= fileContent.size()-1)
				fini = true;
			else
				i++;
		}
	}
}
//cette fonction sert � cr�er un sommet, on lui passe en param�tre la liste ordonn�e des types de valeurs qu'il contient
// et �galement la premi�re case qui le compose.
//renvoie un sommet avec -1 en num�ro si jamais �a se passe mal
void CHugoDecrypte::VertexCreation(std::vector<std::string> motclefs, int k, int j, CGrapheUpdate& G)
{
	CSommetUpgrade temp;
	G.GRAAjouterSommet(temp);
	CSommetUpgrade& currentSommet = G.GRAObtenirListeSommet()[G.GRAObtenirListeSommet().size()-1];
	for (int i = 0; i < motclefs.size(); i++)
	{
		int cI = i + k;
		switch (matchWordKW(motclefs[i]))
		{
		case 0:
			currentSommet.SOMModifierNumero(atoi(fileContent[j][cI].c_str()));
			break;
		case 1:
			if (fileContent[j][cI] != "")
			{
				G.GRAAjouterArc(atoi(fileContent[j][cI].c_str()), currentSommet.SOMLireNumero());
			}
			break;
		case 2:
			currentSommet.addValue(fileContent[j][cI]);
			break;
		}
	}
}

CHugoDecrypte::CHugoDecrypte(std::string fileName)
{
CParserCSV temp(fileName);
fileContent = temp.getElements();
parseFile();
}

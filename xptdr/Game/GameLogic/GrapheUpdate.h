#pragma once
#include"Graphe.h"
class GrapheUpdate : public Graphe
{
public:
	bool endOfGraph = false;
	std::vector<std::string> ListeType;
	std::string Name;
	SommetUpgrade* currentVert = NULL;

	GrapheUpdate& operator=(const GrapheUpdate& GRAParam)
	{
		bGRAType = GRAParam.bGRAType;
		lisGRAListeSommet = GRAParam.lisGRAListeSommet;
		ListeType = GRAParam.ListeType;
		Name = GRAParam.Name;
		return *this;
	}
	GrapheUpdate(const GrapheUpdate& GRAParam)
	{
		this->operator=(GRAParam);
	}
	GrapheUpdate() {
		bGRAType = Oriente;
	}
	//Méthode qui supprime un sommet et qui supprime tous ceux qui lui sont liés.
	bool supprimerSommetetDescendences(int vertIndex) {
		if (lisGRAListeSommet[vertIndex].SOMLireArcPartant().size() == 0)
		{
			GRASupprimerSommet(vertIndex);
			return true;
		}
		for (int i = 0; i < lisGRAListeSommet[vertIndex].SOMLireArcPartant().size(); i++)
		{
			SommetUpgrade& nextVert = lisGRAListeSommet[lisGRAListeSommet[vertIndex].SOMLireArcPartant()[i].ARCObtenirDest()];
			supprimerSommetetDescendences(nextVert.SOMLireNumero());
		}
		if (lisGRAListeSommet[vertIndex].SOMLireArcPartant().size() == 0)
		{
			GRASupprimerSommet(vertIndex);
			return true;
		}
		return false;
	}
};


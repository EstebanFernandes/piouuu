#pragma once
#include"CGraphe.h"
class CGrapheUpdate : public CGraphe
{
public:
	bool endOfGraph = false;
	std::vector<std::string> ListeType;
	std::string Name;
	CSommetUpgrade* currentVert = NULL;

	CGrapheUpdate& operator=(const CGrapheUpdate& GRAParam)
	{
		bGRAType = GRAParam.bGRAType;
		lisGRAListeSommet = GRAParam.lisGRAListeSommet;
		ListeType = GRAParam.ListeType;
		Name = GRAParam.Name;
		return *this;
	}
	CGrapheUpdate(const CGrapheUpdate& GRAParam)
	{
		this->operator=(GRAParam);
	}
	CGrapheUpdate() {
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
			CSommetUpgrade& nextVert = lisGRAListeSommet[lisGRAListeSommet[vertIndex].SOMLireArcPartant()[i].ARCObtenirDest()];
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


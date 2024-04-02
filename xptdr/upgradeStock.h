#pragma once
#include"CGrapheUpdate.h"
#include"CHugoDecrypte.h"
enum typeGraphe {
	ARME_PRINCIPALE = 1,
	ARME_SECONDAIRE,
	DIVERS
};
struct graphComponent {
	//pointeur où on se trouve
	CSommetUpgrade* pointerToSommet = nullptr;
	sf::Vector2i pos= sf::Vector2i(-1,-1);//position correspond au graphe sur lequel on se trouve(c'est une matrice de graphe) 
	bool isGraphEnd()
	{
		if (pos.x == 0 && pos.y == 0)
			return true;
		return false;
	}
};
/// <summary>
/// Classe qui stocke toutes les améliorations possibles, 
/// </summary>
class upgradeStock
{
private:
public:
	upgradeStock();
	std::vector< std::vector <CGrapheUpdate>> graphs;
	void addGraphs(std::string fileName);
	graphComponent initVert(typeGraphe type);
	void avancer(graphComponent &comp, int next);
	CGrapheUpdate& currentGraph(graphComponent g);
};


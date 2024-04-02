#include "upgradeStock.h"

upgradeStock::upgradeStock()
{
	graphs.push_back(std::vector<CGrapheUpdate>());
	graphs[0].push_back(CGrapheUpdate());
}

void upgradeStock::addGraphs(std::string fileName)
{
	CHugoDecrypte temp(fileName);
	graphs.push_back(temp.returnGraphs());
	CGrapheUpdate t;
	t.GRAAjouterSommet(0);
	int nbOfGraphs = (int)temp.returnGraphs().size();
	//On rajoute donc un graphe qui a tous les premiers de chaque graphe
	for (int i = 0; i < nbOfGraphs; i++)
	{
		CSommetUpgrade tempSommet = temp.returnGraphs()[i].GRAObtenirListeSommet()[0];
		tempSommet.SOMModifierNumero(i + 1);
		t.GRAAjouterSommet(tempSommet);
		t.GRAAjouterArc(0, i + 1);
	}
	graphs.at(0).push_back(t);
}

graphComponent upgradeStock::initVert(typeGraphe type)
{
	graphComponent res;
	switch (type)
	{
	case ARME_PRINCIPALE:
		res.pointerToSommet = &graphs.at(0).at(1).GRAObtenirListeSommet().at(0);
		res.pos = sf::Vector2i(1, 0);
		break;
	case ARME_SECONDAIRE:
		res.pointerToSommet = &graphs.at(0).at(2).GRAObtenirListeSommet().at(0);
		res.pos = sf::Vector2i(2, 0);
		break;
	}
	return res;
}

void upgradeStock::avancer(graphComponent& comp, int next)
{
	if (comp.pos.y == 0&& comp.pos.x!=0)//Si on est sur la première ligne du tableau c'est que c'est un graphe d'initialisation, donc 
	{					//Donc on se déplace sur le bon graphe, pour cela le x du nouveau graphe correspond au sommet choisi (donc next ) et
						//Le y correspond au x+1 ;-)
		comp.pointerToSommet = &(graphs[comp.pos.x ][next].GRAObtenirListeSommet().at(0));
		comp.pos.y = comp.pos.x;
		comp.pos.x = next;
	}
	else if (comp.pos.y == 0 && comp.pos.x == 0)
	{
		//ON ne fait rien
	}
	else //Comportement normal (la ligne de dingo)
		comp.pointerToSommet = &(graphs[comp.pos.y][comp.pos.x].GRAObtenirListeSommet().at(graphs[comp.pos.x][comp.pos.y].GRATrouverSommet(comp.pointerToSommet->SOMLireArcPartant().at(next).ARCObtenirDest())));
	//Permet de vérifier si on est en fin de graphe ou non
	if(comp.pointerToSommet->SOMLireArcPartant().size()==0&& comp.pos.y!=0)
	{
		comp.pointerToSommet = &(graphs[0][0].GRAObtenirListeSommet().at(0));
		comp.pos.y = 0;
		comp.pos.x = 0;
	}
}

CGrapheUpdate& upgradeStock::currentGraph(graphComponent g)
{
	return graphs.at(g.pos.y).at(g.pos.x);
}

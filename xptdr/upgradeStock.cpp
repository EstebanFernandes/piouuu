#include "upgradeStock.h"
#include"CCardUpgrade.h"
#include"InterfaceState.h"
#include<sys/stat.h>
void upgradeStock::plusStatGraph()
{
	//int nbOfUpgrade = 6;
	//std::vector<std::string> typeString = { "name","maxHealthPoint",
	//									"moveSpeed","damagePerBullet",
	//										"attackSpeed","bulletSpeed","dashDamage" };
	//CGrapheUpdate& graph = graphs[0][0];
	//graph.ListeType = typeString;
	//for (int i = 0; i < nbOfUpgrade; i++)
	//{
	//	CSommetUpgrade temp(i + 1);
	//	temp.values = std::vector<std::string>(6);
	//	temp.values.at(0) = "Supplément";
	//	temp.values.at(i+1) = "<rand:0.2:0.6>";//Le premier est le nom donc ça décale tout de +1

	//	graph.GRAAjouterSommet(temp);
	//	graph.GRAAjouterArc(0, i + 1);
	//}
}
upgradeStock::upgradeStock()
{
	assets = NULL;
	graphs.push_back(std::vector<CGrapheUpdate>());
	graphs[0].push_back(CGrapheUpdate());
	graphs[0][0].GRAAjouterSommet(0);
	plusStatGraph();
}

void upgradeStock::addGraphs(std::string fileName)
{
	CHugoDecrypte temp(fileName);
	graphs.push_back(temp.returnGraphs());
	CGrapheUpdate t;
	t.Name = std::to_string(graphs.size()-1);
	t.GRAAjouterSommet(0);
	int nbOfGraphs = (int)temp.returnGraphs().size();
	//On rajoute donc un graphe qui a tous les premiers sommet de chaque graphe
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
	{
		CGrapheUpdate& curGraph = graphs[comp.pos.y][comp.pos.x];
		int idProchainSommet = comp.pointerToSommet->SOMLireArcPartant().at(next).ARCObtenirDest();
		//comp.pointerToSommet = &(curGraph.GRAObtenirListeSommet().at(curGraph.GRATrouverSommet(idProchainSommet)));
		comp.pointerToSommet = &(curGraph.GRAObtenirListeSommet().at(curGraph.GRATrouverSommet(idProchainSommet)));
	}
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

int upgradeStock::indexInGraphs(graphComponent& component)
{
	int index = 0;
	for (int i = 0; i < component.pos.y; i++)
	{
		index += graphs[i].size();
	}
	index += component.pos.x;
	return index;
}


#pragma once

#define mainWeaponfilePath "res/data/principalweapon2.csv"
#define secondaryWeaponfilePath "res/data/secondaryweapon.csv"
#include"CGrapheUpdate.h"
#include"CHugoDecrypte.h"
#include"CCardUpgrade.h"
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
	sf::Texture textureOfAllCard;
	sf::RenderTexture renderTexture;
	CAssetManager* assets;
	std::vector<CCardUpgrade> CardList;
	//Créer un graph avec les améliorations disponibles en fin d'arbre 
	void plusStatGraph();
	float fileCreation(std::string filePath);
public:
	upgradeStock();
	std::vector< std::vector <CGrapheUpdate>> graphs;
	void addGraphs(std::string fileName);
	graphComponent initVert(typeGraphe type);
	void avancer(graphComponent &comp, int next);
	CGrapheUpdate& currentGraph(graphComponent g);
	/// <summary>
	/// Initialise la texture qui contient les cartes d'améliorations
	/// </summary>
	/// 
	
	void initAllGraphTexture();

	void setAssets(CAssetManager* a)
	{
		assets = a;
	}
	int indexInGraphs(graphComponent& component);
	sf::Texture& getTexture() { return textureOfAllCard; }
	void init() {
		addGraphs(mainWeaponfilePath);
		addGraphs(secondaryWeaponfilePath);
	}
};
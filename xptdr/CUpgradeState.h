#pragma once
#include "CState.h"
#include <string>
#include "CJeu.h"
#include"CPlayer.h"
#include"CHugoDecrypte.h"
#include"CCardUpgrade.h"
#include"InterfaceState.h"
#include"upgradeStock.h"
//état qui gère les améliorations d'un joueur 
class CUpgradeState : public CState, public InterfaceState
{
private:
	GameDataRef data;
	int nbOfGraph;
	int type;
	upgradeStock* US;
	graphComponent* playerComp;
	//Pointeur sur le joueur afin d'accéder plus facilement à ces stats
	CPlayer* pointerToPlayer1;
	Weapon* pointerToWeapon;
	int levelofPlayer;
	//Liste qui gère les améliorations une fois que l'on arrive à la fin d'un arbre
	std::vector<std::string> listUpgradeMax;
	CGrapheUpdate* currentGraph;
	bool isFirstTime = false;
	bool isGraphEnd = false;
	int hasPressedKey = 0;
	//Graphique
	std::vector<CCardUpgrade> CardList;
	sf::Text title;
	//Selection
	int iCardSelection = 0;

	void fillUpgrade(int nbofUpgrade);
	//Méthodes et constructeurs
	int whichKindofUpgrade() {
		int temp = levelofPlayer;
		int res = temp % 3;
		if (res == 0)
		{
			res = 1;
		}
		switch (res)
		{
		case 1:
			return 0;
		case 2:
			return 1;
		case 3:
			return 2;
		}
		return -1;
	}
	/// <summary>
	/// Cette fonction est appelé pendant l'initialisation et crée les cartes , on présuppose que les upgradestock ont été défini ainsi que le PlayerComp et isFirstTime
	/// </summary>
	/// <param name="type"></param>
	/// <param name="isFirstTime"></param>
	void CreateCard()
	{

		int screen_Height = data->assets.sCREEN_HEIGHT;
		int screen_Width = data->assets.sCREEN_WIDTH;
		CSommetUpgrade& baseSommet = (*playerComp->pointerToSommet);
		if (playerComp->isGraphEnd())//Si le graphe est fini on met les trucs supplémentaire
		{
			isGraphEnd = true;
			plusStats();
		}
		else
		{
			int nbofUpgrade = (int)baseSommet.SOMLireArcPartant().size();
				for (int i = 0; i < nbofUpgrade; i++)
				{
					sf::Vector2f pos;
						int iDNextVert = baseSommet.SOMLireArcPartant()[i].ARCObtenirDest();
						CSommetUpgrade nextVert = currentGraph->GRAObtenirListeSommet()[currentGraph->GRATrouverSommet(iDNextVert)];
					CCardUpgrade temp;
					if(isFirstTime==false)
					{
						temp = CCardUpgrade(nextVert.returnValues(), US->graphs[playerComp->pos.y][playerComp->pos.x].ListeType, &(data->assets));
					}
					else {
						temp = CCardUpgrade(nextVert.returnValues(), US->graphs[playerComp->pos.x][iDNextVert-1].ListeType, &(data->assets));
					}
					float ratio = 1 / (float)nbofUpgrade;
					//Distance qui n'est pas prise par les cartes
					float t = screen_Width - (temp.getGlobalBounds().width * nbofUpgrade);
					while (t <= screen_Width * 0.2)
					{
						temp.reduceScale();
						t = screen_Width - (temp.getGlobalBounds().width * nbofUpgrade);
					}
					float spaceBetweenCard = t / (float)(nbofUpgrade + 1);
					pos.x = spaceBetweenCard + (spaceBetweenCard + temp.getGlobalBounds().width) * i;
					pos.y = (screen_Height / 2.f) - (temp.getGlobalBounds().height / 2.f);
					temp.setPosition(pos);
					CardList.push_back(temp);
				}
		}
	}
	void plusStats();
	void applyStats();
	float setValue(float init, std::string modif);
	int setValue(int init, std::string modif);
	bool matchTypeWithValue(std::string type, std::string value);
public:
	CUpgradeState(GameDataRef d, CPlayer* player, upgradeStock* pointerToUpgradeStocks);
	void STEInit(); 
	void STEHandleInput();
	void STEUpdate(float delta);
	void STEDraw(float delta);
	
};
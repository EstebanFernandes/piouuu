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
	const sf::Vector2f sizeOfCard = sf::Vector2f(255, 366.f);
	CState* pointertoGameState;
	GameDataRef data;

	struct upgradeForOnePlayer{
		sf::FloatRect bord;
		int nbOfGraph;
		int type;
		graphComponent* playerComp;
		CPlayer* pointerToPlayer;
		Weapon* pointerToWeaponPlayer;
		int levelOfPlayer;
		//Liste qui gère les améliorations une fois que l'on arrive à la fin d'un arbre
		std::vector<std::string> listUpgradeMax;
		bool isFirstTime = false;
		bool isGraphEnd = false;
		int hasPressedKey = 0;
		//Graphique
		std::vector<CCardUpgrade> CardList;
		//Selection
		int iCardSelection = 0;
		sf::Text title;
		bool cfini = false;
	};
	upgradeStock* US;
	std::vector<upgradeForOnePlayer> players;
	sf::Shader blurShader;
	sf::Sprite fond;
	sf::RectangleShape frontiere;
	void fillUpgrade(upgradeForOnePlayer& player ,int nbofUpgrade);
	//Méthodes et constructeurs
	int whichKindofUpgrade(upgradeForOnePlayer& player) {
		int temp = player.levelOfPlayer;
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
	void CreateCard(upgradeForOnePlayer& player)
	{

		float screen_Height = player.bord.height;
		float screen_Width = player.bord.width;
		CSommetUpgrade& baseSommet = (*player.playerComp->pointerToSommet);
		if (player.playerComp->isGraphEnd())//Si le graphe est fini on met les trucs supplémentaire
		{
			player.isGraphEnd = true;
			plusStats(player);
		}
		else
		{
			sf::Vector2f trueSizeOfCard = (players.size() == 2) ? sf::Vector2f(sizeOfCard * 0.8f) : sizeOfCard;
			int nbofUpgrade = (int)baseSommet.SOMLireArcPartant().size();

			float totalRectanglesWidth = (float)nbofUpgrade * trueSizeOfCard.x;
			// Calculer l'espacement nécessaire
			float totalSpacing = player.bord.width - totalRectanglesWidth;
			float spacing = totalSpacing / (nbofUpgrade + 1);

			// Calculer la position de départ
			float startX = player.bord.left+ spacing;

			for (int i = 0; i < nbofUpgrade; i++)
			{
				sf::Vector2f pos;
					int iDNextVert = baseSommet.SOMLireArcPartant()[i].ARCObtenirDest();
					CSommetUpgrade nextVert = US->currentGraph((*player.playerComp)).GRAObtenirListeSommet()[US->currentGraph((*player.playerComp)).GRATrouverSommet(iDNextVert)];
				CCardUpgrade temp;
				if(player.isFirstTime==false)
				{
					temp = CCardUpgrade(nextVert.returnValues(), US->graphs[player.playerComp->pos.y][player.playerComp->pos.x].ListeType, &(data->assets));
				}
				else {
					temp = CCardUpgrade(nextVert.returnValues(), US->graphs[player.playerComp->pos.x][iDNextVert-1].ListeType, &(data->assets));
				}
				temp.setSize(trueSizeOfCard);
				pos.x = startX;
				pos.y = (screen_Height / 2.f) - (temp.getGlobalBounds().height / 2.f);
				temp.setPosition(pos);
				player.CardList.push_back(temp);
				startX += trueSizeOfCard.x+spacing;
			}
		}
	}
	void plusStats(upgradeForOnePlayer& player);
	void applyStats(upgradeForOnePlayer& player);
	float setValue(float init, std::string modif);
	int setValue(int init, std::string modif);
	bool matchTypeWithValue(upgradeForOnePlayer& player, std::string type, std::string value);
	void handleInput(upgradeForOnePlayer& player, sf::Event& event);
public:
	CUpgradeState(GameDataRef d, CPlayer* player, upgradeStock* pointerToUpgradeStocks,CState* prev);
	CUpgradeState(GameDataRef d, std::list<CPlayer>* player, upgradeStock* pointerToUpgradeStocks, CState* prev);
	void STEInit(); 
	void STEHandleInput();
	void STEUpdate(float delta);
	void STEDraw(float delta);
	
};
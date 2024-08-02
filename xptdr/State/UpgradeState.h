#pragma once
#include "State.h"
#include <string>
#include "../Engine/MainLoop.h"
#include"../Game/Player.h"
#include"../UI/CardUpgrade.h"
#include"InterfaceState.h"
#include"../Game/GameLogic/upgradeStock.h"
#include"../UI/SpinningCard.hpp"

namespace StateNS {
	//état qui gère les améliorations d'un joueur 
	class UpgradeState : public State, public InterfaceState
	{
	private:
		const sf::Vector2f sizeOfCard = sf::Vector2f(255, 365.f);
		State* pointertoGameState;
		GameDataRef data;
		const float speedCard = 1.5f;
		struct cardHandler{
			sf::Vector2f finalPos;
			sw::SpinningCard* cardBack;
			sw::SpinningCard* cardFace;
			float degree;
			float scale=1.f;
			bool canMove=false;
			void freeMemory() {
				delete cardBack;
				delete cardFace;
			}
			void move(sf::Vector2f offset)
			{
				cardFace->move(offset);
				cardBack->move(offset);
			}
			void move(float x,float y)
			{
				cardFace->move(x,y);
				cardBack->move(x,y);
			}
			void setScale(float newScale)
			{
				scale = newScale;
				cardFace->setScale(scale, scale);
			cardBack->setScale(scale, scale);
			}
			sf::Vector2f getScale() {
				return cardFace->getScale();
			}
			void spin(float spin)
			{
				cardFace->spin(spin);
				cardBack->spin(spin);
			}

			void spinVertically(float angleInDegrees) {
				cardFace->spinVertically(angleInDegrees);
			cardBack->spinVertically(angleInDegrees);
			}
			void setPosition(sf::Vector2f pos)
			{
				cardFace->setPosition(pos);
				cardBack->setPosition(pos);
			}
			void draw(sf::RenderTarget& renderTarget)
			{
				bool backFirst = (degree > 90.f && degree < 270.f) ? true : false;
					renderTarget.draw(*cardBack);
			
				if (!backFirst)
				{
	
					renderTarget.draw(*cardFace);
				}
			}
		};
		struct upgradeForOnePlayer{
			sf::FloatRect bord;
			int nbOfGraph;
			int type;
			graphComponent* playerComp;
			Player* pointerToPlayer;
			Weapon* pointerToWeaponPlayer;
			int levelOfPlayer;
			//Liste qui gère les améliorations une fois que l'on arrive à la fin d'un arbre
			std::vector<std::string> listUpgradeMax;
			bool isFirstTime = false;
			bool isGraphEnd = false;
			int hasPressedKey = 0;
			//Graphique
			std::vector<cardHandler> CardList;
			//Selection
			int iCardSelection = 0;
			sf::Text title;
			sf::Text subtitle;
			bool cfini = false;
			int indexesUpgrade[3];
			float timeOffset=-1.f;
			sf::Texture cardTexture;
			int nbDeTours = 3;
			bool weStop = false;
		};
		sf::Texture backCardTexture;
		upgradeStock* US;
		std::vector<upgradeForOnePlayer> players;
		sf::Shader blurShader;
		sf::Shader fadeShader;
		sf::Sprite fond;
		sf::RectangleShape frontiere;
		//0 Intro,1 sélection et 2 outro 
		int state = 0;
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
			backCardTexture.loadFromFile("res/img/backCard2.png");
			float screen_Height = player.bord.height;
			float screen_Width = player.bord.width;
			SommetUpgrade& baseSommet = (*player.playerComp->pointerToSommet);
			if (player.playerComp->isGraphEnd())//Si le graphe est fini on met les trucs supplémentaire
			{
				player.isGraphEnd = true;
				plusStats(player);
			}
			int nbofUpgrade = (int)baseSommet.SOMLireArcPartant().size();
			int trueNbOfUpgrade = (nbofUpgrade <3) ? nbofUpgrade : 3;
			for (int i = 0; i < trueNbOfUpgrade; i++) //Décide aléatoirement des augmentes
			{
				//Index du prochain sommet dans la liste des sommets du graphe
				int nextIndex = baseSommet.SOMLireArcPartant()[(rand() % nbofUpgrade)].ARCObtenirDest();
				while (isNumberInArray(player.indexesUpgrade, 3, nextIndex))
				{
					nextIndex = baseSommet.SOMLireArcPartant()[(rand() % nbofUpgrade)].ARCObtenirDest();
				}
				player.indexesUpgrade[i] = nextIndex;
				
			}
			 //Comportement normal
			createCardTexture(player,trueNbOfUpgrade);
		
		
			bool isAlone = (players.size() == 2) ? false : true;
			sf::Vector2f trueSizeOfCard = (players.size() == 2) ? sf::Vector2f(sizeOfCard * 0.8f) : sizeOfCard;
			float totalRectanglesWidth = (float)trueNbOfUpgrade * trueSizeOfCard.x;
			// Calculer l'espacement nécessaire
			float totalSpacing = player.bord.width - totalRectanglesWidth;
			float spacing = totalSpacing / (trueNbOfUpgrade + 1);

			// Calculer la position de départ
			float startX = player.bord.left+ spacing;
			CardUpgrade cardArray[3];
			for (int i = 0; i < trueNbOfUpgrade; i++)
			{
				sf::Vector2f pos;
				sf::Sprite spriteCard(player.cardTexture), backSpriteCard(backCardTexture);
				spriteCard.setTextureRect(
					sf::IntRect(
						sf::Vector2i((int)sizeOfCard.x * i, 0), sf::Vector2i(sizeOfCard)));
				utilities::centerObject(spriteCard);
				utilities::centerObject(backSpriteCard);
				if (!isAlone)
					spriteCard.setScale(0.8f, 0.8f);
				pos.x = startX+spriteCard.getGlobalBounds().width/2.f;
				pos.y = screen_Height / 2.f;
				cardHandler tempCard;
				tempCard.finalPos = pos;
				
				sw::SpinningCard* tempSpCard = new sw::SpinningCard(spriteCard);
				sw::SpinningCard* cardBackFace = new sw::SpinningCard(backSpriteCard);
				tempCard.cardBack = cardBackFace;
				tempCard.cardFace = tempSpCard;
	
				tempCard.degree = 180.f;//Les cartes commencent retournées
				sf::Vector2f moveTo(pos.x, screen_Height + spriteCard.getGlobalBounds().height);
				tempCard.move(moveTo);
				tempCard.spin(180.f);
				player.CardList.push_back(tempCard);
				startX += trueSizeOfCard.x + spacing;
			}
		
		}
		void createCardTexture(upgradeForOnePlayer& player, int nbOfUpgrade);
		void plusStats(upgradeForOnePlayer& player);
		void applyStats(upgradeForOnePlayer& player);
		float setValue(float init, std::string modif);
		int setValue(int init, std::string modif);
		bool matchTypeWithValue(upgradeForOnePlayer& player, std::string type, std::string value);
		void handleInput(upgradeForOnePlayer& player, sf::Event& event);

		bool isNumberInArray(int arr[], int size, int number) {
			for (int i = 0; i < size; ++i) {
				if (arr[i] == number) {
					return true;
				}
			}
			return false;
		}

		bool updateCards(upgradeForOnePlayer& player);
		void updateState();
		void updateChosenCard(upgradeForOnePlayer& player,int previousSelec);
	public:
		UpgradeState(GameDataRef d, Player* player, upgradeStock* pointerToUpgradeStocks,State* prev);
		UpgradeState(GameDataRef d, std::list<Player>* player, upgradeStock* pointerToUpgradeStocks, State* prev);
		~UpgradeState() {
			for (int i = 0; i < players.size(); i++)
			{
				for (int j = 0; j < players[i].CardList.size(); j++)
				{
					players[i].CardList[j].freeMemory();
				}
			}
		}
		void STEInit(); 
		void STEHandleInput(sf::Event& event);
		void STEUpdate(float delta);
		void STEDraw(float delta);
	
	};
}
#pragma once
#include "State.h"
#include <iostream>
#include "GameMenu.h"
#include <sstream>
#include "../Game/Enemy/BomberEnemy.h"
#include "../Game/Enemy/ShootingEnemy.h"
#include "../Game/Enemy/Boss.h"
#include "../Game/Enemy/RusherEnemy.h"
#include "../Game/Enemy/testEnemy.h"
#include "GameOver.h"
#include "../Game/Player.h"
#include "../Game/Entity.h"
#include "../Game/HittingEntity.h"
#include "../Game/PowerUp.h"
#include <list>
#include"../Game/GameLogic/GrapheUpdate.h"
#include "../Engine/Background.h"
#include "../Engine/MainLoop.h"
namespace StateNS {
	class GameState : public State
	{
	protected:
		GameDataRef data;
		upgradeStock US;
		sf::Time gameTime;
		std::list<Player> players;
		std::vector<HittingEntity*> entityList;
		int* enemyNumber = new int();
		bool isThistheEnd = false;
		bool hasLevelUp = false;
		bulletStorage bulletstorage;
		//engine related
		//Background related:
		Background BG1;
		float totalScore;

		sf::Text gameClockText;
		sf::Text uitext;
		bool CESTBON = false;
		void initPlayer();
		virtual void initBackground();
		void deleteEntity(int i);
		void updateTime();
		EllipseShape ellipseForSun;
		int indexForSun = 0;

		//Handle light fx
		sf::Shader lightShader;
		sf::RenderTexture renderTexture;
		sf::RenderTexture shadowMask;
		sf::Sprite spriteRender;
	public:
		GameState();
		GameState(GameDataRef _data);
		GameState(GameDataRef _data, std::vector<Character>& characterParam);
		~GameState();
		virtual void STEInit();
		void STEHandleInput(sf::Event& event);
	
		/// <summary>
		/// Possibilities :
		///	 -roaming, a standard enemy
		///	 -shooter, an enemy with a big GUN PIOU PIOU
		/// - bomber, a bomber man
		/// - bomberInverse, a bomberman, mon cousin félix who start to the oposite side
		/// - rusher, a quick guy			qu'est-ce qu'ils sont beaux
		///	 -boss, first prototype of a boss
		/// </summary>
		void addEnemy(std::string enemyName);
		void addPowerUp(sf::Vector2f pos);
		void STEUpdate(float delta);
		virtual void updateBackground(float delta);
		virtual void updateSun();
		// Méthode qui initialise les assets du niveau.
		virtual void initAssets() = 0;
		virtual void GameOver() = 0;
		void renderBackground(sf::RenderTarget& target);
		void STEDraw(float delta);
		virtual void drawOnTarget(sf::RenderTarget& target, float interpolation);
		void STEResume();
		void STEPause();
		void setData(GameDataRef dataa) { data = dataa; }
		void updateClock();
		/// <summary>
		/// Méthode appelé qui regarde si les joueurs ont level up
		/// </summary>
		virtual void updateXpPlayers();
		void afterTransi();
		Mob* nearEnemy(Mob* player);
		Mob* nearestPlayer(sf::Vector2f pos);
		GameDataRef getData();

		void drawOnTargetEntity(sf::RenderTarget& target, float interpolation)
		{
			BG1.drawEverythingButFirstLayer(target, interpolation);
			for (auto i = players.begin(); i != players.end(); i++)
				i->renderEntity(target);
			for (int i = 0; i < entityList.size(); i++)
			{
				entityList[i]->renderEntity(target);
			}
			for (int i = 0; i < entityList.size(); i++)
			{
				entityList[i]->renderBuffs(target);
			}
		}

		//Rend uniquement les élements d'interface graphique
		void drawOnTargetUI(sf::RenderTarget& target, float interpolation)
		{

			for (int i = 0; i < entityList.size(); i++)
			{
				entityList[i]->renderUI(target);
			}
			for (auto i = players.begin(); i != players.end(); i++)
			{
				i->renderUI(target);
			}
			target.draw(uitext);
			target.draw(gameClockText);
		}

	}; 
}
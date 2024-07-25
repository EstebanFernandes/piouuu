#pragma once
#include "CState.h"
#include <iostream>
#include "CPlayer.h"
#include "CGameMenu.h"
#include <sstream>
#include"BomberEnemy.h"
#include"ShootingEnemy.h"
#include"testEnemy.h"
#include"CGameOver.h"
#include"CEntity.h"
#include"CBackground.h"
#include "CHittingEntity.h"
#include "Boss.h"
#include "RusherEnemy.h"
#include <list>
#include "CPowerUp.h"
#include"CGrapheUpdate.h"
#include"CUpgradeState.h"
class CGameState : public CState
{
protected:
	GameDataRef data;
	upgradeStock US;
	sf::Time gameTime;
	std::list<CPlayer> players;
	std::vector<CHittingEntity*> entityList;
	int* enemyNumber = new int();
	bool isThistheEnd = false;
	bool hasLevelUp = false;
	bulletStorage bulletstorage;
	//engine related
	//Background related:
	CBackground BG1;
	float totalScore;

	sf::Text gameClockText;
	sf::Text uitext;
	bool CESTBON = false;
	void initPlayer();
	void initBackground();
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
	CGameState();
	CGameState(GameDataRef _data);
	CGameState(GameDataRef _data, std::vector<CCharacter>& characterParam);
	~CGameState();
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
	void updateBackground(float delta);
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
	CMob* nearEnemy(CMob* player);
	CMob* nearestPlayer(sf::Vector2f pos);
	GameDataRef getData();

	void drawOnTargetEntity(sf::RenderTarget& target, float interpolation)
	{
		BG1.drawEverythingButFirstLayer(target, interpolation);
		for (auto i = players.begin(); i != players.end(); i++)
			i->renderEntity(target);
		for (int i = 0; i < entityList.size(); i++)
		{
			entityList[i]->renderTheEntity(target);
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
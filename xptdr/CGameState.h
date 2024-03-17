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
	sf::Time gameTime;
	sf::Clock gameClock;
	CPlayer player1;
	float clock;
	std::vector<CHittingEntity*> entityList;
	int* enemyNumber = new int();
	std::vector<CGrapheUpdate> Upgradegraphs;
	int currentLevelOfplayer = 0;
	bool isThistheEnd = false;
	bool hasLevelUp = false;
	bulletStorage bulletstorage;
	//engine related
	//Background related:
	CBackground BG1;

	sf::Text gameClockText;
	sf::Text uitext;
	bool CESTBON = false;
	void initPlayer();
	void initBackground();
	void deleteEntity(int& i);
public:
	CGameState();
	CGameState(GameDataRef _data);
	CGameState(GameDataRef _data, CCharacter characterParam);
	~CGameState();
	virtual void STEInit();
	void STEHandleInput();
	
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
	void renderBackground();
	void STEDraw(float delta);
	void STEResume();
	void STEPause();
	void setData(GameDataRef dataa) { data = dataa; }
	CMob* nearEnemy(CMob* player);
	GameDataRef getData();
};
#pragma once
#include "CState.h"
#include "CPhysics.h"
#include <iostream>
#include "CPlayer.h"
#include "CGameMenu.h"
#include <sstream>
#include"RoamingEnnemy.h"
#include"ShootingEnemy.h"
#include"CGameOver.h"
#include"CEntity.h"
#include"CBackground.h"
#include "CHittingEntity.h"
#include <list>
#include "CPowerUp.h"
class CGameState : public CState
{
protected:
	GameDataRef data;
	sf::Time gameTime;
	sf::Clock gameClock;
	CPlayer player1;
	std::vector<CHittingEntity*> entityList;
	int enemyNumber = 0;
	//engine related
	//Background related:
	CBackground BG1;

	sf::Text gameClockText;
	sf::Text uitext;
	bool CESTBON = false;
	void initPlayer();
	void initBackground();
	void deleteEntity(int& i);
	void initAsset();
public:
	CGameState();
	CGameState(GameDataRef _data);
	CGameState(GameDataRef _data, CCharacter characterParam);
	~CGameState();
	void STEInit();
	void STEHandleInput();
	/**
	* Possibilities :
	* - roaming, a standard enemy
	* - shooter, an enemy with a big GUN PIOU PIOU
	*/
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
	GameDataRef getData();
};


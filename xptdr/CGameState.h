#pragma once
#include "CState.h"
#include "CJeu.h"
#include "DEFINITIONS.h"
#include "CPhysics.h"
#include <iostream>
#include "CPlayer.h"
#include "CGameMenu.h"
#include <sstream>
#include"CEnemy.h"
#include"CGameOver.h"
#include"CEntity.h"
#include"CBackground.h"
#include "CHittingEntity.h"
class CGameState : public CState
{
protected:
	GameDataRef data;
	sf::Time gameTime;
	sf::Clock gameClock;
	CPlayer player1;
	std::vector<CHittingEntity*> entityList;
	int enemyNumber = 0;
private:
	//engine related
	//std::vector<CEntity1> entityList;
	//Background related:
	//Sorte de booléen pour gérer le background
	int c1 = 0;
	CBackground BG1;

	sf::Text gameClockText;
	sf::Text uitext;
	bool CESTBON = false;
	void initPlayer();
	void initBackground();
	void initEnemy();
	void deleteEntity(int& i);
public:
	CGameState();
	CGameState(GameDataRef _data);
	~CGameState();
	void STEInit();
	void STEHandleInput();
	void addEnemy();
	void STEUpdate(float delta);
	void updateBackground(float delta);
	virtual void GameOver() = 0;
	void updateCollision(float dt);
	void DrawPlayer();
	void renderBackground();
	void STEDraw(float delta);
	void STEResume();
	void setData(GameDataRef dataa) { data = dataa; }
};


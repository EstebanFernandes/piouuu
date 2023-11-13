#pragma once
#include"CGameState.h"
#include "CPowerUp.h"
#include"CGrapheUpdate.h"
class CTestGame : public CGameState
{
private:
	std::vector<CGrapheUpdate> Upgradegraphs;
	int currentLevelOfplayer = 0;
public:

	CTestGame(GameDataRef _data); 
	CTestGame(GameDataRef _data, CCharacter characterParam);
	void STEInit();
	void STEHandleInput();
	void STEUpdate(float delta);
	void addPowerUp();
	void STEDraw(float delta);
	void GameOver();
};


#pragma once
#include"CGameState.h"
#include "CPowerUp.h"
class CTestGame : public CGameState
{
public:

	CTestGame(GameDataRef _data);
	void STEInit();
	void STEHandleInput();
	void STEUpdate(float delta);
	void addPowerUp();
	void STEDraw(float delta);
	void GameOver();
};


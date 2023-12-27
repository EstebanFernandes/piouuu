#pragma once
#include "CGameState.h"
class CInfiniteGameState : public CGameState
{
private:
	sf::Clock enemyClock;
public:
	CInfiniteGameState(GameDataRef _data);
	CInfiniteGameState(GameDataRef _data, CCharacter characterParam);
	void initAssets(){}
	void STEHandleInput();
	void STEUpdate(float delta);
	void STEDraw(float delta);
	void GameOver();
};


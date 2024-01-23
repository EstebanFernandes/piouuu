#pragma once
#include"CGameState.h"

#include"CGrapheUpdate.h"
class CTestGame : public CGameState
{
private:
	std::vector<CGrapheUpdate> Upgradegraphs;
	int currentLevelOfplayer = 0;
	bool isThistheEnd = false;
	bool hasLevelUp = false;
public:

	CTestGame(GameDataRef _data); 
	CTestGame(GameDataRef _data, CCharacter characterParam);

	void STEInit();
	void initAssets();
	void STEHandleInput();
	void STEUpdate(float delta);
	void addPowerUp();
	void STEDraw(float delta);
	void GameOver();
	void STEResume();
	void STEPause();
};


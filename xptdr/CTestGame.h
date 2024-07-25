#pragma once
#include"CGameState.h"
#include"bulletStorage.h"
#include"CGrapheUpdate.h"
#include"upgradeStock.h"
class CTestGame : public CGameState
{
private:
	std::string string;
public:
	std::vector<effetspecial*> globalBuffs;
	CTestGame(GameDataRef _data); 
	CTestGame(GameDataRef _data, CCharacter characterParam);
	CTestGame(GameDataRef _data, std::vector<CCharacter>& characterParam);
	void STEInit();
	void initAssets();
	void STEHandleInput(sf::Event& event);
	void STEDraw(float delta) 
	{
		drawOnTarget(data->window, delta);
	}
private:

	void debugInfo();
public:


	void addPowerUp();
	void GameOver();
	void STEUpdate(float delta);
	//void updateXpPlayers();
};


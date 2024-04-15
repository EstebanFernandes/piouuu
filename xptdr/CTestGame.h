#pragma once
#include"CGameState.h"
#include"bulletStorage.h"
#include"CGrapheUpdate.h"
#include"upgradeStock.h"
class CTestGame : public CGameState
{
public:
	CTestGame(GameDataRef _data); 
	CTestGame(GameDataRef _data, CCharacter characterParam);
	CTestGame(GameDataRef _data, std::vector<CCharacter>& characterParam);
	void STEInit();
	void initAssets();
	void STEHandleInput();
	void STEDraw(float delta) {
		sf::RenderWindow& r = data->window;
		r.clear(sf::Color::Red);
		renderBackground();
		for (auto i = players.begin(); i != players.end(); i++)
			i->renderEntity(data->window);
		for (int i = 0; i < entityList.size(); i++)
		{
			entityList[i]->renderEntity(r);
		}
		
		r.setView(data->window.getDefaultView());
		//Permet de remettre la vue par défaut et donc pas de soucis sur la suite
		for (int i = 0; i < entityList.size(); i++)
		{
			entityList[i]->renderUI(r);
		}
		for (auto i = players.begin(); i != players.end(); i++)
		{
			i->renderUI(data->window);
		}
		r.draw(uitext);
		r.draw(gameClockText);
	}

	void addPowerUp();
	void GameOver();
	void STEUpdate(float delta);
};


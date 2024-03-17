#pragma once
#include"CGameState.h"
#include"bulletStorage.h"
#include"CGrapheUpdate.h"
class CTestGame : public CGameState
{
private:
	CPlayer player2;
public:

	CTestGame(GameDataRef _data); 
	CTestGame(GameDataRef _data, CCharacter characterParam);

	void STEInit();
	void initAssets();
	void STEHandleInput();
	void STEDraw(float delta) {
		sf::RenderWindow& r = data->window;
		r.clear(sf::Color::Red);
		renderBackground();
		player1.renderEntity(r);
		player2.renderEntity(r);
		for (int i = 0; i < entityList.size(); i++)
		{
			entityList[i]->renderEntity(r);
		}
		
		//Permet de remettre la vue par défaut et donc pas de soucis sur la suite
		player1.renderUI(r);
		player2.renderUI(r);
		for (int i = 0; i < entityList.size(); i++)
		{
			entityList[i]->renderUI(r);
		}
		r.setView(data->window.getDefaultView());
		r.draw(uitext);
		r.draw(gameClockText);
		r.display();
	}

	void addPowerUp();
	void GameOver();
	void STEUpdate(float delta);
};


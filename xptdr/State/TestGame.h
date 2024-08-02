#pragma once
#include"GameState.h"
namespace StateNS {

class TestGame : public GameState
{
private:
	std::string string;
public:
	std::vector<effetspecial*> globalBuffs;
	TestGame(GameDataRef _data); 
	TestGame(GameDataRef _data, Character characterParam);
	TestGame(GameDataRef _data, std::vector<Character>& characterParam);
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


}
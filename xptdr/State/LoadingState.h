#pragma once
#include"State.h"
#include"../IO/ParserXML.h"
#include<thread>
#include"../Game/GameLogic//Level.h"
/// <summary>
/// écran de chargement qui load les infos sur un niveau
/// //écran posé au dessus de l'écran de base add is replacing false, on passe un pointeur vers le stockage du niveau
/// </summary>
//info nécessaire pour le parserXML pour load un niveau
struct infoForloading {
	std::vector<std::pair<std::string, std::string>>* assetToLoadForGame;
	Level* level;
	std::string fileName;
	bulletStorage* bulletStorage;
	upgradeStock* US;
	AssetManager* assetHandler;
	infoForloading() {
		level = NULL;
		assetToLoadForGame = NULL;
		fileName = "";
		bulletStorage=NULL;
		US = NULL;
		assetHandler = NULL;
	}
};
class LoadingState : public State
{
private:
	sf::Vector2f posPlayer;
	bool isPlayerSet = false;
	GameDataRef data;
	infoForloading info;
	std::list<Player>* players;
	std::vector<sf::Vector2f>playerPos;
	float speed = 0.1f;
	sf::Text validText;
	sf::Text levelNameText;
	void debugInfo()
	{
		posPlayer = players->front().getPosition();

		ImGui::Text(std::string("x pos : "+std::to_string(posPlayer.x) + " y pos : " + std::to_string(posPlayer.y)).c_str());


	}
public:
	LoadingState(GameDataRef data_,infoForloading info_, std::list<Player>* pointerToPlayers);
	void STEInit();
	void STEHandleInput(sf::Event& event);
	void STEUpdate(float delta);
	void STEDraw(float delta);

	void threadFunction(infoForloading* infoquoi);
};


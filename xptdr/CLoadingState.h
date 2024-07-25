#pragma once
#include"CState.h"
#include"CParserXML.h"
#include<thread>
#include"Level.h"
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
	infoForloading() {
		level = NULL;
		assetToLoadForGame = NULL;
		fileName = "";
		bulletStorage=NULL;
		US = NULL;
	}
};
class CLoadingState : public CState
{
private:
	bool isPlayerSet = false;
	GameDataRef data;
	infoForloading info;
	std::list<CPlayer>* players;
	std::vector<sf::Vector2f>playerPos;
	float speed = 0.1f;
	sf::Text validText;
	sf::Text levelNameText;
public:
	CLoadingState(GameDataRef data_,infoForloading info_, std::list<CPlayer>* pointerToPlayers);
	void STEInit();
	void STEHandleInput(sf::Event& event);
	void STEUpdate(float delta);
	void STEDraw(float delta);

	void threadFunction(infoForloading* infoquoi,CAssetManager* asset);
};


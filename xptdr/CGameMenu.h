#pragma once
#include "CState.h"
#include "DEFINITIONS.h"
#include "CMainMenuState.h"
class CGameMenu : public CState
{
private:
	GameDataRef data;
	// On met un petit compteur avant de reprendre
	bool resumeClicked = false;
	sf::Texture texta;
	sf::Sprite backGroundImage;
	sf::Text quitToMMenu;
	sf::Text resume;
	sf::Clock resumeClock;
	sf::Time ahah;
	bool mdrr = false;
public:
	CGameMenu(GameDataRef _data);
	void STEInit();
	void STEHandleInput();
	void STEUpdate(float delta);
	void STEDraw(float delta);
};


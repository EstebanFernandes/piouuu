#pragma once
#include <SFML/Graphics.hpp>
#include "CState.h"
#include "CJeu.h"
#include "DEFINITIONS.h"
#include <iostream>
#include "CMainMenuState.h"
#include"CParserCSV.h"
class CSplashState : public CState
{

private:
	GameDataRef data;
	bool CESTBON = false;
	sf::Clock CSSClock;
	sf::Sprite CSSBackground;
public:
	CSplashState(GameDataRef _data);

	void STEInit() ;
	void STEHandleInput(sf::Event& event);
	void STEUpdate(float delta);
	void STEDraw(float delta);

};


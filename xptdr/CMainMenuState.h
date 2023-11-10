#pragma once
#include"CScoreboardname.h"
#include "CState.h"
#include "CSettingState.h"
#include "DEFINITIONS.h"
#include <iostream>
#include <sstream>
#include "CHugoDecrypte.h"
#include "CCharacterSelection.h"
#include"SFML/Audio.hpp"

class CMainMenuState : public CState
{
private:
	GameDataRef data;
	sf::Clock CMMClock;
	sf::Sprite CMMBackground;
	sf::Text CMMPlayButton;
	sf::Text CMMHowToPlay;
	sf::Text CMMSettingsButton;
	sf::Text CMMQuitButton;
	sf::Text CMMInfinitePlayButton;
	sf::Sprite CMMTitle;
	CHugoDecrypte aaaa;
public:

	CMainMenuState(GameDataRef _data);
	void STEInit();
	void STEHandleInput();
	void STEUpdate(float delta);
	void STEDraw(float delta);
	void STEResume()
	{
		//CESTBON = false;
	}
};


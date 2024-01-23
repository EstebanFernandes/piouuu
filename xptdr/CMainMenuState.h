#pragma once
#include"CClavierVirtuel.h"
#include "CState.h"
#include "CSettingState.h"
#include "DEFINITIONS.h"
#include <iostream>
#include <sstream>
#include "CHugoDecrypte.h"
#include "CCharacterSelection.h"
#include"SFML/Audio.hpp"
#include"EllipseShape.h"
#include"CButton.h"
#include"InterfaceState.h"
class CMainMenuState : public CState, public InterfaceState
{
private:
	int index;
	GameDataRef data;
	sf::Clock CMMClock;
	std::vector<CButton> buttons;
	std::vector<float> where;
	sf::Sprite CMMTitle;
	sf::Text info;
	void choosedButton();
	void outline(int previndex);
public:

	CMainMenuState(GameDataRef _data);
	void STEInit();
	void STEHandleInput();
	void STEUpdate(float delta);
	void STEDraw(float delta);
	void STEResume()
	{
		resizeScreen();
	}
	void resizeScreen();
};


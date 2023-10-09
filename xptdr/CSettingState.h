#pragma once
#include "CState.h"
#include <TGUI/TGUI.hpp>
#include "DEFINITIONS.h"
#include <string.h>
#include "CJeu.h"
class CSettingState : public CState
{
private:
	GameDataRef data;
	//Attributs
	sf::Text backbutton;
public:
	//Constructeurs
	CSettingState(GameDataRef _data);
	void STEInit();
	void STEHandleInput();
	void STEUpdate(float delta);
	void STEDraw(float delta);

};


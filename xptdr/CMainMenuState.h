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
#include "LevelSelectionState.h"
class CMainMenuState : public CState, public InterfaceState
{
private:
	std::string blab = "";
	int index;
	GameDataRef data;
	sf::Clock CMMClock;
	std::vector<CButton> buttons;
	std::vector<float> where;
	sf::Sprite CMMTitle;
	sf::Text info;
	sf::Sound* buttonSound;
	/// <summary>
	/// Information about the character about to get played
	/// </summary>
	std::vector<CCharacter> characters;
	std::string nbJoueur;
	bool charaSet = false;

	/// <summary>
	/// nom du niveau � lancer
	/// </summary>
	std::string* levelToLaunch;
	bool isTest = false;
	void choosedButton();
	void addLevelType();
public:
	~CMainMenuState();
	CMainMenuState(GameDataRef _data);
	void STEInit();
	void STEHandleInput();
	void STEUpdate(float delta);
	void STEDraw(float delta);
	void STEResume();
	void resizeScreen();
};


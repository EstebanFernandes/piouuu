#pragma once
#include "CState.h"
#include "DEFINITIONS.h"
#include "CParserCSV.h"
#include <string.h>
#include "CJeu.h"
#include <SFML/Audio.hpp>
#include"CSlider.h"
#include"CCheckbox.h"
#include "CButton.h"
#include "InterfaceState.h"
#include "CBackground.h"
//Setting state, handle music/sound volume and full screen option
//a file text will save settings to be independant from any 
class CSettingState : public CState, public InterfaceState
{
private:
	std::vector<std::string> keyWord;
	std::vector<std::vector<std::string>> settingsInfo;
	std::vector<int> value;
	GameDataRef data;
	//Attributs
	
	/// <summary>
	/// index pour savoir sur quel controleur on se trouve (de base sur 0)
	/// </summary>
	int index;
	 CButton backbutton;
	CSlider musicVolume;
	CSlider SoundVolume;
	CCheckbox fullScreenCon;
	float outlineThickness = 10.f;
	CBackground background;
	bool isMovingUp = false;
	bool isMovingDown = false;
	bool isMovingLeft = false;
	bool isMovingRight = false;
	bool isEnterPressed = false;
	int matchKW(std::string word);

	void outlineGood(int index, int previousSelec);
public:
	//Constructeurs
	CSettingState(GameDataRef _data);
	void STEInit();
	void STEHandleInput();
	void STEUpdate(float delta);
	void STEDraw(float delta);
	void onAction(int index, int type);
	/// <summary>
	/// Update the settings.csv file with actual information
	/// </summary>
	void updateSettingsFile();
	/// <summary>
	/// méthode a appelé pour mettre en place tous les élements
	/// </summary>
	void resizeScreen();
};


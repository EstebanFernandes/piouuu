#pragma once
#include "State.h"
#include "../DEFINITIONS.h"
#include "../IO/ParserCSV.h"
#include <string.h>
#include "../Engine/MainLoop.h"
#include <SFML/Audio.hpp>
#include"../UI/Slider.h"
#include"../UI/Checkbox.h"
#include "../UI/Button.h"
#include "InterfaceState.h"
#include "../Engine/Background.h"

namespace StateNS {
	//Setting state, handle music/sound volume and full screen option
	//a file text contains settings informations
	class SettingState : public State, public InterfaceState
	{
	private:
		std::vector<std::string> keyWord;
		std::vector<std::vector<std::string>> settingsInfo;
		std::vector<int> value;
		GameDataRef data;
		sf::Sound* selectionButton;
		sf::Sound* slideSound;
		//Attributs
	
		/// <summary>
		/// index pour savoir sur quel controleur on se trouve (de base sur 0)
		/// </summary>
		int index;
		 Button backbutton;
		Slider musicVolume;
		Slider SoundVolume;
		Checkbox fullScreenCon;
		float outlineThickness = 10.f;
		bool isMovingUp = false;
		bool isMovingDown = false;
		bool isMovingLeft = false;
		bool isMovingRight = false;
		bool isEnterPressed = false;
		int matchKW(std::string word);

		void outlineGood(int index, int previousSelec);
	public:
		//Constructeurs
		SettingState(GameDataRef _data);
		void STEInit();
		void STEHandleInput(sf::Event& event);
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

}
#pragma once
#include "State.h"
#include "SettingState.h"
#include "../DEFINITIONS.h"
#include <iostream>
#include <sstream>
#include "CharacterSelection.h"
#include"SFML/Audio.hpp"
#include"../UI/Button.h"
#include"InterfaceState.h"
#include "LevelSelectionState.h"

namespace StateNS {

	class MainMenuState : public State, public InterfaceState
	{
	private:
		std::string blab = "";
		int index;
		GameDataRef data;
		sf::Clock CMMClock;
		std::vector<Button> buttons;
		std::vector<float> where;
		sf::Sprite CMMTitle;
		sf::Text info;
		sf::Sound* buttonSound;
		/// <summary>
		/// Information about the character about to get played
		/// </summary>
		std::vector<Character> characters;
		std::string nbJoueur;
		bool charaSet = false;

		/// <summary>
		/// nom du niveau à lancer
		/// </summary>
		std::string* levelToLaunch;
		bool isTest = false;
		void choosedButton();
		void addLevelType();
		sf::Sprite titleSprite;
		bool isUp = true;
		sf::RectangleShape demiFond;
		float scaleTitle = 1.f;
		sf::Shader lightShader;
		sf::Vector2f lightPoint;
		sf::Clock lightClock;
		sf::RenderTexture renderTexture;
		sf::Sprite spriteRender;
		float test1 = 0.f, test2 = 0.f,offset=0.f;
		std::string str1, str2;
		void debugInfo() {
			//if(std::abs(time - offset) <=1.f)
			/*test2++;
			ImGui::Text(std::string("STEUpdate : " + std::to_string(test1)).c_str());
			ImGui::Text(std::string("En dehors : " + std::to_string(test2)).c_str());
			if (std::abs(time - offset) <= 1.f)
				ImGui::Text(std::string("Temps écoulé : " + std::to_string(time)).c_str());
			else
				ImGui::Text("Temps écoulé : 1");*/
		}
	public:
		~MainMenuState();
		MainMenuState(GameDataRef _data);
		void STEInit();
		void STEHandleInput(sf::Event& event);
		void STEUpdate(float delta);
		void STEDraw(float delta);
		void STEResume();
		void resizeScreen();
		void updateTitle();
		void updateLight();
	};


}
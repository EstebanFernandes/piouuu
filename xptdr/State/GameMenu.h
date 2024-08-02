#pragma once
#include "State.h"
#include "../DEFINITIONS.h"
#include "MainMenuState.h"
namespace StateNS {
	class GameMenu : public State, public InterfaceState
	{
	private:
		GameDataRef data;
		State* gamePointer;
		// On met un petit compteur avant de reprendre
		bool resumeClicked = false;
		sf::Sprite backGroundImage;
		std::vector<Button> buttons;
		std::vector<float> where;
		sf::Shader blurShader;
		int index;
		sf::Clock resumeClock;
		sf::Time ahah;
		sf::Text decompte;
		bool mdrr = false;
		void choosedButton();
	public:
		GameMenu(GameDataRef _data,State* prevState);
		void STEInit();
		void STEHandleInput(sf::Event& event);
		void STEUpdate(float delta);
		void STEDraw(float delta);
		void outline(int previndex);
		void STEResume()
		{
			resizeScreen();
		}
		void resizeScreen();
	};

}
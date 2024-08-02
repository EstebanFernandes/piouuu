#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "../Engine/MainLoop.h"
#include "../DEFINITIONS.h"
#include <iostream>
#include "MainMenuState.h"
namespace StateNS {

class SplashState : public State
{

	private:
		GameDataRef data;
		bool CESTBON = false;
		sf::Clock CSSClock;
		sf::Sprite CSSBackground;
	public:
		SplashState(GameDataRef _data);

		void STEInit() ;
		void STEHandleInput(sf::Event& event);
		void STEUpdate(float delta);
		void STEDraw(float delta);

	};


}
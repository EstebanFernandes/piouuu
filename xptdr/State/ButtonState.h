#pragma once
#include"../Engine/MainLoop.h"
#include"../UI/Button.h"
#include"State.h"
/// <summary>
/// Classe qui permet de faire un choix entre plusieurs boutons
/// </summary>

namespace StateNS {
	class ButtonState : public State
	{
	private:
		sf::RectangleShape backFonce;
		GameDataRef data;
		std::vector<Button> buttonList;
		std::vector<std::string> choices;
		std::string* selected;
		int index;
		State* prevState;
		void choosedButton();
	public:
		ButtonState(GameDataRef _data);
		ButtonState(GameDataRef _data,std::vector<std::string> listOfChoices, std::string* choice,State* prevState);
		void STEInit();
		void STEHandleInput(sf::Event& event);
		void STEUpdate(float delta);
		void STEDraw(float delta);
	};


}
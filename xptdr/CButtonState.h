#pragma once
#include"CJeu.h"
#include"CButton.h"
#include"CState.h"
/// <summary>
/// Classe qui permet de faire un choix entre plusieurs boutons
/// </summary>
class CButtonState : public CState
{
private:
	sf::RectangleShape backFonce;
	sf::Texture back;
	sf::Sprite spritz;
	GameDataRef data;
	std::vector<CButton> buttonList;
	std::vector<std::string> choices;
	std::string* selected;
	int index;
	void choosedButton();
public:
	CButtonState(GameDataRef _data);
	CButtonState(GameDataRef _data,std::vector<std::string> listOfChoices, std::string* choice);
	void STEInit();
	void STEHandleInput();
	void STEUpdate(float delta);
	void STEDraw(float delta);
};


#pragma once
#include<string>
#include"DEFINITIONS.h"
#include "CState.h"
#include"SFML/Graphics.hpp"
#include <sstream>
#include "CJeu.h"

class CClavierVirtuel : public CState
{
private:
	GameDataRef data;
	enum maj { RELACHE, ENFONCE, LOCK };
	int capsInt = 0;
	sf::RectangleShape CapsLock;
	unsigned int position = 0;
	std::vector<std::string> keyboard;
	bool OUAIS = false;
	sf::Text ui;
	sf::Vector2i mouseSelectionRectangle = sf::Vector2i(0, 0);
	sf::RectangleShape ahouais;
	sf::Sprite capslocksprite;
	sf::Sprite keyboardWhiteSprite;
	sf::Sprite keyboardBlackSprite;
	sf::Vector2i mousePositionScreen;
	sf::Vector2f mousePositionKeyboard;
	sf::Vector2f tilePositionKeyboard;
	sf::Text nameText;
	sf::Text scorePrompt;
	std::string name;
	sf::Clock barClock;
	unsigned int stringPosition;
	bool cancel = false;
	sf::RectangleShape bar;
	float score;
	int rank;
	std::string* playerName;
public:
	CClavierVirtuel(GameDataRef _data, float scoreParam, int rankParam, std::string &playerNameParam);
	void keyboardInit();
	void STEInit();
	void STEHandleInput();
	void STEUpdate(float delta);
	void UpdateText();
	void drawBar();
	void STEDraw(float delta);
	void STEPause() {};
	void STEResume() {};
};


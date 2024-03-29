#pragma once
#include<string>
#include"DEFINITIONS.h"
#include "CState.h"
#include"SFML/Graphics.hpp"
#include <sstream>
#include "CJeu.h"
#include"utilities.h"
class CClavierVirtuel : public CState
{
private:
	struct keys {
		sf::Keyboard::Key up = sf::Keyboard::Z;
		sf::Keyboard::Key down = sf::Keyboard::S;
		sf::Keyboard::Key left = sf::Keyboard::Q;
		sf::Keyboard::Key right = sf::Keyboard::D;
		sf::Keyboard::Key press = sf::Keyboard::Num1;
	};
	GameDataRef data;
	enum maj { RELACHE, ENFONCE, LOCK };
	int capsInt = 0;
	sf::RectangleShape CapsLock;
	unsigned int position = 0;
	std::vector<std::string> keyboard;
	std::vector<bool> OUAIS;
	sf::Text ui;
	std::vector<sf::Vector2i> playerSelection;
	std::vector<sf::RectangleShape> ahouais;
	sf::Sprite capslocksprite;
	std::vector<sf::Sprite> keyboardPlayer;
	std::vector<sf::Sprite> keyboardLetterSprites;
	sf::Sprite keyboardBlackSprite;
	std::vector<sf::Vector2f> tilePositionsKeyboard;
	std::vector<sf::Text> nameTexts;
	/// ça correspond au barre sous le texte on en a 2 par joueur 
	std::vector < sf::Text > bars;
	std::vector<keys> keysPlayer;
	sf::Text scorePrompt;
	std::vector<std::string> names;
	std::vector<sf::Clock> barClocks;
	std::vector<float> yDirection;
	sf::Text midText;
	std::vector<unsigned int> stringPositions;
	bool cancel = false;
	float score;
	int rank;
	std::string* playerName;

	int numberCharMin = 3;
	int numberCharMax = 9;

	int nbJoueur = 0;

public:
	CClavierVirtuel(GameDataRef _data, float scoreParam, int rankParam, std::string *playerNameParam,int nbJoueur);
	void keyboardInit();
	void STEInit();
	void STEHandleInput();
	void STEUpdate(float delta);
	void UpdateText(int joueur);
	void STEDraw(float delta);
	void STEPause() {};
	void STEResume() {};
	void updateBars();
};


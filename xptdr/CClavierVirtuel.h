#pragma once
#include<string>
#include"DEFINITIONS.h"
#include "CState.h"
#include"SFML/Graphics.hpp"
#include <sstream>
#include "CJeu.h"
#include"utilities.h"
#include"CBackground.h"
class CClavierVirtuel : public CState
{
private:
	GameDataRef data;
	enum maj { RELACHE, ENFONCE, LOCK };
	int capsInt = 0;
	sf::RectangleShape CapsLock;
	unsigned int position = 0;
	std::vector<std::string> keyboard;
	sf::Text ui;
	sf::Sprite capslocksprite;
	sf::Sprite keyboardBlackSprite;
	/// ça correspond au barre sous le texte on en a 2 par joueur 
	std::vector<sf::Text> scorePrompts;
	sf::Text midText;
	bool cancel = false;
	float score;
	int rank;
	std::string* playerName;

	int numberCharMin = 3;
	int numberCharMax = 9;

	int nbJoueur = 0;
	struct joueur {
		inputPlayer* input;
		sf::RectangleShape fondBlanc; //Fond où on affiche le nom
		unsigned int stringPosition = 0; //Position de la bar, on peut faire fleche de droite pour écrire au milieu du text
		std::string name="";
		sf::Text nameText;
		sf::Text bar;
		float yDirection = 1.f;
		sf::Vector2f tilePositionsKeyboard;
		sf::Vector2i playerSelection = sf::Vector2i(0,0);//Savoir sur quelle case on est
		bool isValid = false; //On a validé ou pas
		sf::Sprite keyboardLetterSprite; //Sprite de la lettre sur laquelle on est
		sf::Sprite keyboardPlayer;//Sprite du contour de la lettre, la couleur change selon le joueur
		bool isPressed = false;
		bool dontshowBar = false;
	};
	std::vector<joueur> players;
public:
	CClavierVirtuel(GameDataRef _data, float scoreParam, int rankParam, std::string *playerNameParam,int nbJoueur);
	void keyboardInit();
	void STEInit();
	void STEHandleInput(sf::Event& event);
	void STEUpdate(float delta);
	void UpdateText(int joueur);
	void STEDraw(float delta);
	void STEPause() {};
	void STEResume() {};
	void updateBars(int index);
	void setBar(int index);
};


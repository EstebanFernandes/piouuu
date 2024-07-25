#pragma once
#include"CJeu.h"
#include<SFML/Graphics.hpp>
#include"CAnimation.h"
#include"CCharacter.h"
#include"SpinningCard.hpp"
class CCharacterSelectionMultiState : public CState
{
private:
	 struct avion{
		 sf::Sprite spriteAvion;
		 CAnimation animationAvion;
		 CCharacter characterAvion;
		 int niveau;//Si le niveau est à 0 c'est que personne ne l'a choisi, 
		 int MDRRcafonctionne = 0;
	 };
	 struct joueur {
		 inputPlayer* curInput;
		sf::Text avionName;
		sf::Text avionDescription;
		sf::Text avionplayerNumber;
		sf::Text trueAvionPlayerNumber;
		int index=0;
		float degree = 0.f;
		bool isValid = false;
		sf::FloatRect zone;
		sw::SpinningCard* spinArrow;
		sf::Sprite arrowSprite;
		sf::Sprite preViewSpriteFirst;
		sf::Sprite preViewSprite;
		bool sens = false;//if false on descend, true on monte pour la fleche
	};
	 float arrowMid=0.f;
		GameDataRef data;
		std::vector<avion> avions;
		sf::RectangleShape fondMiTransparent;
		std::vector<CCharacter>* pointerToCharacters;
		std::vector<joueur> players;
		sf::RectangleShape deuxiemefond;
		sf::Text Titre;
		sf::Sound* selectionSound;
		sf::Sound* validationSound;
		sf::Text returnTexte;//Texte qu'on affiche lorsqu'on appuie sur le bouton pour revenir en arrière
		sf::RectangleShape retourBar;
		float maxArrow;
		float minArrow;
		bool isPressingReturn = false;
		sf::Clock returnClock;
		bool containChanges = false;
		void loadCharacters();
		//On l'appelle après loadCharacters
		void setAvionPosition();
		void updateAvions();
		void initTexts(joueur& curJoeur,int index);
		void updateTexts(int index);
		void resizeText(sf::FloatRect zone,sf::Text& textToResize, unsigned int charSize, bool divided = true);
		void updateArrow(int index);
		void drawElements(bool onlyAvion=false);
public:
	~CCharacterSelectionMultiState();
	CCharacterSelectionMultiState(GameDataRef data_);
	CCharacterSelectionMultiState(GameDataRef data_,std::vector<CCharacter>* pointerToVectCharact);
	void STEInit();
	void STEHandleInput(sf::Event& event);
	void STEUpdate(float dt);
	void STEDraw(float interpolation);

};


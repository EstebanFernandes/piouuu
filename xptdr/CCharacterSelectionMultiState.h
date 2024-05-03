#pragma once
#include"CJeu.h"
#include<SFML/Graphics.hpp>
#include"CAnimation.h"
#include"CCharacter.h"
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
		keys keys;
		sf::Text avionName;
		sf::Text avionDescription;
		sf::Text avionplayerNumber;
		sf::Text trueAvionPlayerNumber;
		int index=0;
		bool isValid = false;
		sf::FloatRect zone;
		sf::Sprite arrowSprite;
		sf::Sprite preViewSprite;
		bool sens = false;//if false on descend, true on monte pour la fleche
	};
		GameDataRef data;
		std::vector<avion> avions;
		sf::RectangleShape fondMiTransparent;
		std::vector<CCharacter>* pointerToCharacters;
		std::vector<joueur> players;
		sf::RectangleShape deuxiemefond;
		sf::Shader bwShader;
		sf::Text Titre;
		sf::Sound* selectionSound;
		sf::Sound* validationSound;
		float maxArrow;
		float minArrow;
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
	CCharacterSelectionMultiState(GameDataRef data_);
	CCharacterSelectionMultiState(GameDataRef data_,std::vector<CCharacter>* pointerToVectCharact);
	void STEInit();
	void STEHandleInput();
	void STEUpdate(float dt);
	void STEDraw(float interpolation);

};


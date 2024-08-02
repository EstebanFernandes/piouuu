#pragma once
#include"../Engine/MainLoop.h"
#include<SFML/Graphics.hpp>
#include"../Engine/Animation.h"
#include"../Game/Character.h"
#include"../UI/SpinningCard.hpp"
namespace StateNS {
	class CharacterSelectionMultiState : public State
	{
	private:
		 struct avion{
			 sf::Sprite spriteAvion;
			 Animation animationAvion;
			 Character characterAvion;
			 int niveau;//Si le niveau est à 0 c'est que personne ne l'a choisi, 
			 int MDRRcafonctionne = 0;
		 };
		 struct joueur {
			 InputPlayer* curInput;
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
			std::vector<Character>* pointerToCharacters;
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
		~CharacterSelectionMultiState();
		CharacterSelectionMultiState(GameDataRef data_);
		CharacterSelectionMultiState(GameDataRef data_,std::vector<Character>* pointerToVectCharact);
		void STEInit();
		void STEHandleInput(sf::Event& event);
		void STEUpdate(float dt);
		void STEDraw(float interpolation);

	};
}


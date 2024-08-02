#pragma once
#include <vector>
#include"../UI/Carousel.h"
#include"../Engine/MainLoop.h"
#include"../Engine/Background.h"
#include"../UI/ShakeSpinningCard.h"
namespace StateNS {
	class CharacterSelection : public State
	{
	private :
		float shakeAngle = 0.f;
		int state=0;
		int nb = -1;
		bool isMovingRight = false;
		bool isMovingLeft = false;
		bool drawMask = false;
		GameDataRef data;
		std::vector<Character> characterList;
		int currentCharacterIndex;
		Character chosenCharacter;
		Carousel carousel;
		sf::Text Title;
		Character* returnChar = NULL;
		sf::Sound* selectionSound;
		sf::Sound* validationSound;
		sf::RectangleShape mask;
		float speedCard =3.f;
		float timec = -1.f;
		sf::Text UIText;
		ShakeSpinningCard shakeitoff;

		//Method use to handle animation
		//Retourne true si l'animation est fini
		bool animationEffect(float& dt);

		void debugInfo() {
			ImGui::InputFloat("Shake angle", &shakeAngle);
		}
	public:
		// Constructeur
		CharacterSelection(GameDataRef _data);
		~CharacterSelection();
		CharacterSelection(GameDataRef _data, Character* ch)
			: CharacterSelection(_data) {
			returnChar = ch;
		}
		CharacterSelection(GameDataRef _data, Character* ch, int numero)
			:CharacterSelection(_data, ch)
		{
			nb = numero;
		}
		void loadCharacters();
		void loadCarousel();
		
		void STEInit();
		void STEHandleInput(sf::Event& event);
		void STEUpdate(float delta);
		void STEDraw(float delta);

	};
}
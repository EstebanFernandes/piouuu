#pragma once
#include <vector>
#include"CCarousel.h"
#include"CJeu.h"
#include"CBackground.h"
#include"ShakeSpinningCard.h"
class CCharacterSelection : public CState
{
private :
	float shakeAngle = 0.f;
	int state=0;
	int nb = -1;
	bool isMovingRight = false;
	bool isMovingLeft = false;
	bool drawMask = false;
	GameDataRef data;
	std::vector<CCharacter> characterList;
	int currentCharacterIndex;
	CCharacter chosenCharacter;
	CCarousel carousel;
	sf::Text Title;
	CCharacter* returnChar = NULL;
	sf::Sound* selectionSound;
	sf::Sound* validationSound;
	sf::RectangleShape mask;
	float speedCard = 1.5f;
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
	CCharacterSelection(GameDataRef _data);
	~CCharacterSelection();
	CCharacterSelection(GameDataRef _data, CCharacter* ch)
		: CCharacterSelection(_data) {
		returnChar = ch;
	}
	CCharacterSelection(GameDataRef _data, CCharacter* ch, int numero)
		:CCharacterSelection(_data, ch)
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
#pragma once
#include <vector>
#include"CCarousel.h"
#include"CJeu.h"
class CCharacterSelection : public CState
{
private :
	int nb = -1;
	bool isMovingRight = false;
	bool isMovingLeft = false;
	GameDataRef data;
	std::vector<CCharacter> characterList;
	int currentCharacterIndex;
	CCharacter chosenCharacter;
	CCarousel carousel;
	sf::Text Title;
	CCharacter* returnChar = NULL;
	sf::Text ui;
	sf::Vector2i mousePositionScreen;
	bool LaunchTransi = false;
public:
	// Constructeur
	CCharacterSelection(GameDataRef _data);
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
		
	void STEInit();
	void STEHandleInput();
	void STEUpdate(float delta);
	void STEDraw(float delta);

};
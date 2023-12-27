#pragma once
#include <vector>
#include "CState.h"
#include "CSettingState.h"
#include"CCarousel.h"

class CCharacterSelection : public CState
{
private :
	bool isMovingRight = false;
	bool isMovingLeft = false;
	GameDataRef data;
	std::vector<CCharacter> characterList;
	int currentCharacterIndex;
	CCharacter chosenCharacter;
	CCarousel carousel;
	sf::Text Title;

	sf::Text ui;
	sf::Vector2i mousePositionScreen;

public:
	// Constructeur
	CCharacterSelection(GameDataRef _data);
	void loadCharacters();

	void STEInit();
	void STEHandleInput();
	void STEUpdate(float delta);
	void STEDraw(float delta);

};
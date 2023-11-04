#pragma once
#include <vector>
#include "CState.h"
#include "CSettingState.h"
#include "CCard.h"
#include "CCharacter.h"

class CCharacterSelection : public CState
{
private :
	GameDataRef data;
	std::vector<CCharacter> characterList;
	int currentCharacterIndex;
	CCharacter chosenCharacter;
	CCard characterCard;

	sf::Sprite CMMBackground;
	sf::CircleShape triangle1;
	sf::CircleShape triangle2;

public:
	// Constructeur
	CCharacterSelection(GameDataRef _data);
	void loadCharacters();

	void STEInit();
	void STEHandleInput();
	void STEUpdate(float delta);
	void STEDraw(float delta);
};


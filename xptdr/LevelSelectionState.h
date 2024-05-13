#pragma once
#include "CState.h"
#include "CJeu.h"
#include "CCharacter.h"
#include "CCharacterSelection.h"
#include "CCharacterSelectionMultiState.h"
#include "CButton.h"
#include "CParserXML.h"

#include <filesystem>

struct levelData {
	CButton button;
	std::string levelName;
	std::string creatorName;
	std::string description;
	bool isInfinite;
};

class LevelSelectionState : public CState
{
private:
	GameDataRef data;
	/// <summary>
	/// Utile pour la suite du programme, (choix des personnages)
	/// </summary>
	std::vector<CCharacter>* characters;
	/// <summary>
	/// rectangle d'arri�re plan de la partie o� le nom des niveaux sont affich�s
	/// </summary>
	sf::RectangleShape levelNamesBackground;
	/// <summary>
	/// rectangle d'arri�re plan de la partie o� la description des niveaux est affich�e
	/// </summary>
	sf::RectangleShape levelDescriptionBackground;

	/// <summary>
	/// Booleen qui indique si le state doit �tre supprimer
	/// </summary>
	bool toRemove = false;

	/// <summary>
	/// Liste des niveaux pr�sents dans le dossier "level"
	/// </summary>
	std::vector<levelData> levels;

	/// <summary>
	/// index du niveau s�lectionn�
	/// </summary>
	int levelIndex = 0;

	/// <summary>
	/// Pointeur vers le niveau � lancer de CMainMenu
	/// </summary>
	std::string* levelToLauch;

	/// <summary>
	/// M�thodes permettant d'initialiser les donn�es des niveaux
	/// </summary>
	void initLevelDatas();
public:
	LevelSelectionState(GameDataRef _data);
	//LevelSelectionState(GameData _data, CCharacter* character, int numero);
	LevelSelectionState(GameDataRef _data, std::vector<CCharacter>* charactersParam, std::string* levelToLauchParam);

	void STEInit();
	void STEHandleInput();
	void STEUpdate(float delta);
	void STEDraw(float delta); // diff�rence entre les frames
	void STEResume();
};


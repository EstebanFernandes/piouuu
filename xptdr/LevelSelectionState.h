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
	/// rectangle d'arrière plan de la partie où le nom des niveaux sont affichés
	/// </summary>
	sf::RectangleShape levelNamesBackground;
	/// <summary>
	/// rectangle d'arrière plan de la partie où la description des niveaux est affichée
	/// </summary>
	sf::RectangleShape levelDescriptionBackground;

	/// <summary>
	/// Booleen qui indique si le state doit être supprimer
	/// </summary>
	bool toRemove = false;

	/// <summary>
	/// Liste des niveaux présents dans le dossier "level"
	/// </summary>
	std::vector<levelData> levels;

	/// <summary>
	/// index du niveau sélectionné
	/// </summary>
	int levelIndex = 0;

	/// <summary>
	/// Pointeur vers le niveau à lancer de CMainMenu
	/// </summary>
	std::string* levelToLauch;

	/// <summary>
	/// Méthodes permettant d'initialiser les données des niveaux
	/// </summary>
	void initLevelDatas();
public:
	LevelSelectionState(GameDataRef _data);
	//LevelSelectionState(GameData _data, CCharacter* character, int numero);
	LevelSelectionState(GameDataRef _data, std::vector<CCharacter>* charactersParam, std::string* levelToLauchParam);

	void STEInit();
	void STEHandleInput();
	void STEUpdate(float delta);
	void STEDraw(float delta); // différence entre les frames
	void STEResume();
};


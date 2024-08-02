#pragma once
#include "State.h"
#include "../Engine/MainLoop.h"
#include "../Game/Character.h"
#include "CharacterSelection.h"
#include "CharacterSelectionMultiState.h"
#include "../UI/Button.h"
#include "../IO/ParserXML.h"

#include <filesystem>

namespace StateNS {

	struct levelData {
		Button button;
		std::string levelName;
		std::string creatorName;
		std::string description;
		bool isInfinite;
	};

	class LevelSelectionState : public State
	{
	private:
		GameDataRef data;
		/// <summary>
		/// Utile pour la suite du programme, (choix des personnages)
		/// </summary>
		std::vector<Character>* characters;
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
		//LevelSelectionState(GameData _data, Character* character, int numero);
		LevelSelectionState(GameDataRef _data, std::vector<Character>* charactersParam, std::string* levelToLauchParam);

		void STEInit();
		void STEHandleInput(sf::Event& event);
		void STEUpdate(float delta);
		void STEDraw(float delta); // différence entre les frames
		void STEResume();
	};


}
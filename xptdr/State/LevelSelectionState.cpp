#include "LevelSelectionState.h"

void StateNS::LevelSelectionState::initLevelDatas()
{
	std::string folderPath = "res/level";
	std::vector<std::string> levelNames;

	// On parcourt les fichiers du dossier folderPath
	for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
		// On vérifie si l'entrée est un fichier et on ne conserve que les fichiers .piou
		if (entry.is_regular_file() && entry.path().extension() == ".piou") {
			levelNames.push_back(entry.path().filename().string());
		}
	}

	// On lit les données de chaque niveau
	for (std::string it : levelNames) {
		ParserXML parser(it, nullptr, nullptr);
		std::vector<std::string> result = parser.searchLevelDatas(it);
		levelData data;
		data.levelName = it;
		(result[0] == "1") ? data.isInfinite = true : data.isInfinite = false;
		data.description = it[1];
		data.creatorName = it[2];
		levels.push_back(data);
	}
}

StateNS::LevelSelectionState::LevelSelectionState(GameDataRef _data)
{
	data = _data;
	initLevelDatas();
}

StateNS::LevelSelectionState::LevelSelectionState(GameDataRef _data, std::vector<Character>* charactersParam, std::string* levelToLauchParam) : LevelSelectionState(_data)
{
	characters = charactersParam;
	levelToLauch = levelToLauchParam;
}

void StateNS::LevelSelectionState::STEInit()
{
	// Taille du background des noms de niveau : 
	// x : 40% de la largeur
	// y : 75% de la hauteur
	sf::Vector2f size = sf::Vector2f(Engine::SCREEN_WIDTH * 0.40f, Engine::SCREEN_HEIGHT * 0.80f);
	levelNamesBackground.setSize(size);

	// Taille du background des descriptions de niveau : 
	// x : 35% de la largeur
	// y : 75% de la hauteur
	size = sf::Vector2f(Engine::SCREEN_WIDTH * 0.35f, Engine::SCREEN_HEIGHT * 0.80f);
	levelDescriptionBackground.setSize(size);

	// Position des background

	float x = Engine::SCREEN_WIDTH * 0.10f;
	float y = Engine::SCREEN_HEIGHT * 0.1f;
	levelNamesBackground.setPosition(x, y);

	x = x + levelNamesBackground.getSize().x + Engine::SCREEN_WIDTH * 0.05f;
	levelDescriptionBackground.setPosition(x, y);

	// Afficher les noms des niveaux
	for (int i = 0; i < levels.size(); i++) {
		Button button(&data.get()->assets, levelNamesBackground.getSize().x, levelNamesBackground.getSize().y / 15.f);
		button.setPosition(levelNamesBackground.getPosition().x, levelNamesBackground.getPosition().y + i * levelNamesBackground.getSize().y / 15.f);
		button.setString(levels[i].levelName);

		if (i == 0) button.setOutlineThickness(3.f);

		levels[i].button = button;

	}
}

void StateNS::LevelSelectionState::STEHandleInput(sf::Event& event)
{
	
		if (sf::Event::Closed == event.type) {
			data->window.close();
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == inputOfPlayers[0].button1) {
				// On enregistre le niveau sélectionné dans le pointeur
				*levelToLauch = levels[levelIndex].levelName;
				// TEMP on passe à l'étape suivante
				if (characters->size() == 1)
				{
					data->machine.AddState(StateRef(new CharacterSelection(data, &characters->back(), (int)characters->size())), false);
				}
				else if (characters->size() >= 2)
				{
					data->machine.AddState(StateRef(new CharacterSelectionMultiState(data, characters)), false);
				}
			}
			int previousSelec = levelIndex;
			if (event.key.code == inputOfPlayers[0].moveUp) {
				if (levelIndex == 0) {
					levelIndex = (int)levels.size() - 1;
				}
				else {
					levelIndex = (levelIndex - 1) % levels.size();
				}
			}
			else if (event.key.code == inputOfPlayers[0].moveDown) {
				levelIndex = (levelIndex + 1) % levels.size();
			}
			else if (event.key.code == inputOfPlayers[0].button2) {
				data->machine.RemoveState();
			}
			levels[previousSelec].button.setOutlineThickness(0.f);
			levels[levelIndex].button.setOutlineThickness(3.f);
		}
}

void StateNS::LevelSelectionState::STEUpdate(float delta)
{
	// Pour supprimer le state
	if (toRemove) {
		data->machine.RemoveState();
	}
	// Nécessaire au background
	updateTime();
	background.updateBackground(delta);
}

void StateNS::LevelSelectionState::STEDraw(float delta)
{
	if (!toRemove) {
		background.renderBackground(data->window);
		data->window.draw(levelDescriptionBackground);
		data->window.draw(levelNamesBackground);
		for (levelData level : levels) {
			data->window.draw(level.button);
		}
	}
}

void StateNS::LevelSelectionState::STEResume()
{
	toRemove = true;
}

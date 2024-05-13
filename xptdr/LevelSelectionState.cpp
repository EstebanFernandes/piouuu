#include "LevelSelectionState.h"

void LevelSelectionState::initLevelDatas()
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
		CParserXML parser(it, nullptr, nullptr);
		std::vector<std::string> result = parser.searchLevelDatas(it);
		levelData data;
		data.levelName = it;
		(result[0] == "1") ? data.isInfinite = true : data.isInfinite = false;
		data.description = it[1];
		data.creatorName = it[2];
		levels.push_back(data);
	}
}

LevelSelectionState::LevelSelectionState(GameDataRef _data)
{
	data = _data;
	initLevelDatas();
}

LevelSelectionState::LevelSelectionState(GameDataRef _data, std::vector<CCharacter>* charactersParam, std::string* levelToLauchParam) : LevelSelectionState(_data)
{
	characters = charactersParam;
	levelToLauch = levelToLauchParam;
}

void LevelSelectionState::STEInit()
{
	// Taille du background des noms de niveau : 
	// x : 40% de la largeur
	// y : 75% de la hauteur
	sf::Vector2f size = sf::Vector2f(data->assets.sCREEN_WIDTH * 0.40f, data->assets.sCREEN_HEIGHT * 0.80f);
	levelNamesBackground.setSize(size);

	// Taille du background des descriptions de niveau : 
	// x : 35% de la largeur
	// y : 75% de la hauteur
	size = sf::Vector2f(data->assets.sCREEN_WIDTH * 0.35f, data->assets.sCREEN_HEIGHT * 0.80f);
	levelDescriptionBackground.setSize(size);

	// Position des background

	float x = data->assets.sCREEN_WIDTH * 0.10f;
	float y = data->assets.sCREEN_HEIGHT * 0.1f;
	levelNamesBackground.setPosition(x, y);

	x = x + levelNamesBackground.getSize().x + data->assets.sCREEN_WIDTH * 0.05f;
	levelDescriptionBackground.setPosition(x, y);

	// Afficher les noms des niveaux
	for (int i = 0; i < levels.size(); i++) {
		CButton button(&data.get()->assets, levelNamesBackground.getSize().x, levelNamesBackground.getSize().y / 15.f);
		button.setPosition(levelNamesBackground.getPosition().x, levelNamesBackground.getPosition().y + i * levelNamesBackground.getSize().y / 15.f);
		button.setString(levels[i].levelName);

		if (i == 0) button.setOutlineThickness(3.f);

		levels[i].button = button;

	}
}

void LevelSelectionState::STEHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event)) {
		if (sf::Event::Closed == event.type) {
			data->window.close();
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Enter) {
				// On enregistre le niveau sélectionné dans le pointeur
				*levelToLauch = levels[levelIndex].levelName;
				// TEMP on passe à l'étape suivante
				if (characters->size() == 1)
				{
					data->machine.AddState(StateRef(new CCharacterSelection(data, &characters->back(), (int)characters->size())), false);
				}
				else if (characters->size() >= 2)
				{
					data->machine.AddState(StateRef(new CCharacterSelectionMultiState(data, characters)), false);
				}
			}
			int previousSelec = levelIndex;
			if (event.key.code == sf::Keyboard::Z) {
				if (levelIndex == 0) {
					levelIndex = (int)levels.size() - 1;
				}
				else {
					levelIndex = (levelIndex - 1) % levels.size();
				}
			}
			else if (event.key.code == sf::Keyboard::S) {
				levelIndex = (levelIndex + 1) % levels.size();
			}
			levels[previousSelec].button.setOutlineThickness(0.f);
			levels[levelIndex].button.setOutlineThickness(3.f);
		}
	}
}

void LevelSelectionState::STEUpdate(float delta)
{
	// Pour supprimer le state
	if (toRemove) {
		data->machine.RemoveState();
	}
	// Nécessaire au background
	updateTime();
	background.updateCBackground(delta);
}

void LevelSelectionState::STEDraw(float delta)
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

void LevelSelectionState::STEResume()
{
	toRemove = true;
}

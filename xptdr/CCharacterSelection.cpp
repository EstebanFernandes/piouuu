#include "CCharacterSelection.h"
#include "CTestGame.h"
#include "CParserCSV.h"
#include <typeinfo>

CCharacterSelection::CCharacterSelection(GameDataRef _data) : data(_data)
{
	currentCharacterIndex = 0;
}

void CCharacterSelection::loadCharacters()
{
	CParserCSV parser = CParserCSV("res/data/characters.csv");
	std::vector<std::vector<std::string>> charactersInfo = parser.getElements();

	//Nouvelle méthode pour initialiser les stats
	for (int i = 1; i < charactersInfo.size(); i++) {
		characterList.push_back(CCharacter(charactersInfo[i][1], charactersInfo[i][0], charactersInfo[i][2], charactersInfo[i][3] == "animated"));
		data->assets.LoadTexture(charactersInfo[i][0], charactersInfo[i][1]);

		int maxHealthPointTemp = 20;
		if (charactersInfo[i][4] != "" && typeid(std::stoi(charactersInfo[i][4])) == typeid(int)) maxHealthPointTemp = std::stoi(charactersInfo[i][4]);

		float moveSpeedTemp = 0.5f;
		if (charactersInfo[i][5] != "" && typeid(std::stof(charactersInfo[i][5])) == typeid(float)) moveSpeedTemp = std::stof(charactersInfo[i][5]);

		int canonNumberTemp = 1;
		if (charactersInfo[i][6] != "" && typeid(std::stoi(charactersInfo[i][6])) == typeid(int)) canonNumberTemp = std::stoi(charactersInfo[i][6]);

		int damagePerBulletTemp = 5;
		if (charactersInfo[i][7] != "" && typeid(std::stoi(charactersInfo[i][7])) == typeid(int)) damagePerBulletTemp = std::stoi(charactersInfo[i][7]);

		float attackSpeedTemp = 8.f;
		if (charactersInfo[i][8] != "" && typeid(std::stof(charactersInfo[i][8])) == typeid(float)) attackSpeedTemp = std::stof(charactersInfo[i][8]);

		float bulletSpeedTemp = 2.0f;
		if (charactersInfo[i][9] != "" && typeid(std::stof(charactersInfo[i][9])) == typeid(float)) bulletSpeedTemp = std::stof(charactersInfo[i][9]);

		characterList[i - 1].setCharacterStats(maxHealthPointTemp, moveSpeedTemp, canonNumberTemp, damagePerBulletTemp, attackSpeedTemp, bulletSpeedTemp);

	}

	//ancienne
	/*
	for (int i = 0; i < charactersInfo.size(); i++) {
		characterList.push_back(CCharacter(charactersInfo[i][1], charactersInfo[i][0], charactersInfo[i][2], charactersInfo[i][3]=="animated"));
		data->assets.LoadTexture(charactersInfo[i][0], charactersInfo[i][1]);
	}
	*/
}

void CCharacterSelection::STEInit()
{
	loadCharacters();
	data->assets.LoadFont("Lato", FONT_FILE_PATH); //Load la police d'écriture

	//temp
	data->assets.LoadTexture("backgroundCharacter", CHARACTERBACKGROUND);
	chosenCharacter = characterList[currentCharacterIndex];
	characterCard = CCard(chosenCharacter.getName(), chosenCharacter.getDescription(), chosenCharacter.getName(), &(data->assets), chosenCharacter.getAnimated());

	CMMBackground.setTexture(data->assets.GetTexture("Background"));
	CMMBackground.setScale(1.2f, 1.2f);

	triangle1 = sf::CircleShape(80.f, 3);
	triangle1.rotate(270.f);
	triangle1.setFillColor(sf::Color::Color(64, 64, 64));
	triangle1.setPosition(275.f, (float)data->assets.sCREEN_HEIGHT/2);

	triangle2 = sf::CircleShape(80.f, 3);
	triangle2.rotate(90.f);
	triangle2.setFillColor(sf::Color::Color(64, 64, 64));
	triangle2.setPosition(275+320 +((float)data->assets.sCREEN_WIDTH / 3.f), data->assets.sCREEN_HEIGHT / 2.f);
}

void CCharacterSelection::STEHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event)) {

		//Pour pouvoir fermer la fenêtre
		if (sf::Event::Closed == event.type) {
			data->window.close();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			data->machine.AddState(StateRef(new CTestGame(data, chosenCharacter)), true);
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::D)
			{
				currentCharacterIndex = (currentCharacterIndex + 1) % characterList.size();
				chosenCharacter = characterList[currentCharacterIndex];
				characterCard = CCard(chosenCharacter.getName(), chosenCharacter.getDescription(), chosenCharacter.getName(), &(data->assets), chosenCharacter.getAnimated());
			}
			else if (event.key.code == sf::Keyboard::Q)
			{
				if (currentCharacterIndex == 0) {
					currentCharacterIndex = characterList.size() - 1;
				}
				else {
					currentCharacterIndex = (currentCharacterIndex - 1) % characterList.size();
				}
				chosenCharacter = characterList[currentCharacterIndex];
				characterCard = CCard(chosenCharacter.getName(), chosenCharacter.getDescription(), chosenCharacter.getName(), &(data->assets), chosenCharacter.getAnimated());
			}
		}
	}
}

void CCharacterSelection::STEUpdate(float delta)
{
	characterCard.update(delta);
}

void CCharacterSelection::STEDraw(float delta)
{
	data->window.clear(sf::Color::Red);
	data->window.draw(CMMBackground);
	data->window.draw(characterCard);
	data->window.draw(triangle1);
	data->window.draw(triangle2);
	data->window.display();
}


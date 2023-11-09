#include "CCharacterSelection.h"
#include "CTestGame.h"
#include "CParserCSV.h"

CCharacterSelection::CCharacterSelection(GameDataRef _data) : data(_data)
{
	currentCharacterIndex = 0;
}

void CCharacterSelection::loadCharacters()
{
	CParserCSV parser = CParserCSV("res/data/characters.txt");
	std::vector<std::vector<std::string>> charactersInfo = parser.getElements();

	for (int i = 0; i < charactersInfo.size(); i++) {
		characterList.push_back(CCharacter(charactersInfo[i][1], charactersInfo[i][0], charactersInfo[i][2]));
		data->assets.LoadTexture(charactersInfo[i][0], charactersInfo[i][1]);
	}
}

void CCharacterSelection::STEInit()
{
	loadCharacters();
	data->assets.LoadFont("Lato", FONT_FILE_PATH); //Load la police d'écriture

	//temp
	data->assets.LoadTexture("backgroundCharacter", CHARACTERBACKGROUND);
	chosenCharacter = characterList[currentCharacterIndex];
	characterCard = CCard(chosenCharacter.getName(), chosenCharacter.getDescription(), chosenCharacter.getName(), &(data->assets));

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
			data->machine.AddState(StateRef(new CTestGame(data)), true);
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::D)
			{
				currentCharacterIndex = (currentCharacterIndex + 1) % characterList.size();
				chosenCharacter = characterList[currentCharacterIndex];
				characterCard = CCard(chosenCharacter.getName(), chosenCharacter.getDescription(), chosenCharacter.getName(), &(data->assets));
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
				characterCard = CCard(chosenCharacter.getName(), chosenCharacter.getDescription(), chosenCharacter.getName(), &(data->assets));
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


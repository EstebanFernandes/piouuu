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

	//Nouvelle m�thode pour initialiser les stats
	for (int i = 1; i < charactersInfo.size(); i++) {
		characterList.push_back(CCharacter(charactersInfo[i][1], charactersInfo[i][0], charactersInfo[i][2], charactersInfo[i][3] == "animated"));
		data->assets.LoadTexture(charactersInfo[i][0], charactersInfo[i][1]);

		float maxHealthPointTemp = 20;
		if (charactersInfo[i][4] != "" && typeid(std::stof(charactersInfo[i][4])) == typeid(int)) maxHealthPointTemp = std::stof(charactersInfo[i][4]);

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
}

void CCharacterSelection::STEInit()
{
	int screenwidth = data->assets.sCREEN_WIDTH;
	int screenheight = data->assets.sCREEN_HEIGHT;
	loadCharacters();
	data->assets.LoadFont("Lato", FONT_FILE_PATH); //Load la police d'�criture

	//temp

	//on a load les personnages donc on va les mettre dans le carousel
	int maxPoint = (int)carousel.ellipse.getPointCount();
	int nbCharacter = (int)characterList.size();

	carousel.setSize(sf::Vector2f(screenwidth*0.35f, screenwidth*0.03f));
	sf::Vector2f carouselPos((float)screenwidth / 2 - carousel.ellipse.getGlobalBounds().width/2,
		(float)screenheight * 0.02f);
	carousel.setCarouselPosition(carouselPos);
	carousel.setEllipseVisibility(false);
	for (int i = 0; i < characterList.size(); i++)
	{
		chosenCharacter = characterList[i];
		CCard temp(chosenCharacter.getName(), chosenCharacter.getDescription(), chosenCharacter.getName(), &(data->assets), chosenCharacter.getAnimated());
		temp.setOutlineThickNess(10.f);
		carousel.addCard(temp);
	}
	chosenCharacter = characterList[0];
}

void CCharacterSelection::STEHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event)) {
		switch (event.type)
		{
		case sf::Event::KeyPressed:
		 if (event.key.code == sf::Keyboard::D)
			{
				if (!carousel.isMoving)
					isMovingLeft = true;
			}
			else if (event.key.code == sf::Keyboard::Q)
			{
				if (!carousel.isMoving)
					isMovingRight = true;
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
			 if(!carousel.isMoving)
				 data->machine.AddState(StateRef(new CTestGame(data, chosenCharacter)), true);
			}
			break;
		case sf::Event::Closed:
			data->window.close();
			break;
		}
	}
}


void CCharacterSelection::STEUpdate(float delta)
{
	if (isMovingLeft)
	{
			currentCharacterIndex = (currentCharacterIndex + 1) % characterList.size();
			chosenCharacter = characterList[currentCharacterIndex];
			if (carousel.move(LeftMove))
				isMovingLeft = false;
	}
	if (isMovingRight)
	{
			if (currentCharacterIndex == 0) {
				currentCharacterIndex = (int)characterList.size() - 1;
			}
			else
				currentCharacterIndex = (currentCharacterIndex - 1) % characterList.size();
			chosenCharacter = characterList[currentCharacterIndex];
			if (carousel.move(RightMove))
				isMovingRight = false;
	}
	carousel.update(delta);
}

void CCharacterSelection::STEDraw(float delta)
{
	data->window.clear(sf::Color(174, 177, 184));
	data->window.draw(carousel);
	data->window.display();
}


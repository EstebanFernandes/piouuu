#include "CCharacterSelection.h"
#include "CTestGame.h"
#include "CParserCSV.h"
#include <typeinfo>

CCharacterSelection::CCharacterSelection(GameDataRef _data) 
{
	data = _data;
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

		//ICI, mettre les miscs identifiés dans la liste
		if (charactersInfo[i][10] != "") {

			int startIndex = 0, endIndex = 0;

			for (int j = 0; j <= charactersInfo[i][10].size(); j++) {

				// If we reached the end of the word or the end of the input.
				if (charactersInfo[i][10][j] == '/' || j == (charactersInfo[i][10].size())) {
					endIndex = j;
					std::string temp;
					temp.append(charactersInfo[i][10], startIndex, endIndex - startIndex);
					characterList[i-1].specificites.push_back(temp);
					startIndex = endIndex + 1;
				}
			}
		}
		characterList[i - 1].setCharacterStats(maxHealthPointTemp, moveSpeedTemp, canonNumberTemp, damagePerBulletTemp, attackSpeedTemp, bulletSpeedTemp);

	}
}

void CCharacterSelection::STEInit()
{
	int screenwidth = data->assets.sCREEN_WIDTH;
	int screenheight = data->assets.sCREEN_HEIGHT;
	loadCharacters();
	ui.setCharacterSize(12);
	ui.setFillColor(sf::Color::White);
	ui.setFont(data->assets.GetFont("Nouvelle"));
	//temp

	//on a load les personnages donc on va les mettre dans le carousel
	int maxPoint = (int)carousel.ellipse.getPointCount();
	int nbCharacter = (int)characterList.size();

	Title.setFont(data->assets.GetFont("Nouvelle"));
	Title.setCharacterSize(50);
	if (nb != -1)
	{
	Title.setString("Sélection de personnage J"+std::to_string(nb));
	}
	Title.setPosition(
		screenwidth / 2.f - Title.getGlobalBounds().width / 2.f,
		screenheight*0.1f - Title.getGlobalBounds().height / 2.f);
	carousel.setSize(sf::Vector2f(screenwidth * 0.35f, screenwidth * 0.05f));
	carousel.setEllipseVisibility(false);
	for (int i = 0; i < characterList.size(); i++)
	{
		chosenCharacter = characterList[i];
		CCard temp(chosenCharacter.getName(), chosenCharacter.getDescription(), chosenCharacter.getName(), &(data->assets), chosenCharacter.getAnimated());
		temp.setSize(sf::Vector2f(screenwidth / 4.5f, screenheight * 0.5f));
		temp.setOutlineThickNess(10.f);
		carousel.addCard(temp);
	}
	chosenCharacter = characterList[0];
	float xPosition = screenwidth / 2.f - carousel.ellipse.getGlobalBounds().width / 2.f;
	float yPosition = screenheight * 0.20f;
	carousel.setCarouselPosition(sf::Vector2f(xPosition,
		yPosition));
	carousel.updatePos();
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
			else if (event.key.code == sf::Keyboard::U)
			{
				carousel.displayScale();
			}
			else if (event.key.code == sf::Keyboard::Q)
			{
				if (!carousel.isMoving)
					isMovingRight = true;
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				if (!carousel.isMoving)
				{
					LaunchTransi = true;
				}
				break;
		case sf::Event::Closed:
			data->window.close();
			break;
			}
		}
	}
}




void CCharacterSelection::STEUpdate(float delta)
{
	if(LaunchTransi==true)
	{
		currentTransi = CTransition(&(data->assets), HAUT, 2.f);
		if (returnChar == NULL)
			data->machine.AddState(StateRef(new CTestGame(data, chosenCharacter)), true);
		else {
			*returnChar = chosenCharacter;
			data->machine.RemoveState();
			hasChanges = true;
		}
		currentTransi.initTransition();
		data->assets.stopMusique("MenuPrincipal");
	}
	if (isMovingRight)
	{
			currentCharacterIndex = (currentCharacterIndex + 1) % characterList.size();
			chosenCharacter = characterList[currentCharacterIndex];
			if (carousel.move(RightMove))
				isMovingRight = false;
	}
	if (isMovingLeft)
	{
			if (currentCharacterIndex == 0) {
				currentCharacterIndex = (int)characterList.size() - 1;
			}
			else
				currentCharacterIndex = (currentCharacterIndex - 1) % characterList.size();
			chosenCharacter = characterList[currentCharacterIndex];
			if (carousel.move(LeftMove))
				isMovingLeft = false;
	}
	carousel.update(delta);
	float e = carousel.ellipse.getPoint(carousel.ellipse.getPointCount() / 2).y+ carousel.ellipse.getPosition().y;
	std::stringstream ss;
	mousePositionScreen = sf::Mouse::getPosition(data->window);
	ss << "mouse position : \n" << "Window : " << mousePositionScreen.x << " " << mousePositionScreen.y << "\n"
		<< "point le plus bas du carousel : " << e <<std::endl;
	ui.setString(ss.str());
}

void CCharacterSelection::STEDraw(float delta)
{
	data->window.clear(sf::Color(174, 177, 184));
	data->window.draw(carousel);
	data->window.draw(Title);
	data->window.draw(ui);
}


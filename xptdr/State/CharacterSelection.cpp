#include "CharacterSelection.h"
#include "TestGame.h"
#include "../IO/ParserCSV.h"
#include "MainMenuState.h"

bool StateNS::CharacterSelection::animationEffect(float& dt)
{
	if (state == 0)
	{
		bool isInPlace = true;
		
		for (int i = 0; i < carousel.cards.size(); i++)
		{
			if (carousel.cards[i].cardFace->getPosition().x <= carousel.cards[i].finalPos.x)
			{
				carousel.cards[i].move(speedCard , 0.f);
				isInPlace = false;
			}
			else if(carousel.cards[i].cardFace->getPosition().x <= carousel.cards[i].finalPos.x)
			{
				carousel.cards[i].setPosition(carousel.cards[i].finalPos);
				carousel.cards[i].spin(0.f);
			}
			float distanceParcourue = carousel.cards[i].cardFace->getPosition().x;
			float perc = distanceParcourue / carousel.cards[i].finalPos.x;
			carousel.cards[i].degree = 180.f * (1.f - perc);
			carousel.cards[i].spin(carousel.cards[i].degree);
		}
		return isInPlace;
	}
	else if (state == 2)
	{
		float finalPosY = (float)Engine::SCREEN_HEIGHT / 2.f;
		Carousel::cardHandler& selectedCard = carousel.cards[currentCharacterIndex];
		sf::Vector2f basePos = selectedCard.finalPos;
		float totalDistance = basePos.y - finalPosY;
		if (selectedCard.getPosition().y < finalPosY)
		{
			shakeitoff = ShakeSpinningCard(&selectedCard,&time);
			shakeitoff.shake(shakeAngle, 0.5f);
			return true;
		}
		else {
			float distanceParcourue = basePos.y - selectedCard.getPosition().y;
		float perc = distanceParcourue / totalDistance;
		if (perc <= 0.1f)
			perc = perc / 0.1f;
		else if (perc >= 0.9f)
			perc = (1.f - perc) / 0.1f;
		else
			perc = 1.f;
		float angle = 30.f * perc;
		angle = 360.f- angle;
		selectedCard.spinVertically(angle);
		selectedCard.move(0.f, -speedCard/4.f);
		selectedCard.setScale(selectedCard.getScale().x + 0.003f);
		return false;
		}
	}
	else if (state == 3)
	{
		return shakeitoff.update(dt);
	}
	else if (state == 4)
	{
		Carousel::cardHandler& selectedCard = carousel.cards[currentCharacterIndex];
		selectedCard.setScale(selectedCard.getScale().x + 0.03f);
		if(selectedCard.getSize().x>=(float)Engine::SCREEN_WIDTH)
		{
			drawMask = true;
			timec = time;
			return true;
		}
		return false;
	}

	else if (state == 5)
	{
		if (time - timec <= TEMPS_TRANSI)
		{
			drawMask = true;
		Carousel::cardHandler& selectedCard = carousel.cards[currentCharacterIndex];
		selectedCard.setScale(selectedCard.getScale().x + 0.03f);
		float perc = (time - timec) / TEMPS_TRANSI;
		int newIntensity = (int)(255.f * perc);
		//std::cout << "Intensity : " << newIntensity;
		mask.setFillColor(sf::Color(0, 0, 0, newIntensity));
		}
		else {
			mask.setFillColor(sf::Color(0, 0, 0, 255));
			if (returnChar == NULL)
				data->machine.AddState(StateRef(new TestGame(data, chosenCharacter)), true);
			else {
				*returnChar = chosenCharacter;
				data->machine.RemoveState();
				hasChanges = true;
			}
			data->assets.stopMusique("MenuPrincipal");
			return true;
		}
		return false;
	}
}

StateNS::CharacterSelection::CharacterSelection(GameDataRef _data)
{
	data = _data;
	currentCharacterIndex = 0;
}

StateNS::CharacterSelection::~CharacterSelection()
{
	data->assets.deleteSound(selectionSound);
	data->assets.deleteSound(validationSound);
	for (int i = 0; i < carousel.cards.size(); i++)
	{
		carousel.cards[0].freeMemory();
		carousel.cards.erase(carousel.cards.begin());
	}
}

void StateNS::CharacterSelection::loadCharacters()
{
	std::vector<std::vector<std::string>> charactersInfo = IO::retrieveCSVFile("res/data/characters.csv");
	//Nouvelle méthode pour initialiser les stats
	for (int i = 1; i < charactersInfo.size(); i++) {
		characterList.push_back(Character(charactersInfo[i][1], charactersInfo[i][0], charactersInfo[i][2], charactersInfo[i][3] == "animated"));
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
//This suppose that the characters were already loaded
void StateNS::CharacterSelection::loadCarousel()
{
	int nbCharacter = (int)characterList.size();
	sf::Vector2f pos(0,0);
	std::vector<Card> cardStorage;
	int screenwidth = Engine::SCREEN_WIDTH;
	int screenheight = Engine::SCREEN_HEIGHT;
	sf::Vector2f sizeOfCard(255.f, 365.f);
	for (int i = 0; i < nbCharacter; i++)
	{
		chosenCharacter = characterList[i];
		Card temp(chosenCharacter.getName(), chosenCharacter.getDescription(), chosenCharacter.getName(), &(data->assets), chosenCharacter.getAnimated());
		temp.setSize(sizeOfCard);
		pos.x = i * sizeOfCard.x;
		temp.setPosition(pos);
		cardStorage.push_back(temp);
	}
	int minTitleCharSize = InterfaceState::getMinCharSize(cardStorage, 0);
	int minDescCharSize = InterfaceState::getMinCharSize(cardStorage, 1);
	for (int i = 0; i < cardStorage.size(); i++)
	{
		cardStorage.at(i).setTitleCharSize(minTitleCharSize);
		cardStorage.at(i).setDescriptionCharSize(minDescCharSize);
	}
	carousel.addCards(cardStorage);
}

void StateNS::CharacterSelection::STEInit()
{
	mask.setSize(sf::Vector2f(getEcranBound()));
	mask.setFillColor(sf::Color(0, 0, 0, 0));
	data->assets.LoadSFX("slideSelect", "res\\sfx\\selectCharacter.wav");
	data->assets.LoadSFX("validation", "res\\sfx\\selectedCharacter.wav");
	data->assets.addSFX("slideSelect", &selectionSound);
	data->assets.addSFX("validation", &validationSound);
	int screenwidth = Engine::SCREEN_WIDTH;
	int screenheight = Engine::SCREEN_HEIGHT;
	if (screenheight > 1000)
		speedCard =speedCard *2.f;
	loadCharacters();
	//on a load les personnages donc on va les mettre dans le carousel
	carousel.setSize(sf::Vector2f(screenwidth * 0.35f, screenheight * 0.1f));
	carousel.setEllipseVisibility(true);
	carousel.ellipse.setFillColor(sf::Color(0, 0, 0, 100));
	chosenCharacter = characterList[0];
	carousel.setCarouselPosition(sf::Vector2f(screenwidth/2.f, screenheight/2.f));
	carousel.updatePos();
	loadCarousel();
	state = 0;

	Title.setFont(data->assets.GetFont("Nouvelle"));
	Title.setCharacterSize(50);

	Title.setString("Choisissez votre personnage");
	
	Title.setPosition(
		screenwidth / 2.f - Title.getGlobalBounds().width / 2.f,
		screenheight*0.1f - Title.getGlobalBounds().height / 2.f);
	useIMGUI = true;
}

void StateNS::CharacterSelection::STEHandleInput(sf::Event& event)
{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
			{
				if (state == 1) {
					if (event.key.code == inputOfPlayers[0].moveRight)
					{
						if (!carousel.isMoving)
						{
							isMovingLeft = true;
							selectionSound->play();
						}
					}
					else if (event.key.code == inputOfPlayers[0].moveLeft)
					{
						if (!carousel.isMoving)
						{
							isMovingRight = true;
							selectionSound->play();
						}
					}
					else if (event.key.code == inputOfPlayers[0].button1)
					{
						if (!carousel.isMoving)
						{
							state++;
							validationSound->play();
						}

					}
				}
				if (event.key.code == inputOfPlayers[0].button2)
				{
					data->machine.RemoveState();
					break;
				}
				break;
			}
			case sf::Event::Closed:
			{
				data->window.close();
				break;
			}
			}
}




void StateNS::CharacterSelection::STEUpdate(float delta)
{
	updateTime();
	std::string mousePosString = std::to_string(sf::Mouse::getPosition(data->window).x) + " " + std::to_string(sf::Mouse::getPosition(data->window).y);
	UIText.setString(mousePosString);

	background.updateBackground(delta);
	/*if(LaunchTransi==true)
	{
		currentTransi = Transition(&(data->assets), HAUT, TEMPS_TRANSI);
		if (returnChar == NULL)
			data->machine.AddState(StateRef(new TestGame(data, chosenCharacter)), true);
		else {
			*returnChar = chosenCharacter;
			data->machine.RemoveState();
			hasChanges = true;
		}
		currentTransi.initTransition();
		data->assets.stopMusique("MenuPrincipal");
	}*/
	if (state == 1)
	{
		if (isMovingRight)
		{
			carousel.cards[currentCharacterIndex].saveCardState();
				currentCharacterIndex = (currentCharacterIndex + 1) % characterList.size();
				carousel.updateCurrentSelectedCard(currentCharacterIndex);
				chosenCharacter = characterList[currentCharacterIndex];
				if (carousel.move(RightMove))
					isMovingRight = false;
		}
		if (isMovingLeft)
		{
				if (currentCharacterIndex == 0) {
					carousel.cards[currentCharacterIndex].saveCardState();
					currentCharacterIndex = (int)characterList.size() - 1;
					carousel.updateCurrentSelectedCard(currentCharacterIndex);
				}
				else
				{
					carousel.cards[currentCharacterIndex].saveCardState();
					currentCharacterIndex = (currentCharacterIndex - 1) % characterList.size();
					carousel.updateCurrentSelectedCard(currentCharacterIndex);
				}
				chosenCharacter = characterList[currentCharacterIndex];
				if (carousel.move(LeftMove))
					isMovingLeft = false;
		}
	carousel.update(delta);
	}
	else
	{
		if(state!=0)
			carousel.update(delta);
		if (animationEffect(delta))
			state++;
	}

}

void StateNS::CharacterSelection::STEDraw(float delta)
{
	background.renderBackground(data->window);
	data->window.draw(Title);
	data->window.draw(carousel);
	if (drawMask)
		data->window.draw(mask);
}


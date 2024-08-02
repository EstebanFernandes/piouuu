#include "CharacterSelectionMultiState.h"
#include"MainMenuState.h"
#include "../IO/ParserCSV.h"
#include"../utilities.h"
#include<math.h>
#include"../Engine/Transition.h"

StateNS::CharacterSelectionMultiState::CharacterSelectionMultiState(GameDataRef data_)
{
	data = data_;
	pointerToCharacters = NULL;
}

void StateNS::CharacterSelectionMultiState::resizeText(sf::FloatRect zone,sf::Text& textToResize, unsigned int charSize, bool divided)
{
	while (
		textToResize.getGlobalBounds().width >= zone.width * 0.95f &&
		textToResize.getCharacterSize() >= charSize)
	{
		textToResize.setCharacterSize(textToResize.getCharacterSize() - 1);
	}
	if (divided)
	{
		int dividedIn = 1;
		std::string basicString = textToResize.getString();
		while (textToResize.getGlobalBounds().width >= zone.width * 0.95f)
		{
			dividedIn++;
			std::string temp = basicString;
			for (int i = 1; i < dividedIn; i++)
			{
				int R = (int)(temp.size() / (float)(dividedIn)) * i;
				for (int j = R; j < temp.size(); j++)
				{
					if (temp[j] == ' ')
					{
						temp.insert(j, "\n");
						textToResize.setString(temp);
						break;
					}
				}
			}
		}
	}
}

StateNS::CharacterSelectionMultiState::CharacterSelectionMultiState(GameDataRef data_, std::vector<Character>* pointerToVectCharact)
	:CharacterSelectionMultiState(data_)
{
	pointerToCharacters = pointerToVectCharact;
}

void StateNS::CharacterSelectionMultiState::updateArrow(int index)
{
	if (players[index].degree >= 360.f)
		players[index].degree = -0.05f;
	players[index].degree += 0.05f;
players[index].spinArrow->spin(players[index].degree);
	float speed = 0.02f;
	sf::Sprite& sprite = players[index].arrowSprite;
	int indexAvion = players[index].index;
	sf::Sprite& spriteAvion = avions[indexAvion].spriteAvion;
	if (players[index].sens == true)
	{
		players[index].trueAvionPlayerNumber.move(0.f, -speed);
		players[index].spinArrow->move(0.f, -speed);
		sprite.move(0.f, -speed);
		if(sprite.getPosition().y<=minArrow)
			players[index].sens = false;
	}
	else
	{
		players[index].trueAvionPlayerNumber.move(0.f, speed);
		sprite.move(0.f, speed);
		players[index].spinArrow->move(0.f, speed);
		if (sprite.getPosition().y >= maxArrow)
			players[index].sens = true;
	}
}

void StateNS::CharacterSelectionMultiState::STEInit()
{
	data->assets.LoadSFX("slideSelect", "res\\sfx\\selectCharacter.wav");
	data->assets.LoadSFX("validation", "res\\sfx\\selectedCharacter.wav");
	data->assets.addSFX("slideSelect", &selectionSound);
	data->assets.addSFX("validation", &validationSound);
	selectionSound;
	validationSound;
	float width = (float)Engine::SCREEN_WIDTH;
	float height = (float)Engine::SCREEN_HEIGHT;
	Titre.setFont(data->assets.GetFont("Nouvelle"));
	Titre.setString("Sélection des personnages");
	Titre.setFillColor(sf::Color::White);
	Titre.setCharacterSize(40);
	Titre.setPosition((width - Titre.getGlobalBounds().width) / 2.f, height * 0.1f);
	Titre.setOutlineThickness(2.f);

	time = 0.f;
	loadCharacters();
	setAvionPosition();
	fondMiTransparent.setSize(sf::Vector2f(width, height / 2));
	fondMiTransparent.setFillColor(sf::Color(0, 0, 0, 120));
	fondMiTransparent.setPosition(sf::Vector2f(0.f, height / 2));
	deuxiemefond.setFillColor(sf::Color(64, 62, 62,150));
	//deuxiemefond.setFillColor(sf::Color(0, 0, 0, 240));
	 
	sf::FloatRect zoneJouer(0.f, height / 2.f, width / 2.f, height *0.3f);
	for (int i = 0; i < 2; i++)
	{
		joueur curJoueur;
		curJoueur.curInput = &inputOfPlayers[i];
	players.push_back(curJoueur);
	}

	players[0].zone = zoneJouer;
	zoneJouer.left += zoneJouer.width;
	players[1].zone = zoneJouer;
	data->assets.LoadTexture("arrowDown", "res/img/arrowDown.png");
	for(int i=0;i<2;i++)
	{
		players[i].arrowSprite.setTexture(data->assets.GetTexture("arrowDown"));
		players[i].arrowSprite.setOrigin(
			players[i].arrowSprite.getLocalBounds().width / 2.f,
			players[i].arrowSprite.getLocalBounds().height);
		players[i].arrowSprite.setScale(0.3f, 0.3f);
		initTexts(players[i], i);
	}
	float arrowHeight = players[0].arrowSprite.getGlobalBounds().height;
	maxArrow = avions[0].spriteAvion.getGlobalBounds().top - 0.5f * arrowHeight;
	minArrow = avions[0].spriteAvion.getGlobalBounds().top - arrowHeight;
	for (int i = 0; i < 2; i++)
	{
		players[i].arrowSprite.setPosition(
			avions[players[i].index].spriteAvion.getPosition().x + avions[players[i].index].spriteAvion.getGlobalBounds().width / 2.f,
			minArrow);
		players[i].spinArrow = new sw::SpinningCard(players[i].arrowSprite);
	}
	containChanges = true;
	STEUpdate(0.0003f);
	deuxiemefond.setPosition(0.f, +players[0].trueAvionPlayerNumber.getGlobalBounds().top-5.f);
	deuxiemefond.setSize(sf::Vector2f(width, 
		height/2.f -deuxiemefond.getPosition().y+ players[0].zone.height));
	returnTexte.setFont(data->assets.GetFont("Nouvelle"));
	returnTexte.setString("Retour vers \nle menu principal");
	returnTexte.setCharacterSize(20);
	returnTexte.setPosition(width * 0.05f, height * 0.05f);
	retourBar.setSize(returnTexte.getGlobalBounds().getSize());
	retourBar.setPosition(returnTexte.getGlobalBounds().left, returnTexte.getGlobalBounds().top);
	retourBar.setFillColor(sf::Color::Black);
	retourBar.setOutlineThickness(2.f);
	retourBar.setOutlineColor(sf::Color::Black);
}

void StateNS::CharacterSelectionMultiState::loadCharacters()
{//J'ai copié collé la méthode de CharacterSelection en adaptant
	std::vector<std::vector<std::string>> charactersInfo = IO::retrieveCSVFile("res/data/characters.csv");

	//Nouvelle méthode pour initialiser lefs stats
	for (int i = 1; i < charactersInfo.size(); i++) {
		avion tempAvion;
		tempAvion.characterAvion = Character(charactersInfo[i][1], charactersInfo[i][0], charactersInfo[i][2], charactersInfo[i][3] == "animated");
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
					tempAvion.characterAvion.specificites.push_back(temp);
					startIndex = endIndex + 1;
				}
			}
		}
		//On adapte, ici on doit définir d'autres paramètres en plus
		tempAvion.characterAvion.setCharacterStats(maxHealthPointTemp, moveSpeedTemp, canonNumberTemp, damagePerBulletTemp, attackSpeedTemp, bulletSpeedTemp);
		tempAvion.spriteAvion.setTexture(data->assets.GetTexture(tempAvion.characterAvion.getName()));
		if (i == 1)
			tempAvion.niveau = 3;
		else
			tempAvion.niveau = 0;
		avions.push_back(tempAvion);
		sf::Vector2i frame( 153, 66);
		avions.back().animationAvion = Animation(&tempAvion.spriteAvion, frame, 4, 0.16f);
		avions.back().spriteAvion.setTextureRect(sf::IntRect(sf::Vector2i(0,0),frame));
	}
}

void StateNS::CharacterSelectionMultiState::setAvionPosition()
{
	float totalWidth = 0.0f;

	// Calculer la largeur totale des éléments
	for (const auto& element : avions) {
		totalWidth += element.spriteAvion.getGlobalBounds().width;
	}

	// Calculer la distance entre les éléments
	float distance = (Engine::SCREEN_WIDTH - totalWidth) / (avions.size() + 1 );

	// Position x de départ pour centrer les éléments
	float startX = distance; // Ajuster la position de départ pour inclure la distance entre le premier élément et le bord de la fenêtre

	// Position y des éléments (centrés verticalement)
	float y = (Engine::SCREEN_HEIGHT - avions[0].spriteAvion.getGlobalBounds().height) *0.35f;

	// Position x pour chaque élément
	float x = startX;

	// Parcourir la liste des éléments et les placer sur la fenêtre
	for (auto& element : avions) {
		// Définir la position de l'élément
		element.spriteAvion.setPosition(x, y);

		// Mettre à jour la position x pour le prochain élément
		x += element.spriteAvion.getGlobalBounds().width + distance;
	}
}

void StateNS::CharacterSelectionMultiState::updateAvions()
{
	std::for_each(avions.begin(), avions.end(), [](avion& n) { n.niveau = 0;
	n.spriteAvion.setScale(1.f, 1.f); });
	for (int i = 0; i < 2; i++)
	{
		avions[players[i].index].niveau += (i + 1);
		avions[players[i].index].spriteAvion.setScale(1.2f, 1.2f);
		updateTexts(i);
	}
}

void StateNS::CharacterSelectionMultiState::initTexts(joueur& curJoueur, int index)
{
	sf::FloatRect& zone = curJoueur.zone;
	sf::Vector2f padding(5.f, 5.f);
	sf::Text sampleText;
	sampleText.setFont(data->assets.GetFont("Nouvelle"));
	sampleText.setString("J" + std::to_string(index + 1));
	curJoueur.trueAvionPlayerNumber = sampleText;
	curJoueur.trueAvionPlayerNumber.setCharacterSize(20);
	sampleText.setPosition(zone.getPosition() + padding);
	curJoueur.avionplayerNumber = sampleText;
	curJoueur.avionDescription = sampleText;
	curJoueur.avionName = sampleText;
}

void StateNS::CharacterSelectionMultiState::updateTexts(int index)
{
	sf::FloatRect& zone = players[index].zone;
	sf::Vector2f padding(5.f, 5.f);
	sf::Text& name = players[index].avionName;
	sf::Text& description = players[index].avionDescription;
	name.setString(avions[players[index].index].characterAvion.getName());
	float nameWidth = name.getGlobalBounds().width;
	name.setPosition(
		zone.left +( zone.width - nameWidth) / 2.f,
		zone.top +padding.y+ players[index].avionName.getGlobalBounds().height);
	
	description.setString(avions[players[index].index].characterAvion.getDescription());
	description.setPosition(zone.left + padding.x ,
		zone.top + zone.height*0.7f + description.getGlobalBounds().height/2.f);
	resizeText(zone, description, 20);
	sf::Sprite& arrowSprite = players[index].arrowSprite;
	if (index == 1&& avions[players[index].index].niveau>2)
	{//Les deux sont sur le même
		players[0].arrowSprite.setPosition(
			avions[players[index].index].spriteAvion.getPosition().x + avions[players[index].index].spriteAvion.getGlobalBounds().width / 2.f- players[0].arrowSprite.getGlobalBounds().width/2.f-2.f,
			players[0].arrowSprite.getPosition().y);
		players[0].trueAvionPlayerNumber.setPosition(
			players[0].arrowSprite.getGlobalBounds().left
			, players[0].arrowSprite.getGlobalBounds().top - 10.f - players[0].trueAvionPlayerNumber.getGlobalBounds().height);
		arrowSprite.setPosition(
			avions[players[index].index].spriteAvion.getPosition().x + avions[players[index].index].spriteAvion.getGlobalBounds().width / 2.f+arrowSprite.getGlobalBounds().width / 2.f + 2.f,
			arrowSprite.getPosition().y);
		players[0].spinArrow->setPosition(players[0].arrowSprite.getPosition());
		players[index].spinArrow->setPosition(arrowSprite.getPosition());

	}
	else
	arrowSprite.setPosition(
		avions[players[index].index].spriteAvion.getPosition().x + avions[players[index].index].spriteAvion.getGlobalBounds().width / 2.f,
		 arrowSprite.getPosition().y);
	players[index].spinArrow->setPosition(arrowSprite.getPosition());
	players[index].trueAvionPlayerNumber.setPosition(
		arrowSprite.getGlobalBounds().left
		, arrowSprite.getGlobalBounds().top - 10.f - players[index].trueAvionPlayerNumber.getGlobalBounds().height);
	players[index].preViewSprite = avions[players[index].index].spriteAvion;
	players[index].preViewSprite.setPosition(
		players[index].zone.left+players[index].zone.width / 2.f- players[index].preViewSprite.getGlobalBounds().width/2.f,
		players[index].zone.top + players[index].zone.height / 2.f - players[index].preViewSprite.getGlobalBounds().height / 2.f);
	if(!players[index].isValid)
		players[index].preViewSprite.setColor(sf::Color(0, 0, 0, 122));
}

void StateNS::CharacterSelectionMultiState::STEHandleInput(sf::Event& event)
{
	for (int i = 0; i < 2; i++)
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			if (players[i].isValid == false)
			{
				if (event.key.code == players[i].curInput->moveLeft)
				{
					selectionSound->play();
					if (players[i].index == 0)
						players[i].index = (int)avions.size() - 1;
					else
						players[i].index--;
					containChanges = true;
				}
				if (event.key.code == players[i].curInput->moveRight)
				{
					selectionSound->play();
					if (players[i].index == avions.size() - 1)
						players[i].index = 0;
					else
						players[i].index++;
					containChanges = true;
				}
				if (event.key.code == players[i].curInput->button1)
				{
					players[i].isValid = true;
					validationSound->play();
					players[i].preViewSprite.setColor(sf::Color::White);
				}
				if (event.key.code == players[i].curInput->button2)
				{
					if (!isPressingReturn)//Première fois que l'on appuie
						returnClock.restart();
					isPressingReturn = true;
				}
			}
			else if (event.key.code == players[i].curInput->button2)
			{
				players[i].isValid = false;
				containChanges = true;

			}
				
		break;

		case sf::Event::KeyReleased:
			if (players[i].isValid == false && event.key.code == players[i].curInput->button2)
			{
				isPressingReturn = false;
			}
			break;
		case sf::Event::Closed:
			data->window.close();
			break;
		}
	}
}

void StateNS::CharacterSelectionMultiState::STEUpdate(float dt)
{
	updateTime();
	background.updateBackground(dt);
	if (containChanges)
	{
		updateAvions();
		containChanges = false;
	}
	for (auto& element : avions)
	{
		if(element.niveau!=0)
		{
			if (element.MDRRcafonctionne++ == 1)
				element.animationAvion.setSprite(&element.spriteAvion);
			element.animationAvion.updateAnimation();
		}
	}
	for (int i = 0; i < 2; i++)
	{
		if(players[i].isValid==false)
			updateArrow(i);

	}
	if (players[0].isValid && players[1].isValid)
	{
		pointerToCharacters->at(0) = avions[players[0].index].characterAvion;
		pointerToCharacters->at(1) = avions[players[1].index].characterAvion;
		data->machine.RemoveState();
		hasChanges = true;
		currentTransi = Transition(&(data->assets), Engine::SENS_TRANSITION::DROITE, TEMPS_TRANSI);
		currentTransi.initTransition();
	}
	if(isPressingReturn&& returnClock.getElapsedTime().asSeconds() >= 2.5f)
		data->machine.RemoveState();
	else if (isPressingReturn)
	{
		retourBar.setFillColor(sf::Color(0, 0, 0, (int)(returnClock.getElapsedTime().asSeconds() * 255.f / 2.5f)));
		retourBar.setOutlineColor(retourBar.getFillColor());
	}
}

void StateNS::CharacterSelectionMultiState::STEDraw(float interpolation)
{
	background.renderBackground(data->window);
	drawElements();
}

void StateNS::CharacterSelectionMultiState::drawElements(bool onlyAvion)
{
	data->window.draw(deuxiemefond);
	data->window.draw(Titre);
	if (isPressingReturn)
	{
		data->window.draw(retourBar);
		data->window.draw(returnTexte);
	}
		for (auto& element : avions)
		{
			
			data->window.draw(element.spriteAvion);
		}
		//data->window.draw(fondMiTransparent);

		for (int i = 0; i < 2; i++)
		{
			data->window.draw(players[i].avionDescription);
			data->window.draw(players[i].avionplayerNumber);
			data->window.draw(players[i].avionName);
			if(players[i].isValid==false)
			{
				data->window.draw(*players[i].spinArrow);
				data->window.draw(players[i].trueAvionPlayerNumber);
				data->window.draw(players[i].preViewSprite);
			}
			else
				data->window.draw(players[i].preViewSprite);
		}
}

StateNS::CharacterSelectionMultiState::~CharacterSelectionMultiState()
{
	for (int i = 0; i < 2; i++)
		delete players[i].spinArrow;
}

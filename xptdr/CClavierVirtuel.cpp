#include "CClavierVirtuel.h"

CClavierVirtuel::CClavierVirtuel(GameDataRef _data, float scoreParam, int rankParam, std::string *playerNameParam, int nbJoueur) : data(_data)
{
	score = scoreParam;
	rank = rankParam;
	playerName = playerNameParam;
	this->nbJoueur = nbJoueur;
	for(int i=0;i<nbJoueur;i++)
	{
		joueur tempJoueur;
		tempJoueur.input = &inputOfPlayers[i];
		players.push_back(tempJoueur);
	}
}

void CClavierVirtuel::keyboardInit()
{

}

void CClavierVirtuel::STEInit()
{
	float width = (float)data->assets.sCREEN_WIDTH;
	float height = (float)data->assets.sCREEN_HEIGHT;
	//Le tableau correspond au lettre du clavier, 
					  //1234567890-effacer
	keyboard.push_back("1234567890-&");
	//azertyuiop,Entrer
	keyboard.push_back("azertyuiop'!à");
	//qsdfghjlm;ok
	keyboard.push_back("qsdfghjklm;²");
	//wxcvbn,.!?:ok
	keyboard.push_back("wxcvbn,.!?:²");
	//  MAJ  décaler gauche décaler droite barre espace ANNULER 
	keyboard.push_back("  ^<>    è");
	data->assets.LoadTexture("keyboardBlack", "res\\img\\keyboard_black.png");
	data->assets.LoadTexture("keyboardWhite", "res\\img\\keyboard_white.png");
	data->assets.LoadTexture("keyboardLetter", "res\\img\\keyboard_black2.png");
	//mouseSelectionRectangle = sf::FloatRect(0.f, 0.f, 40.f, 40.f);//avec la scale actuelle (3) c'est 40 une case
	keyboardBlackSprite.setTexture(data->assets.GetTexture("keyboardBlack"));
	keyboardBlackSprite.setScale(4.f, 4.f);
	keyboardBlackSprite.setPosition((width / 2.f) - keyboardBlackSprite.getGlobalBounds().width / 2.f, height * 0.4f);
	for (int i = 0; i < nbJoueur; i++)
	{
		sf::Sprite temp;
		sf::Sprite keyboardLetterSprite;
		temp.setTexture(data->assets.GetTexture("keyboardWhite"));
		temp.setScale(keyboardBlackSprite.getScale());
		temp.setPosition(keyboardBlackSprite.getPosition());
		if (nbJoueur == 2)
		{
			if (i == 0)
				temp.setColor(sf::Color(3, 140, 252));
			else
				temp.setColor(sf::Color(52, 199, 62));
		}
		players[i].keyboardPlayer = temp;
		if (nbJoueur == 1)
			keyboardLetterSprite.setColor(sf::Color::Black);
		keyboardLetterSprite.setTexture(data->assets.GetTexture("keyboardLetter"));
		keyboardLetterSprite.setScale(keyboardBlackSprite.getScale());
		keyboardLetterSprite.setPosition(keyboardBlackSprite.getPosition());
		players[i].keyboardLetterSprite= keyboardLetterSprite;
	}
	capslocksprite.setTexture(data->assets.GetTexture("keyboardWhite"));
	capslocksprite.setScale(keyboardBlackSprite.getScale());
	capslocksprite.setPosition(keyboardBlackSprite.getPosition());
	//capslocksprite.setPosition(sf::Vector2f(448.f,544.f));
	capslocksprite.setPosition(capslocksprite.getPosition().x + (32.f * keyboardBlackSprite.getScale().x), capslocksprite.getPosition().y + (64.f * keyboardBlackSprite.getScale().y));
	capslocksprite.setTextureRect(sf::IntRect(32, 64, 14, 13));

	ui.setCharacterSize(12);
	ui.setFillColor(sf::Color::White);
	ui.setFont(data->assets.GetFont("Lato"));

	CapsLock.setFillColor(sf::Color::Black);
	CapsLock.setPosition(keyboardBlackSprite.getPosition().x + 172, keyboardBlackSprite.getPosition().y + 264);
	CapsLock.setSize(sf::Vector2f(4.f, 4.f));


		sf::RectangleShape ah;
		ah.setFillColor(sf::Color(255, 255, 255, 200));
	if (nbJoueur == 2)
	{
		ah.setSize(sf::Vector2f(keyboardBlackSprite.getGlobalBounds().width/3.f , 50.f));
		ah.setPosition(
			keyboardBlackSprite.getPosition().x ,
			(float)data->assets.sCREEN_HEIGHT * 0.3f);
		players[0].fondBlanc=  ah;
		ah.setPosition(keyboardBlackSprite.getPosition().x+keyboardBlackSprite.getGlobalBounds().width*2.f/3.f,
			(float)data->assets.sCREEN_HEIGHT * 0.3f);
		players[1].fondBlanc = ah;
		midText.setPosition(keyboardBlackSprite.getPosition().x + keyboardBlackSprite.getGlobalBounds().width/2.f, ah.getPosition().y * 1.03f);
		midText.setCharacterSize(25);
		midText.setFillColor(sf::Color::White);
		midText.setFont(data->assets.GetFont("Nouvelle"));
		midText.setString("&");
	}
	else{
		ah.setSize(sf::Vector2f(keyboardBlackSprite.getGlobalBounds().width * 0.5f, 50.f));
		ah.setPosition(keyboardBlackSprite.getPosition().x + ((keyboardBlackSprite.getGlobalBounds().width - ah.getLocalBounds().width) * 0.5f), (float)data->assets.sCREEN_HEIGHT * 0.3f);
		players[0].fondBlanc = ah;
		midText.setPosition(keyboardBlackSprite.getPosition().x + keyboardBlackSprite.getGlobalBounds().width / 2.f, ah.getPosition().y * 1.03f);
		midText.setCharacterSize(25);
		midText.setFillColor(sf::Color::Transparent);
		midText.setFont(data->assets.GetFont("Nouvelle"));
		midText.setString("neuil");
	}
	for (int i = 0; i < nbJoueur; i++)
	{
		joueur& currentPlayer = players[i];
		sf::Text nameText;
		if(i==0)
			utilities::readaptText(nameText, sf::Vector2f(currentPlayer.fondBlanc.getPosition().x * 1.01f, ah.getPosition().y * 1.03f));
		else
			utilities::readaptText(nameText, sf::Vector2f(currentPlayer.fondBlanc.getPosition().x * 1.01f, ah.getPosition().y * 1.03f));
		nameText.setCharacterSize(25);
		nameText.setFillColor(sf::Color::Black);
		nameText.setFont(data->assets.GetFont("Nouvelle"));
		nameText.setString(currentPlayer.name);
		currentPlayer.nameText = nameText;
		nameText.setString("-");
		nameText.setPosition(nameText.getPosition().x,
			ah.getGlobalBounds().top + ah.getGlobalBounds().height * 0.5f);
		currentPlayer.bar = nameText;
	}
	scorePrompts.push_back(sf::Text());
	scorePrompts.push_back(sf::Text());
	scorePrompts.push_back(sf::Text());
	for (int i = 0; i < scorePrompts.size(); i++)
	{
	std::stringstream textToPrompt;
		sf::Text scorePrompt;
		scorePrompt.setFont(data->assets.GetFont("Nouvelle"));
		scorePrompt.setCharacterSize(30);
		scorePrompt.setFillColor(sf::Color::White);
		switch (i)
		{
		case 0:
			if(nbJoueur==1)
			{
				if (rank == 1) {
					textToPrompt << "Tu deviens la nouvelle légende de PIOU avec ce magnifique score de " << score ;
				}else
					textToPrompt << "Tu termines avec ce magnifique score de " << score;
			}
			else {//2 joueurs
				if (rank == 1)
					textToPrompt << "Félicitation vous avez atteint le rang de légendes vivantes avec ce score de " << score;
				else
					textToPrompt << "Vous terminez avec ce magnifique score de " << score;
			}
			break;
		case 1:
			if (nbJoueur == 1)
			{
				if (rank == 1) 
					textToPrompt << ", et finit donc premier du classement";
				else
					textToPrompt << "tu finis donc " << rank<<"ème du classement";
			}
			else {
				if (rank == 1)
					textToPrompt << ", vous finissez donc premier du classement";
				else
					textToPrompt << "et finissez donc " << rank << "ème du classement, écrivez vos noms";
			}
			break;
		case 2:
			if (nbJoueur == 1)
				textToPrompt << "écris ton nom afin qu'il rentre dans la légende";
			else
				textToPrompt << "afin qu'ils restent gravés dans la roche";
			break;
		}
		scorePrompt.setString(textToPrompt.str());
		if(i!=0)
		scorePrompt.setPosition(
			(width-scorePrompt.getGlobalBounds().width)/2.f,
			scorePrompts[i - 1].getGlobalBounds().top + scorePrompts[i - 1].getGlobalBounds().height + 5.f);
		else
			scorePrompt.setPosition(
				(width - scorePrompt.getGlobalBounds().width) / 2.f,
				height * 0.05f );
		scorePrompts[i] = scorePrompt;
	}

}

void CClavierVirtuel::STEHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
			data->window.close();
		if (event.type == sf::Event::KeyPressed)
		{
			for (int i = 0; i < nbJoueur; i++)
			{
				int& x = players[i].playerSelection.x;
				int& y = players[i].playerSelection.y;
				inputPlayer* curInput = players[i].input;
				if (event.key.code == curInput->moveUp)
				{
					if (y != 0)
						y -= 1;
				}
				if (event.key.code == curInput->moveLeft)
				{
					if (y == 4 && x == 2)
						break;
					if (y == 4 && (x >= 5 && x <= 8))
						x = 4;
					else if (x != 0)
						x -= 1;
				}
				if (event.key.code == curInput->moveDown)
				{
					if (y == 3 && (x < 2 || x > 9))
						break;
					if (y != 4)
						y += 1;
				}
				if (event.key.code == curInput->moveRight)
				{
					if (y == 4 && x == 9)
						break;
					if (x != 11)
						x += 1;
				}
				if (event.key.code == curInput->moveUp)
				{
					players[i].isPressed = true;
				}
			}
		}
	}
}

void CClavierVirtuel::STEUpdate(float delta)
{
	updateTime();
	background.updateCBackground(delta);
	sf::IntRect temp;
	//On check les positions du clavier et on remet s'il faut
	bool globalvalid = true;
	for (int i = 0; i < nbJoueur; i++)
	{
		joueur& currentPlayer = players[i];
		if (players[i].playerSelection.x != -1 && players[i].playerSelection.y != -1)
		{
			int& x = currentPlayer.playerSelection.x;
			int& y = currentPlayer.playerSelection.y;
			if (x == 11 && (y == 2 || y == 3))
			{
				y = 2;
				temp = sf::IntRect(14 * x + 2 * x, 13 * y + 3 * y, 14, 26 + 12);
				currentPlayer.tilePositionsKeyboard.x = keyboardBlackSprite.getPosition().x + 56 * x + 8 * x;
				players[i].tilePositionsKeyboard.y = keyboardBlackSprite.getPosition().y + 52 * y + 12 * y;
			}
			else if (y == 4 && (x >= 5 && x <= 8))
			{
				x = 5;
				temp = sf::IntRect(14 * x + 2 * x, 13 * y + 3 * y, (14 * 4) + 2 * 3, 13);
				currentPlayer.tilePositionsKeyboard.x = keyboardBlackSprite.getPosition().x + 56 * x + 8 * x;
				currentPlayer.tilePositionsKeyboard.y = keyboardBlackSprite.getPosition().y + 52 * y + 12 * y;
				x = 8;
			}
			else {
				currentPlayer.tilePositionsKeyboard.x = keyboardBlackSprite.getPosition().x + 56 * x + 8 * x;
				currentPlayer.tilePositionsKeyboard.y = keyboardBlackSprite.getPosition().y + 52 * y + 12 * y;
				temp = sf::IntRect(14 * x + 2 * x, 13 * y + 3 * y, 14, 13);
			}
			currentPlayer.keyboardPlayer.setPosition(players[i].tilePositionsKeyboard);
			currentPlayer.keyboardPlayer.setTextureRect(temp);
			currentPlayer.keyboardLetterSprite.setPosition(players[i].tilePositionsKeyboard);
			currentPlayer.keyboardLetterSprite.setTextureRect(temp);
		}
		if (currentPlayer.isPressed)
		{
			UpdateText(i);
			setBar(i);
			currentPlayer.isPressed = false;
		}
		if(!currentPlayer.isValid)
		{
			updateBars(i);
			globalvalid = false;
		}
	}
	if (globalvalid)
		data->machine.RemoveState();
}
//Fonction appelée que si l'utilisateur appuie sur une touche
void CClavierVirtuel::UpdateText(int joueur)
{
	int x = players[joueur].playerSelection.x;
	int y = players[joueur].playerSelection.y;
	char letter = keyboard[y][x];
	std::string& name = players[joueur].name;
	unsigned int& stringPosition = players[joueur].stringPosition;
	if (players[joueur].isValid)
		players[joueur].isValid = false; //Permet de faire réapparaitre la bar en dessous
	switch (letter)
	{
	case '&'://Touche effacer
		if (name.size() != 0)
		{
			if (name.size() == stringPosition)
				name = name.substr(0, name.size() - 1);
			else {
				if (stringPosition == 0 && name.size() == 1)
				{
					name = name.substr(0, name.size() - 1);
					stringPosition = 1;
				}
				else
				{
					if (stringPosition == 0)
						stringPosition++;
					else
					{
						std::string name1 = name.substr(0, stringPosition - 1);
						std::string name2 = name.substr(stringPosition);
						name = name1 + name2;
					}
				}
			}
			stringPosition--;
		}
		break;
	case 'è':
		cancel = true;
		break;
	case '²':
		if (name.size() >= numberCharMin) {
			players[joueur].isValid = true;
		}
		else {
			//Signaler que nom trop court
		}
		break;
	case 'à':

		break;
	case '^':
		if (capsInt == RELACHE)
		{
			capsInt = ENFONCE;
			CapsLock.setFillColor(sf::Color::White);
		}
		else if (capsInt == ENFONCE)
		{
			capsInt = LOCK;
		}
		else if (capsInt == LOCK)
		{
			capsInt = RELACHE;
			CapsLock.setFillColor(sf::Color::Black);
		}
		break;
	case '<':
		if (stringPosition != 0)
		{
			stringPosition--;
		}
		break;
	case '>':
		if (stringPosition != name.size())
		{
			stringPosition++;
		}
		break;
	default:
		if (name.size() < numberCharMax) {
			if (capsInt == 1 || capsInt == 2) {
				if (capsInt == 1)
				{
					capsInt = 0;
					CapsLock.setFillColor(sf::Color::Black);
				}
				if (letter >= 'a')
				{
					{
						if (letter <= 'z')
							letter = letter + ('A' - 'a');
					}
				}
			}
			if (name.size() == stringPosition)
				name = name + letter;
			else {
				std::string name1 = name.substr(0, stringPosition);
				std::string name2 = name.substr(stringPosition);
				name = name1 + letter + name2;
			}
			stringPosition ++;
			if (players[joueur].name.size() == numberCharMax)
				players[joueur].dontshowBar = true;
			else
				players[joueur].dontshowBar = false;
		}
		else {
			//Ici, signaler que le nom est trop long
		}
	}
	players[joueur].nameText.setString(name);
	std::string totalName="";
	for (int i = 0; i < nbJoueur; i++)
	{
		if (i == 1)
		{
			totalName += "&";
		}
		totalName += players[i].name;
	}
	*playerName = totalName;
}



void CClavierVirtuel::STEDraw(float delta)
{
	sf::RenderWindow& r = data->window;
	background.renderBackground(r);
		r.draw(midText);
	r.draw(keyboardBlackSprite); 
	for (int i = 0; i < nbJoueur; i++)
	{
		joueur& currentPlayer = players[i];
		r.draw(currentPlayer.fondBlanc);
		r.draw(currentPlayer.nameText);
		bool merde = false;
			if (!currentPlayer.isValid)
				merde = true;
			if (currentPlayer.dontshowBar == true)
				merde = false;
		if(merde)
			r.draw(currentPlayer.bar);
		r.draw(currentPlayer.keyboardPlayer);
		r.draw(currentPlayer.keyboardLetterSprite);
	}
	if (capsInt == 2)r.draw(capslocksprite);
	r.draw(CapsLock);
	r.draw(ui);
	for (int i = 0;i < scorePrompts.size(); i++)
	{
		r.draw(scorePrompts[i]);
	}
}

void CClavierVirtuel::updateBars(int index)
{
		joueur& currentPlayer = players[index];
		if (currentPlayer.bar.getGlobalBounds().top <=
			midText.getGlobalBounds().top + midText.getGlobalBounds().height * 1.05f)
			currentPlayer.yDirection = 1.f;
		else if (currentPlayer.bar.getGlobalBounds().top >=
			currentPlayer.fondBlanc.getGlobalBounds().top + currentPlayer.fondBlanc.getGlobalBounds().height * 0.90f)
			currentPlayer.yDirection = -1.f;
		currentPlayer.bar.move(0.f, currentPlayer.yDirection *0.007f);

}


void CClavierVirtuel::setBar(int index)
{
	if(players[index].stringPosition== players[index].name.size())
	{
		players[index].bar.setPosition(players[index].nameText.getPosition().x + players[index].nameText.getGlobalBounds().width + 3.f,
			players[index].bar.getPosition().y);
	}
	else {
		sf::Text temp = players[index].nameText;
		temp.setString(temp.getString().substring(0, players[index].stringPosition));
		players[index].bar.setPosition(temp.getPosition().x + temp.getGlobalBounds().width + 3.f,
			players[index].bar.getPosition().y);
	}
}
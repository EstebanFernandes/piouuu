#include "CClavierVirtuel.h"

CClavierVirtuel::CClavierVirtuel(GameDataRef _data, float scoreParam, int rankParam, std::string *playerNameParam, int nbJoueur) : data(_data)
{
	score = scoreParam;
	rank = rankParam;
	playerName = playerNameParam;
	this->nbJoueur = nbJoueur;
	for(int i=0;i<nbJoueur;i++)
	{
		tilePositionsKeyboard.push_back(sf::Vector2f());
		playerSelection.push_back(sf::Vector2i(0, 0));
		if (i == 0)
			keysPlayer.push_back(keys());
		else
		{
			keys keysecondPlayer;
			keysecondPlayer.up = sf::Keyboard::Up;
			keysecondPlayer.down= sf::Keyboard::Down;
			keysecondPlayer.right = sf::Keyboard::Right;
			keysecondPlayer.left  = sf::Keyboard::Left;
			keysecondPlayer.press = sf::Keyboard::U;
			keysPlayer.push_back(keysecondPlayer);
		}
		stringPositions.push_back(0);
		OUAIS.push_back(false);
		names.push_back(std::string());
		yDirection.push_back(1.f);
	}
}

void CClavierVirtuel::keyboardInit()
{

}

void CClavierVirtuel::STEInit()
{
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
	keyboardBlackSprite.setPosition(((float)data->assets.sCREEN_WIDTH / 2.f) - keyboardBlackSprite.getGlobalBounds().width / 2.f, (float)data->assets.sCREEN_HEIGHT * 0.4f);
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
		keyboardPlayer.push_back(temp);
		keyboardLetterSprite.setTexture(data->assets.GetTexture("keyboardLetter"));
		keyboardLetterSprite.setScale(keyboardBlackSprite.getScale());
		keyboardLetterSprite.setPosition(keyboardBlackSprite.getPosition());
		keyboardLetterSprites.push_back(keyboardLetterSprite);
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
	if (nbJoueur == 2)
	{
		ah.setSize(sf::Vector2f(keyboardBlackSprite.getGlobalBounds().width/3.f , 50.f));
		ah.setPosition(
			keyboardBlackSprite.getPosition().x ,
			(float)data->assets.sCREEN_HEIGHT * 0.3f);
		ahouais.push_back(ah);
		ah.setPosition(keyboardBlackSprite.getPosition().x+keyboardBlackSprite.getGlobalBounds().width*2.f/3.f,
			(float)data->assets.sCREEN_HEIGHT * 0.3f);
		ahouais.push_back(ah);
		midText.setPosition(keyboardBlackSprite.getPosition().x + keyboardBlackSprite.getGlobalBounds().width/2.f, ah.getPosition().y * 1.03f);
		midText.setCharacterSize(25);
		midText.setFillColor(sf::Color::Black);
		midText.setFont(data->assets.GetFont("Nouvelle"));
		midText.setString("&");
	}
	else{
		ah.setSize(sf::Vector2f(keyboardBlackSprite.getGlobalBounds().width * 0.5f, 50.f));
		ah.setPosition(keyboardBlackSprite.getPosition().x + ((keyboardBlackSprite.getGlobalBounds().width - ah.getLocalBounds().width) * 0.5f), (float)data->assets.sCREEN_HEIGHT * 0.3f);
		ahouais.push_back(ah);
	}
	for (int i = 0; i < nbJoueur; i++)
	{
		sf::Text nameText;
		if(i==0)
			utilities::readaptText(nameText, sf::Vector2f(ahouais[i].getPosition().x * 1.01f, ah.getPosition().y * 1.03f));
		else
			utilities::readaptText(nameText, sf::Vector2f(ahouais[i].getPosition().x * 1.01f, ah.getPosition().y * 1.03f));
		nameText.setCharacterSize(25);
		nameText.setFillColor(sf::Color::Black);
		nameText.setFont(data->assets.GetFont("Nouvelle"));
		nameText.setString(names[i]);
		nameTexts.push_back(nameText);
		nameText.setPosition(nameText.getPosition().x,
			ah.getPosition().y + ah.getGlobalBounds().height*0.95f);
		nameText.setString("-");
		bars.push_back(nameText);
	}
	std::stringstream textToPrompt;
	
	if(nbJoueur==1){
		if (rank == 1) {
			textToPrompt << "Tu deviens la nouvelle légende de PIOU avec ce \nmagnifique score de " << score << ",tu finis premier,\nécris ton nom qui deviendra légendaire\n(jusqu'à ce que ton score soit battu)";
		}
		else {
			textToPrompt << "Bien joué, ton score est de " << score << ", tu finis " << rank << "ème, écris ton nom\n pour qu'il reste gravé à jamais dans l'histoire de PIOU";
		}
	}
	else {
		if (rank == 1) {
			textToPrompt << "Vous devenez les légendes de ce foutu game avec ce \nmagnifique score de " << score << ",\n";
		}
		else {
			textToPrompt << "Bien joué, votre score est de " << score << ", vous finissez donc " << rank << "ème\n";
		}
		textToPrompt << "écrivez vos noms pour qu'il reste dans la légende";
	}

	scorePrompt.setFont(data->assets.GetFont("Nouvelle"));
	scorePrompt.setCharacterSize(35);
	scorePrompt.setFillColor(sf::Color::White);
	scorePrompt.setString(textToPrompt.str());
	scorePrompt.setPosition(keyboardBlackSprite.getPosition().x, 0);


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
				int& x = playerSelection[i].x;
				int& y = playerSelection[i].y;
				if (event.key.code == keysPlayer[i].up)
				{
					if (y != 0)
						y -= 1;
				}
				if (event.key.code == keysPlayer[i].left)
				{
					if (y == 4 && x == 2)
						break;
					if (y == 4 && (x >= 5 && x <= 8))
						x = 4;
					else if (x != 0)
						x -= 1;
				}
				if (event.key.code == keysPlayer[i].down)
				{
					if (y == 3 && (x < 2 || x > 9))
						break;
					if (y != 4)
						y += 1;
				}
				if (event.key.code == keysPlayer[i].right)
				{
					if (y == 4 && x == 9)
						break;
					if (x != 11)
						x += 1;
				}
				if (event.key.code == keysPlayer[i].press)
				{
					OUAIS[i] = true;
				}
			}
		}
	}
}

void CClavierVirtuel::STEUpdate(float delta)
{
	sf::IntRect temp;
	//On check les positions du clavier et on remet s'il faut
	for (int i = 0; i < nbJoueur; i++)
	{
		if (playerSelection[i].x != -1 && playerSelection[i].y != -1)
		{
			int& x = playerSelection[i].x;
			int& y = playerSelection[i].y;
			if (x == 11 && (y == 2 || y == 3))
			{
				y = 2;
				temp = sf::IntRect(14 * x + 2 * x, 13 * y + 3 * y, 14, 26 + 12);
				tilePositionsKeyboard[i].x = keyboardBlackSprite.getPosition().x + 56 * x + 8 * x;
				tilePositionsKeyboard[i].y = keyboardBlackSprite.getPosition().y + 52 * y + 12 * y;
			}
			else if (y == 4 && (x >= 5 && x <= 8))
			{
				x = 5;
				temp = sf::IntRect(14 * x + 2 * x, 13 * y + 3 * y, (14 * 4) + 2 * 3, 13);
				tilePositionsKeyboard[i].x = keyboardBlackSprite.getPosition().x + 56 * x + 8 * x;
				tilePositionsKeyboard[i].y = keyboardBlackSprite.getPosition().y + 52 * y + 12 * y;
				x = 8;
			}
			else {
				tilePositionsKeyboard[i].x = keyboardBlackSprite.getPosition().x + 56 * x + 8 * x;
				tilePositionsKeyboard[i].y = keyboardBlackSprite.getPosition().y + 52 * y + 12 * y;
				temp = sf::IntRect(14 * x + 2 * x, 13 * y + 3 * y, 14, 13);
			}
			keyboardPlayer[i].setPosition(tilePositionsKeyboard[i]);
			keyboardPlayer[i].setTextureRect(temp);
			keyboardLetterSprites[i].setPosition(tilePositionsKeyboard[i]);
			keyboardLetterSprites[i].setTextureRect(temp);
		}
		if (OUAIS[i])
		{
			UpdateText(i);
			bars[i].setPosition(sf::Vector2f(nameTexts[i].getPosition().x + nameTexts[i].getGlobalBounds().width + 3.f, midText.getGlobalBounds().top + midText.getGlobalBounds().height * 1.05f));
			OUAIS[i] = false;
		}
		updateBars();
	}
}
//Fonction appelée que si l'utilisateur appuie sur une touche
void CClavierVirtuel::UpdateText(int joueur)
{
	int x = playerSelection[joueur].x;
	int y = playerSelection[joueur].y;
	char letter = keyboard[y][x];
	std::string& name = names[joueur];
	unsigned int& stringPosition = stringPositions[joueur];
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
			data->machine.RemoveState();
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
			stringPosition--;
		break;
	case '>':
		if (stringPosition != name.size())
			stringPosition++;
		break;
	default:
		if (name.size() <= numberCharMax) {
			if (capsInt == 1 || capsInt == 2) {
				if (capsInt == 1)
				{
					capsInt = 0;
					CapsLock.setFillColor(sf::Color::Black);
				}
				if (letter >= 'a')
				{
					{
						if (letter <= 'z')letter = letter + ('A' - 'a');
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
			stringPosition += 1;
			break;
		}
		else {
			//Ici, signaler que le nom est trop long
		}
	}
	nameTexts[joueur].setString(name);
	std::string totalName="";
	for (int i = 0; i < nbJoueur; i++)
	{
		if (i == 1)
		{
			totalName += "&";
		}
		totalName += names[i];
	}
	*playerName = totalName;
}



void CClavierVirtuel::STEDraw(float delta)
{
	sf::RenderWindow& r = data->window;
	r.clear(sf::Color(191, 165, 117, 1));
	for (int i = 0; i < nbJoueur; i++)
	{
	r.draw(ahouais[i]);
		r.draw(nameTexts[i]);
	}
	for (int i = 0; i < bars.size(); i++)
	{
		if(names[i].size()<numberCharMax+1)
			r.draw(bars[i]);
	}
	r.draw(midText);
	r.draw(keyboardBlackSprite); 
	for (int i = 0; i < nbJoueur; i++)
		r.draw(keyboardPlayer[i]);
	for (int i = 0; i < nbJoueur; i++)
		r.draw(keyboardLetterSprites[i]);
	if (capsInt == 2)r.draw(capslocksprite);
	r.draw(CapsLock);
	r.draw(ui);
	r.draw(scorePrompt);
}

void CClavierVirtuel::updateBars()
{
	for (int i = 0; i < bars.size(); i++)
	{
		if (bars[i].getGlobalBounds().top <=
			midText.getGlobalBounds().top + midText.getGlobalBounds().height * 1.05f)
			yDirection[i] = 1.f;
		else if (bars[i].getGlobalBounds().top >=
			ahouais[i].getGlobalBounds().top + ahouais[i].getGlobalBounds().height * 0.90f)
			yDirection[i] = -1.f;
		bars[i].move(0.f, yDirection[i]*0.007f);
	}
}


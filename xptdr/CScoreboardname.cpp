#include "CScoreboardname.h"

CScoreboardname::CScoreboardname(GameDataRef _data) : data(_data)
{
}

void CScoreboardname::keyboardInit()
{
}

void CScoreboardname::STEInit()
{
	//Le tableau correspond au lettre du clavier, 
					  //1234567890-effacer
	keyboard.push_back("1234567890-&");
					  //azertyuiop,Entrer
	keyboard.push_back("azertyuiop'!à");
					  //qsdfghjlm;ok
	keyboard.push_back("qsdfghjklm;²");
					  //wxcvbn,.!?:ok
	keyboard.push_back("wxcvbn,;!?:²");
					  //  MAJ  décaler gauche décaler droite barre espace ANNULER 
	keyboard.push_back("  ^<>    è");
	data->assets.LoadTexture("keyboardBlack", "res\\img\\keyboard_black.png");
	data->assets.LoadTexture("keyboardWhite", "res\\img\\keyboard_white.png");
	ahouais.setSize(sf::Vector2f(200.f, 50.f));
	ahouais.setPosition((float)data->assets.sCREEN_WIDTH  / 2.f, (float)data->assets.sCREEN_HEIGHT *0.3f);
	//mouseSelectionRectangle = sf::FloatRect(0.f, 0.f, 40.f, 40.f);//avec la scale actuelle (3) c'est 40 une case
	keyboardBlackSprite.setTexture(data->assets.GetTexture("keyboardBlack"));
	keyboardBlackSprite.setScale(4.f, 4.f);
	keyboardBlackSprite.setPosition(((float)data->assets.sCREEN_WIDTH / 2.f)- keyboardBlackSprite.getGlobalBounds().width/2.f, (float)data->assets.sCREEN_HEIGHT * 0.4f);
	keyboardWhiteSprite.setTexture(data->assets.GetTexture("keyboardWhite"));
	keyboardWhiteSprite.setScale(keyboardBlackSprite.getScale());
	keyboardWhiteSprite.setPosition(keyboardBlackSprite.getPosition());
	capslocksprite.setTexture(data->assets.GetTexture("keyboardWhite"));
	capslocksprite.setScale(keyboardBlackSprite.getScale());
	capslocksprite.setPosition(keyboardBlackSprite.getPosition());
	//capslocksprite.setPosition(sf::Vector2f(448.f,544.f));
	capslocksprite.setPosition(capslocksprite.getPosition().x + (32.f* keyboardBlackSprite.getScale().x), capslocksprite.getPosition().y + (64.f* keyboardBlackSprite.getScale().y));
	capslocksprite.setTextureRect(sf::IntRect(32, 64, 14, 13));
	nameText.setPosition((data->assets.sCREEN_WIDTH / 2) + 10.f, data->assets.sCREEN_HEIGHT * 0.3f);
	nameText.setCharacterSize(30);
	nameText.setFillColor(sf::Color::Black);
	nameText.setFont(data->assets.GetFont("Lato"));
	nameText.setString(name);
	bar.setSize(sf::Vector2f(2.f,40.f));
	bar.setPosition(nameText.getPosition());
	bar.setFillColor(sf::Color::Black);
	ui.setCharacterSize(12);
	ui.setFillColor(sf::Color::White);
	ui.setFont(data->assets.GetFont("Lato"));
	CapsLock.setFillColor(sf::Color::Black);
	CapsLock.setPosition(keyboardBlackSprite.getPosition().x + 172, keyboardBlackSprite.getPosition().y + 264);
	CapsLock.setSize(sf::Vector2f(4.f, 4.f)); 
}

void CScoreboardname::STEHandleInput()
{
	sf::Event event;
	int &x = mouseSelectionRectangle.x;
	int &y = mouseSelectionRectangle.y;
	while (data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
			data->window.close();
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
		{
			data->assets.changeScreenType(data->window, data->isFullScreen);
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Z)
			{
				if (y != 0)
					y -= 1;
			}
			if (event.key.code == sf::Keyboard::Q)
			{
				if (y == 4 && x == 2)
					break;
				if (y == 4 && (x >= 5 && x <= 8))
					x = 4;
				else if (x != 0)
					x -= 1;
			}
			if (event.key.code == sf::Keyboard::S)
			{
				if (y == 3 && (x < 2 || x > 9))
					break;
				if (y != 4 )
					y += 1;
			}
			if (event.key.code == sf::Keyboard::D)
			{
				if (y == 4 && x == 9)
					break;
			if (x != 11)
				x += 1;
			}
		}
			if (sf::Event::MouseButtonPressed == event.type)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					OUAIS = true;
				}
			}
	}
}

void CScoreboardname::STEUpdate(float delta)
{
	sf::IntRect temp;
	mousePositionScreen = sf::Mouse::getPosition(data->window);
	mousePositionKeyboard = (sf::Vector2f)mousePositionScreen - keyboardBlackSprite.getPosition();
	std::stringstream ss;
	ss << "mouse position : \n" << "Window : " << mousePositionScreen.x << " " << mousePositionScreen.y << "\n"
		<< "keyboard relative: " << mousePositionKeyboard.x << " " << mousePositionKeyboard.y<<std::endl
	<< "rectangleseleciton : " <<mouseSelectionRectangle.x << " " << mouseSelectionRectangle.y;
	ui.setString(ss.str());
	//On check les positions du clavier et on remet s'il faut
	if (mouseSelectionRectangle.x != -1 && mouseSelectionRectangle.y != -1)
	{
		int &x = mouseSelectionRectangle.x;
		int &y = mouseSelectionRectangle.y;
		if (x == 11 && (y == 2 || y == 3))
		{
			y = 2;
			temp = sf::IntRect(14 * x + 2 * x, 13 * y + 3 * y, 14, 26 + 12);
		tilePositionKeyboard.x = keyboardBlackSprite.getPosition().x + 56 * x + 8 * x;
		tilePositionKeyboard.y = keyboardBlackSprite.getPosition().y + 52 * y + 12 * y;	
		}
		else if (y == 4 && (x >= 5 && x <=8))
		{
			x = 5;
			temp = sf::IntRect(14 * x + 2 * x, 13 * y + 3 * y, (14 * 4) + 2 * 3, 13);
			tilePositionKeyboard.x = keyboardBlackSprite.getPosition().x + 56 * x + 8 * x;
			tilePositionKeyboard.y = keyboardBlackSprite.getPosition().y + 52 * y + 12 * y;
		x = 8;
		}
		else{
		tilePositionKeyboard.x = keyboardBlackSprite.getPosition().x + 56 * x + 8 * x;
		tilePositionKeyboard.y = keyboardBlackSprite.getPosition().y + 52 * y + 12 * y;
		temp = sf::IntRect(14 * x + 2 * x, 13 * y + 3 * y, 14, 13);
		}
		keyboardWhiteSprite.setPosition(tilePositionKeyboard);
		keyboardWhiteSprite.setTextureRect(temp);
	}
	if (OUAIS)
	{
		UpdateText();
		int a= (int)name.size();
		float tempX = nameText.getGlobalBounds().width-(((name.size()- stringPosition)*nameText.getLetterSpacing()*nameText.getCharacterSize())/2);
		bar.setPosition(sf::Vector2f(nameText.getPosition().x+tempX,nameText.getPosition().y));
		OUAIS = false;
	}
}
//Fonction appeler que si l'utilisateur appuie sur une touche
void CScoreboardname::UpdateText()
{
	int x = mouseSelectionRectangle.x;
	int y = mouseSelectionRectangle.y;
	char letter = keyboard[y][x];
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
		ok = true;
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
		if (capsInt == 1 || capsInt==2) {
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
		if(name.size()==stringPosition)
			name = name + letter;
		else {
			std::string name1 = name.substr(0, stringPosition);
			std::string name2 = name.substr(stringPosition);
			name = name1 + letter + name2;
		}
		stringPosition += 1;
		break;
	}
	nameText.setString(name);
}

void CScoreboardname::drawBar()
{
	if (barClock.getElapsedTime().asSeconds() <= 0.5f)
	{
		data->window.draw(bar);
	}
	else if(barClock.getElapsedTime().asSeconds() >= 1.f) {
		barClock.restart();
	}
}

void CScoreboardname::STEDraw(float delta)
{
	sf::RenderWindow & r = data->window;
	r.clear(sf::Color(191,165,117,1));
	r.draw(ahouais);
	r.draw(nameText);
	drawBar();
	r.draw(keyboardBlackSprite);r.draw(keyboardWhiteSprite);
	if (capsInt == 2)r.draw(capslocksprite);
	r.draw(CapsLock);
	r.draw(ui);
	r.display();
}


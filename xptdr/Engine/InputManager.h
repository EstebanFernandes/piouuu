#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class InputManager
{
private : 
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
public :
	//Constructeurs et destructeurs
	InputManager() {};
	~InputManager() {};
	//void updateMousePos();
	//Méthodes
	bool IsSpriteClicked(sf::Sprite object,
		sf::Mouse::Button button,sf::RenderWindow &window);
	sf::Vector2i GetMousePosition(sf::RenderWindow& window);
	bool IsTextClicked(sf::Text text,
		sf::Mouse::Button button, sf::RenderWindow &window);
	void setmousePosView(sf::Vector2f a)
	{
		mousePosView = a;
	}
	void setmousePosWindow(sf::Vector2i a)
	{
		mousePosWindow = a;
	}
	sf::Vector2f getmousePosView()
	{ 
		return mousePosView; 
	}
	sf::Vector2i getmousePosWinsow()
	{ 
		return mousePosWindow;
	}
};


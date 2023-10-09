#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
//Cette classe repr�sente une hitbox, une hitbox est compos� de plusieurs rectangles.
//Attach� � une entit�, il faudra update les hitboxs avec la position de l'entit� � 
//laquelle elle est attach�e.
class CHitbox
{
private:
	int size;
	std::vector<sf::RectangleShape> listHitbox;
public:
	CHitbox();
	void addHitbox(sf::RectangleShape rsParam);
	void moveHitbox(sf::Vector2f vect);
	void updateHitbox(sf::Vector2f pos);
	void renderHitbox(sf::RenderTarget& targz);
};


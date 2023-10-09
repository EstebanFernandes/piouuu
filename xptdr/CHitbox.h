#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
//Cette classe représente une hitbox, une hitbox est composé de plusieurs rectangles.
//Attaché à une entité, il faudra update les hitboxs avec la position de l'entité à 
//laquelle elle est attachée.
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


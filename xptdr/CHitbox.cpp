#include "CHitbox.h"

CHitbox::CHitbox()
{
	size = 0;
}
void CHitbox::addHitbox(sf::RectangleShape rsParam)
{
	listHitbox.push_back(rsParam);
	size++;
}

void CHitbox::moveHitbox(sf::Vector2f vect)
{
	for (int i = 0; i < size; i++)
	{
		listHitbox[i].move(vect);
	}
}

void CHitbox::updateHitbox(sf::Vector2f pos)
{
	//Inutile pour l'instant
}

void CHitbox::renderHitbox(sf::RenderTarget& targz)
{
	for (int i = 0; i < size; i++)
	{
		targz.draw(listHitbox[i]);
	}
}

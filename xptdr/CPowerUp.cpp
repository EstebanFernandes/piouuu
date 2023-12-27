#include "CPowerUp.h"

CPowerUp::CPowerUp(CAssetManager* a)
{
	assets = a;
	setSprite();
	getSprite().setPosition((float)assets->sCREEN_WIDTH, 300.f);
}

CPowerUp::CPowerUp(sf::Vector2f pos, CAssetManager* a)
{
	assets = a;
	setSprite();
	getSprite().setOrigin(
		getSprite().getGlobalBounds().width / 2,
		getSprite().getGlobalBounds().height / 2);
	getSprite().setPosition(pos);
}


void CPowerUp::updatewPlayer(float delta, CPlayer& player)
{
	if (checkCollisions(player))
	{
		player.gainHP(-5);
		needDelete = true;
	}
}


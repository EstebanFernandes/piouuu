#include "PowerUp.h"

PowerUp::PowerUp(AssetManager* a)
{
	assets = a;
	setSprite();
	getSprite().setPosition((float)Engine::SCREEN_WIDTH, 300.f);
}

PowerUp::PowerUp(sf::Vector2f pos, AssetManager* a)
{
	assets = a;
	setSprite();
	getSprite().setOrigin(
		getSprite().getGlobalBounds().width / 2,
		getSprite().getGlobalBounds().height / 2);
	getSprite().setPosition(pos);
}


void PowerUp::updatewPlayer(float delta, Player& player)
{
	if (checkCollisions(player))
	{
		player.gainHP(-5);
		needDelete = true;
	}
}


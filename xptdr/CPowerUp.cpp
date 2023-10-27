#include "CPowerUp.h"

CPowerUp::CPowerUp(CAssetManager* a)
{
	assets = a;
	setSprite();
}


void CPowerUp::updatewPlayer(float delta, CPlayer& player)
{
	if (checkCollisions(player))
	{
		player.gainHP(-5);
		needDelete = true;
	}
}


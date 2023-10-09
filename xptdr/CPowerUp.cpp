#include "CPowerUp.h"

CPowerUp::CPowerUp(CAssetManager* a)
{
	assets = a;
	setSprite();
}

void CPowerUp::setSprite()
{
	currentFrame = sf::IntRect(0, 0, 68, 68);
	getSprite().setTexture((*assets).GetTexture("lifePowerUp"));
	getSprite().setTextureRect(currentFrame);
	getSprite().setPosition(SCREEN_WIDTH, 300.f);
}

void CPowerUp::updatewPlayer(float delta, CPlayer& player)
{
	if (checkCollisions(player))
	{
		player.gainHP(-5);
		needDelete = true;
	}
}

void CPowerUp::updateFX()
{
	sf::Sprite& temp = getSprite();
	if(posSprite==4)
		posSprite = 0;
	if (animationTimer.getElapsedTime().asSeconds() > 0.3f)
	{
		currentFrame.left = posSprite*68;
		temp.setTextureRect(currentFrame);
		posSprite++;
		animationTimer.restart();
	}
}

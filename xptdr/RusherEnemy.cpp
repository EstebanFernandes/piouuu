#include "RusherEnemy.h"

RusherEnemy::RusherEnemy(CAssetManager* assetParam)
{
	initEnnemy(assetParam);
	initPositionX = assetParam->sCREEN_WIDTH * 1.05f;
	setMoveSpeed(5.f);
	setSprite();
}

void RusherEnemy::updateMovement(float delta)
{
	if (checkGlobalCollisions() && isPositionated)
		needDelete = true;
	updateLifeBar();
	// On avance pour se placer ou si il est l'heure de rush
	if ((onAvance == true && !isPositionated) || isRushing)
		moveEntity(sf::Vector2f(moveSpeed * -delta, 0));
	if (!isPositionated && getSprite().getPosition().x <= assets->sCREEN_WIDTH - getSprite().getGlobalBounds().width / 2.f) {
		isPositionated = true;
		colorSwitchClock.restart();
	}
}

void RusherEnemy::updateEntity(float delta)
{
	CEnemy::updateEntity(delta);
	if (isPositionated && counter < 3 && isRed == false && colorSwitchClock.getElapsedTime().asSeconds() >= 1.f) {
		isRed = true;
		counter++;
		colorSwitchClock.restart();
		getSprite().setColor(sf::Color::Red);
		redColorSwitchClock.restart();
	}
	else if (isRed == true && redColorSwitchClock.getElapsedTime().asSeconds() >= 0.5f) {
		getSprite().setColor(sf::Color::White);
		isRed = false;
	}
	else if (counter == 3 && colorSwitchClock.getElapsedTime().asSeconds() >= 1.f) {
		setMoveSpeed(120.f);
		isRushing = true;
	}
}

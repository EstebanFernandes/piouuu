#include "RusherEnemy.h"

RusherEnemy::RusherEnemy(CAssetManager* assetParam)
{
	initEnnemy(assetParam);
	assets->addSFX("enemyRush", &fxRush);
	initPositionX = assetParam->sCREEN_WIDTH * 1.05f;
	setMoveSpeed(5.f);
	setSprite();
	direction = sf::Vector2f(-1.f, 0.f);
	target = NULL;
}

RusherEnemy::RusherEnemy(CAssetManager* assets, CCharacter stat, sf::Vector2f pos, CMob* target_)
	:RusherEnemy(assets,target_)
{
	setCharacterStats(stat);
	initPos = pos;
}

RusherEnemy::RusherEnemy(CAssetManager* assets, CMob* target_)
	: RusherEnemy(assets)
{
	target = target_;
}

void RusherEnemy::updateMovement(float delta)
{
	if (checkGlobalCollisions() && isPositionated)
		needDelete = true;
	updateLifeBar();
	// On avance pour se placer ou si il est l'heure de rush
	if ((onAvance == true && !isPositionated) || isRushing)
	{
		sf::Vector2f avance = direction * moveSpeed * delta;
		moveEntity(avance);
	}
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
		if(fxRush.getStatus()== fxRush.Stopped)//  ca permet de s'assurer que le son n'est joué qu'une fois
		{
			if (target != NULL)
			{
				direction = utilities::dirAtoB(getSprite().getPosition(), target->getSprite().getPosition());
				if (isSpriteFlip())
					setRotation(utilities::getAngleFromDirection(direction) + 180.f);
				else
				setRotation(utilities::getAngleFromDirection(direction));
			}
			fxRush.play();
		}
	}
}
#include "RoamingEnemy.h"

RoamingEnemy::RoamingEnemy()
{
}

RoamingEnemy::RoamingEnemy(CAssetManager* assetParam) {
	info.scale.x = 1.5f;
	info.scale.y = 1.5f;
	initEnnemy(assetParam, info, "rusher");
	anim = CAnimation(getPointerSprite(), sf::Vector2i(73, 86), 2, 0.1f, 2);
	anim.changeIntRect(sf::Vector2i(0, 0), sf::IntRect(300,0,73,86));
	anim.changeIntRect(sf::Vector2i(1, 0), sf::IntRect(375, 0, 73, 86));
	isAnimated = true;
	anim.switchFrames();
	setSprite();
	getSprite().setColor(sf::Color::White);
	moveSpeed = 0.5f;
	initDirection();
	float angle = (float)180.f+(180.f / M_PIl)* atan2(dir.y, dir.x);
	getSprite().setRotation(angle);
}

RoamingEnemy::RoamingEnemy(CAssetManager* asset, CCharacter stat)
	: RoamingEnemy(asset)
{
	setCharacterStats(stat);
}

RoamingEnemy::RoamingEnemy(CAssetManager* asset, CCharacter stat, enemyInfo info_)
	:RoamingEnemy(asset,stat)
{
	setInfo(info_);
	initDirection();
}

void RoamingEnemy::updateMovement(float delta)
{
	if (a++ == 1)
		anim.setSprite(getPointerSprite());
	if(isAnimated)
		anim.updateAnimation();
	if (checkGlobalCollisions())
		needDelete = true;
	updateLifeBar();
	if (onAvance == true)
	{
		moveEntity(dir * delta * moveSpeed * 60.f);
	}
}


void RoamingEnemy::initDirection()
{
	if (info.direction.x == 0.f && info.direction.y == 0.f)
	{//On veut du random
		float minAngle = 0.f, maxAngle = 0.f;
		if (info.spawnSide == "droite" || info.spawnSide == "gauche")
		{
			minAngle = utilities::getAngleFromDirection(utilities::dirAtoB(spawnPos, sf::Vector2f(0.f,(float) assets->sCREEN_HEIGHT)));
			maxAngle = utilities::getAngleFromDirection(utilities::dirAtoB(spawnPos, sf::Vector2f(0.f, 0.f)));
		}
		else
		{
			minAngle = utilities::getAngleFromDirection(utilities::dirAtoB(spawnPos, sf::Vector2f(0.f,0.f)));
			maxAngle = utilities::getAngleFromDirection(utilities::dirAtoB(spawnPos, sf::Vector2f((float)assets->sCREEN_WIDTH, 0.f)));

		}
		if(minAngle != 0.f &&maxAngle!=0.f)
		{
			float angle = RandomFloat(minAngle, maxAngle);
			std::cout << "angle pour celui là : " << angle << std::endl;
			dir = utilities::getDirectionFromAngle(angle);
			setRotation(180.f+angle);
		}
	}
	else
		dir = info.direction;
}

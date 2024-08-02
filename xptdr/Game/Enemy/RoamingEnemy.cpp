#include "RoamingEnemy.h"

RoamingEnemy::RoamingEnemy()
{
}

RoamingEnemy::RoamingEnemy(AssetManager* assetParam) {
	info.scale.x = 1.5f;
	info.scale.y = 1.5f;
	initEnnemy(assetParam, info, "rusher");
	anim = Animation(getPointerSprite(), sf::Vector2i(73, 86), 2, 0.1f, 2);
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

RoamingEnemy::RoamingEnemy(AssetManager* asset, Character stat)
	: RoamingEnemy(asset)
{
	setCharacterStats(stat);
}

RoamingEnemy::RoamingEnemy(AssetManager* asset, Character stat, enemyInfo info_)
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
		bool isSet = false;
		float minAngle = 0.f, maxAngle = 0.f,offset=0.f;
		if (info.spawnSide == "droite" )
		{
			minAngle = utilities::getAngleFromDirection(utilities::dirAtoB(spawnPos, sf::Vector2f(0.f,(float) Engine::SCREEN_HEIGHT)));
			maxAngle = utilities::getAngleFromDirection(utilities::dirAtoB(spawnPos, sf::Vector2f(0.f, 0.f)));
			isSet = true;
		}
		else if (info.spawnSide == "gauche")
		{
			maxAngle = utilities::getAngleFromDirection(utilities::dirAtoB(spawnPos, sf::Vector2f((float)Engine::SCREEN_WIDTH, 0.f)));
			minAngle = utilities::getAngleFromDirection(utilities::dirAtoB(spawnPos, sf::Vector2f((float)Engine::SCREEN_WIDTH, (float)Engine::SCREEN_WIDTH)));
			offset = maxAngle;
			maxAngle = 360-maxAngle;
			minAngle = 0.f;
			isSet = true;
		}
		else if(info.spawnSide=="bas")
		{
			minAngle = utilities::getAngleFromDirection(utilities::dirAtoB(spawnPos, sf::Vector2f(0.f,0.f)));
			maxAngle = utilities::getAngleFromDirection(utilities::dirAtoB(spawnPos, sf::Vector2f((float)Engine::SCREEN_WIDTH, 0.f)));
			isSet = true;
		}
		else
		{
			maxAngle = utilities::getAngleFromDirection(utilities::dirAtoB(spawnPos, sf::Vector2f(0.f, (float)Engine::SCREEN_HEIGHT)));
			minAngle = utilities::getAngleFromDirection(utilities::dirAtoB(spawnPos, sf::Vector2f((float)Engine::SCREEN_WIDTH, (float)Engine::SCREEN_WIDTH)));
			isSet = true;
		}
		if(isSet)
		{
			float angle = RandomFloat(minAngle, maxAngle)+offset;
			std::cout << "angle pour celui là : " << angle << std::endl;
			if (angle > 360.f)
				angle -= 360.f;
			dir = utilities::getDirectionFromAngle(angle);
			setRotation(180.f+angle);
		}
	}
	else
		dir = info.direction;
}

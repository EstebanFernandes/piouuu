#include "RoamingEnemy.h"

RoamingEnemy::RoamingEnemy()
{
	directionY = 0;
}

RoamingEnemy::RoamingEnemy(CAssetManager* assetParam) {
	initEnnemy(assetParam);

	int ySpawnMax = assets->sCREEN_HEIGHT - (int)getGlobalBounds().height;
	float maxDirY = 0.16f * (1.f-(initPositionY / ySpawnMax));
	float minDirY = -(0.16f* initPositionY / (float)ySpawnMax);
	moveSpeed = 60.f;
	directionY = RandomFloat(minDirY, maxDirY);
	float angle = (float)180.f+(180.f / M_PIl)* atan2(directionY, directionX);
	getSprite().setRotation(angle);
}

RoamingEnemy::RoamingEnemy(CAssetManager* asset, CMob* target_) :
	RoamingEnemy(asset)
{
	target = target_;
}

void RoamingEnemy::updateMovement(float delta)
{
	if (checkGlobalCollisions())
		needDelete = true;
	updateLifeBar();
	if (onAvance == true)
		moveEntity(sf::Vector2f(directionX * delta * moveSpeed, directionY * delta * moveSpeed));
}

void RoamingEnemy::setDirectionY(float directionYParam)
{
	directionY = directionYParam;
	float angle = (float)180.f + (180.f / M_PIl) * atan2(directionY, directionX);
	setRotation(angle);
}

void RoamingEnemy::setDirectionX(float directionXParam)
{
	directionX = directionXParam;
	float angle = (float)180.f + (180.f / M_PIl) * atan2(directionY, directionX);
	setRotation(angle);
}

void RoamingEnemy::setDirection(sf::Vector2f dir)
{
	directionX = dir.x;
	directionY = dir.y;
	float angle = (float)180.f + (180.f / M_PIl) * atan2(directionY, directionX);
	setRotation(angle);
}

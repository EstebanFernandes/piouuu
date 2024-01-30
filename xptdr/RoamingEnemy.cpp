#include "RoamingEnemy.h"

RoamingEnemy::RoamingEnemy()
{
	direction.y = 0.f;
}

RoamingEnemy::RoamingEnemy(CAssetManager* assetParam) {
	initEnnemy(assetParam);

	int ySpawnMax = assets->sCREEN_HEIGHT - (int)getGlobalBounds().height;
	float maxDirY = 0.16f * (1.f-(initPositionY / ySpawnMax));
	float minDirY = -(0.16f* initPositionY / (float)ySpawnMax);
	moveSpeed = 60.f;
	direction.y = RandomFloat(minDirY, maxDirY);
	float angle = (float)180.f+(180.f / M_PIl)* atan2(direction.y, direction.x);
	getSprite().setRotation(angle);
}

void RoamingEnemy::updateMovement(float delta)
{
	if (checkGlobalCollisions())
		needDelete = true;
	updateLifeBar();
	if (onAvance == true)
		moveEntity(sf::Vector2f(direction.x * delta * moveSpeed, direction.y * delta * moveSpeed));
}

void RoamingEnemy::setDirectionY(float directionYParam)
{
	direction.y = directionYParam;
	float angle = (float)180.f + (180.f / M_PIl) * atan2(direction.y, direction.x);
	setRotation(angle);
}

void RoamingEnemy::setDirectionX(float directionXParam)
{
	direction.x = directionXParam;
	float angle = (float)180.f + (180.f / M_PIl) * atan2(direction.y, direction.x);
	setRotation(angle);
}

void RoamingEnemy::setDirection(sf::Vector2f dir)
{
	direction.x = dir.x;
	direction.x = dir.y;
	float angle = (float)180.f + (180.f / M_PIl) * atan2(direction.y, direction.x);
	setRotation(angle);
}

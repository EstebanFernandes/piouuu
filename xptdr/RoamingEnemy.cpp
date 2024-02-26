#include "RoamingEnemy.h"

RoamingEnemy::RoamingEnemy()
{
	direction.y = 0.f;
}

RoamingEnemy::RoamingEnemy(CAssetManager* assetParam) {
	initEnnemy(assetParam);
	
	setDirectionX(-1.0f);
	int ySpawnMax = assets->sCREEN_HEIGHT - (int)getGlobalBounds().height;
	float maxDirY = 0.16f * (1.f-(initPositionY / ySpawnMax));
	float minDirY = -(0.16f* initPositionY / (float)ySpawnMax);
	moveSpeed = 0.5f;
	direction.y = RandomFloat(minDirY, maxDirY);
	float angle = (float)180.f+(180.f / M_PIl)* atan2(direction.y, direction.x);
	getSprite().setRotation(angle);
}

RoamingEnemy::RoamingEnemy(CAssetManager* asset, CCharacter stat)
	: RoamingEnemy(asset)
{
	setCharacterStats(stat);
}

void RoamingEnemy::updateMovement(float delta)
{
	if (checkGlobalCollisions())
		needDelete = true;
	updateLifeBar();
	if (onAvance == true)
		moveEntity(direction * delta * moveSpeed * 60.f);
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
	direction.y = dir.y;
	float angle = (float)180.f + (180.f / M_PIl) * atan2(direction.y, direction.x);
	setRotation(angle);
}

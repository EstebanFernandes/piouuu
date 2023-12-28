#include "RoamingEnnemy.h"

RoamingEnnemy::RoamingEnnemy(CAssetManager* assetParam) {
	initEnnemy(assetParam);

	int ySpawnMax = assets->sCREEN_HEIGHT - (int)getGlobalBounds().height;
	float maxDirY = 0.16f * (1.f-(initPositionY / ySpawnMax));
	float minDirY = -(0.16f* initPositionY / (float)ySpawnMax);
	directionY = RandomFloat(minDirY, maxDirY);
	moveSpeed = 60.f;
	directionY = RandomFloat(minDirY, maxDirY);
	float angle = (float)180.f+(180.f / M_PIl)* atan2(directionY, directionX);
	getSprite().setRotation(angle);
}

void RoamingEnnemy::updateMovement(float delta)
{
	if (checkGlobalCollisions())
		needDelete = true;
	updateLifeBar();
	if (onAvance == true)
		moveEntity(sf::Vector2f(directionX * delta * moveSpeed, directionY * delta * moveSpeed));
}

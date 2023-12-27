#include "RoamingEnnemy.h"

RoamingEnnemy::RoamingEnnemy(CAssetManager* assetParam) {
	initEnnemy(assetParam);

	int ySpawnMax = assets->sCREEN_HEIGHT - (int)getGlobalBounds().height;
	float maxDirY = 0.16f * (1.f-(initPositionY / ySpawnMax));
	float minDirY = -(0.16f* initPositionY / (float)ySpawnMax);
	directionY = RandomFloat(minDirY, maxDirY);
	moveSpeed = 19.f;
}

void RoamingEnnemy::updateMovement(float delta)
{
	if (checkGlobalCollisions())
		needDelete = true;
	updateLifeBar();
	if (onAvance == true)
		moveEntity(sf::Vector2f(directionX * delta * moveSpeed, directionY));
}

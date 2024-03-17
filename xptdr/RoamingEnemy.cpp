#include "RoamingEnemy.h"

RoamingEnemy::RoamingEnemy()
{
}

RoamingEnemy::RoamingEnemy(CAssetManager* assetParam) {
	info.scale.x = 0.2f;
	info.scale.y = 0.2f;
	initEnnemy(assetParam,info);
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
		if (info.spawnSide == "droite" || info.spawnSide == "gauche")
		{
			int ySpawnMax = assets->sCREEN_HEIGHT - (int)getGlobalBounds().height;
			float maxDirY = 0.16f * (1.f - (spawnPos.y / ySpawnMax));
			float minDirY = -(0.16f * spawnPos.y / (float)ySpawnMax);
			moveSpeed = 0.5f;
			dir.y = RandomFloat(minDirY, maxDirY);
			if (info.spawnSide == "droite")
				dir.x = -1.f;
			else
				dir.x = 1.f;
		}
		else
		{
			int xSpawnMax = assets->sCREEN_WIDTH - (int)getGlobalBounds().width;
			float maxDirX = 0.16f * (1.f - (spawnPos.x / xSpawnMax));
			float minDirX = -(0.16f * spawnPos.x / (float)xSpawnMax);
			moveSpeed = 0.5f;
			dir.x = RandomFloat(minDirX, maxDirX);
			if (info.spawnSide == "bas")
				dir.y = -1.f;
			else
				dir.y = 1.f;
		}
	}
	else
		dir = info.direction;
}

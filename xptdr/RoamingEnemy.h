#pragma once
#include "CEnemy.h"

class RoamingEnemy : public CEnemy
{
private:
	float directionY;
	float directionX = -1.f;
public:
	RoamingEnemy();
	RoamingEnemy(CAssetManager* asset);
	void updateMovement(float delta);
	void enemyShoot() {}

	void setDirectionY(float directionYParam);
	void setDirectionX(float directionXParam);
};


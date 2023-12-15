#pragma once
#include "CEnemy.h"

class RoamingEnnemy : public CEnemy
{
private:
	float directionY;
	float directionX = -3.f;
public:
	RoamingEnnemy(CAssetManager* asset);
	void updateMovement(float delta);
	void enemyShoot() {}
};


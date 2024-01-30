#pragma once
#include "CEnemy.h"

class RoamingEnemy : public CEnemy
{
private:
	float directionY;
	float directionX = -1.f;
	CMob* target;
public:
	RoamingEnemy();
	RoamingEnemy(CAssetManager* asset);
	RoamingEnemy(CAssetManager* asset,CMob* target_);
	void updateMovement(float delta);
	void enemyShoot() {}

	void setDirectionY(float directionYParam);
	void setDirectionX(float directionXParam);
	void setDirection(sf::Vector2f dir);
};


#pragma once
#include "CEnemy.h"

class RoamingEnemy : public CEnemy
{
private:
	sf::Vector2f direction;
	CMob* target;
public:
	RoamingEnemy();
	RoamingEnemy(CAssetManager* asset);
	void updateMovement(float delta);
	void enemyShoot() {}

	void setDirectionY(float directionYParam);
	void setDirectionX(float directionXParam);
	void setDirection(sf::Vector2f dir);
};


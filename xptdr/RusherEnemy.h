#pragma once

#include "CEnemy.h"

class RusherEnemy : public CEnemy
{
private:
	bool isPositionated = false;
	bool isRushing = false;
	bool isRed = false;
	int counter = 0;
	sf::Clock colorSwitchClock;
	sf::Clock redColorSwitchClock;
public:
	RusherEnemy(CAssetManager* assets);
	void updateMovement(float delta);

	void updateEntity(float delta);
	void enemyShoot() {};
};


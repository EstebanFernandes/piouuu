#pragma once

#include "CEnemy.h"

class RusherEnemy : public CEnemy
{
private:
	bool isPositionated = false;
	bool isRushing = false;
	bool isRed = false;
	int counter = 0;
	sf::Sound fxRush;
	sf::Clock colorSwitchClock;
	sf::Clock redColorSwitchClock;
	CMob* target;
	sf::Vector2f direction;
public:
	RusherEnemy(CAssetManager* assets);
	RusherEnemy(CAssetManager* assets,CCharacter stat ,enemyInfo info, CMob* target_);
	RusherEnemy(CAssetManager* assets,CMob* target_);
	void updateMovement(float delta);

	void updateEntity(float delta);
	void enemyShoot() {};
	CEnemy* clone()  override {
		//initPosition();
		return new RusherEnemy(*this);
	}
};


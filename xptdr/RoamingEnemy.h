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
	RoamingEnemy(CAssetManager* asset,CCharacter stat);
	void updateMovement(float delta);
	void enemyShoot() {}

	void setDirectionY(float directionYParam);
	void setDirectionX(float directionXParam);
	void setDirection(sf::Vector2f dir);
	CEnemy* clone() override {
		initPosition();
		setSprite();
		return new RoamingEnemy(*this);
	}
};


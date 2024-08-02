#pragma once
#include "Enemy.h"

class RoamingEnemy : public Enemy
{
protected:
	sf::Vector2f dir;
	Animation anim;
	int a=0;
public:
	RoamingEnemy();
	RoamingEnemy(AssetManager* asset);
	RoamingEnemy(AssetManager* asset,Character stat);
	RoamingEnemy(AssetManager* asset, Character stat, enemyInfo info);

	void updateMovement(float delta);
	void enemyShoot() {}

	Enemy* clone() override {
		RoamingEnemy* temp = new RoamingEnemy(*this);
		temp->initPosition();
		temp->initDirection();
		temp->setSprite();
		return temp;
	}
	/// <summary>
	/// Surcharge de la direction adapté au roaming enemy
	/// </summary>
	void initDirection();
};


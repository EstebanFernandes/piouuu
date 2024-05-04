#pragma once
#include "CEnemy.h"

class RoamingEnemy : public CEnemy
{
protected:
	sf::Vector2f dir;
	CAnimation anim;
	int a=0;
public:
	RoamingEnemy();
	RoamingEnemy(CAssetManager* asset);
	RoamingEnemy(CAssetManager* asset,CCharacter stat);
	RoamingEnemy(CAssetManager* asset, CCharacter stat, enemyInfo info);

	void updateMovement(float delta);
	void enemyShoot() {}

	CEnemy* clone() override {
		initPosition();
		initDirection();
		setSprite();
		return new RoamingEnemy(*this);
	}
	/// <summary>
	/// Surcharge de la direction adapté au roaming enemy
	/// </summary>
	void initDirection();
};


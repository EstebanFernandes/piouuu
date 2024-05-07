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


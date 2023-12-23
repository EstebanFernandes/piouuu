#pragma once
#include "CEnemy.h"

class ShootingEnemy : public CEnemy
{
private:
	bool isPositionated = false;
	CGunslinger BAW;
	sf::Clock bulletClock;
public:
	ShootingEnemy(CAssetManager* asset);
	void updateMovement(float delta);
	void enemyShoot();

	//redéfinition de CEnemy
	void renderEntity(sf::RenderTarget& target);
	//redéfinition de CEnemy
	void updateEntity(float delta);
	/**
	* redéfinition de CHittingEntity
	* Permet de faire des dégats aux joueurs avec les tirs des ennemis
	*/
	void updatewPlayer(float delta, CPlayer& player);
};


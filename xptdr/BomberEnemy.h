#pragma once

#include "RoamingEnemy.h"

class BomberEnemy : public RoamingEnemy
{
private:
	CGunslinger BAW;
	sf::Clock bulletClock;
	bool isFacingLeft = true;
public:
	BomberEnemy(CAssetManager* assets);

	void changeInitalSide();

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


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

	//red�finition de CEnemy
	void renderEntity(sf::RenderTarget& target);
	//red�finition de CEnemy
	void updateEntity(float delta);
	/**
	* red�finition de CHittingEntity
	* Permet de faire des d�gats aux joueurs avec les tirs des ennemis
	*/
	void updatewPlayer(float delta, CPlayer& player);
};


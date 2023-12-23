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


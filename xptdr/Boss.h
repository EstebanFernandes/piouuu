#pragma once

#include "RoamingEnnemy.h"
#include "ShootingEnemy.h"



class Boss : public CEnemy
{
private:
	bool isPositionated = false;

	//invoking enemies related

	CPlayer* player1;
	std::vector<CHittingEntity*>* entityList;
	int* enemyNumber;

	CAssetManager* assets;

	/**
	life caps for phase switchs (I don't speak english very well)
	*/
	std::vector<float> phasesCaps;
	/*
	Current general phase of the boss (independant of the life)
	*/
	int currentPhase = 1;
	/*
	Life phase indicator for life-related phase switchs
	*/
	int currentLifePhase = 1;
	sf::Clock invulnerabilityClock;

	CGunslinger BAW;
	sf::Clock bulletClock;

public:
	Boss(CAssetManager* assetsParam, CPlayer* playerParam, std::vector<CHittingEntity*>* entityListParam, int* enemyNumber);

	/**
	possibilities :
	- roaming : the roaming enemy
	- shooter : the shooting enemy
	*/
	void addEnemy(std::string enemyName);
	//définition de méthodes virtuelles

	void updateMovement(float delta);
	void enemyShoot() {};

	//redéfinitions
	void updateEntity(float delta);
	void updatewPlayer(float delta, CPlayer& player);
	void renderEntity(sf::RenderTarget& target);

	//méthode pour changer de phase
	void changePhase();
};
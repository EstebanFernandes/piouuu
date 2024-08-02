#pragma once

#include "RoamingEnemy.h"
#include "ShootingEnemy.h"
class Boss : public Enemy, public InterfaceShootingEnemy
{
private:
	bool isPositionated = false;

	//invoking enemies related

	Player* player1;
	std::vector<HittingEntity*>* entityList;
	int* enemyNumber;

	AssetManager* assets;

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

	Gunslinger BAW;

	sf::Clock invulnerabilityClock;
	sf::Clock bulletClock;
	sf::Clock invokeClock;

public:
	Boss(AssetManager* assetsParam, Player* playerParam, std::vector<HittingEntity*>* entityListParam, int* enemyNumber);

	Enemy* clone() override {
		return new Boss(*this);
	}
	/**
	possibilities :
	- roaming : the roaming enemy
	- shooter : the shooting enemy
	*/
	void addEnemy(std::string enemyName);
	void addEnemyColumn();
	//définition de méthodes virtuelles

	void updateMovement(float delta);
	void enemyShoot() {};

	//redéfinitions
	void updateEntity(float delta);
	void updatewPlayer(float delta, Player& player);
	void renderEntity(sf::RenderTarget& target);

	//méthode pour changer de phase
	void changePhase();
};
#pragma once
#include "DEFINITIONS.h"
#include <SFML/Graphics.hpp>
#include<iostream>
#include "CPhysics.h"
#include"CBullet.h"
#include "CEntity.h"
#include "CGunslinger.h"
class CPlayer :  public CEntity
{
private:
	//Attributs
	float playerSpeed = 1.f;
	std::vector<sf::Sprite> lifeBar;
	int previouslifePoint;
	int previousMaxHealth;
	int damagePerBullet;

	//grr paw
	sf::Clock bulletClock;
	sf::Time bulletCooldown;

	sf::Clock hitClock;
	bool hittype = false;
	// Constrcuteurs et destruceurs 
	void setSprite();
	void initStat();
public:
	int xp;
	int maxXp;
	CGunslinger BAW;
	CPlayer();
	CPlayer(CAssetManager* a);
	virtual ~CPlayer();

	//Méthodes
	void initLifeBar();
	void updateCollision(CEntity1& b);
	void gainXP(int levelofEntity);
	void updateLifeBar();
	void iNeedMoreBullet();
	void updateEntity(float dt);
	void PLYupdateMovement(float dt);
	int getDamagePerBullet() { return damagePerBullet; }
	void renderLifeBar(sf::RenderTarget& target);
	void renderEntity(sf::RenderTarget& target);
	void updateFx();
	void setAssets(CAssetManager* a);
	bool checkGlobalCollisions();
	CGunslinger* getBAW() { return &BAW; }
};


#pragma once
#include "DEFINITIONS.h"
#include <SFML/Graphics.hpp>
#include<iostream>
#include "CPhysics.h"
#include"CBullet.h"
#include "CMob.h"
#include "CGunslinger.h"
#include "CAnimation.h"
//CLASSE qui représente un joueur
class CPlayer :  public CMob
{
private:
	//Attributs
	//S'occupe des animations du personnage
	CAnimation anim;
	float playerSpeed = 0.5f;
	//La barre de vie est une liste de sprite représentant chacun un point de vie
	std::vector<sf::Sprite> lifeBar;
	//les deux suivants servent à gérer la barre de vie
	int previouslifePoint;
	int previousMaxHealth;
	bool isMovingUp;
	bool isMovingDown;
	bool isMovingLeft;
	bool isMovingRight;


	//grr paw
	int damagePerBullet;
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
	void updateCollision(CEntity& b);
	void gainXP(int levelofEntity);
	void updateLifeBar();
	void iNeedMoreBullet();
	void updateEntity(float dt);
	void PLYupdateMovement(sf::Event event);
	void updateMovement(float dt);
	int getDamagePerBullet() { return damagePerBullet; }
	void renderLifeBar(sf::RenderTarget& target);
	void renderEntity(sf::RenderTarget& target);
	void updateFx();
	void setAssets(CAssetManager* a);
	bool checkGlobalCollisions();
	CGunslinger* getBAW() { return &BAW; }
};


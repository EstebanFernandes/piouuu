#pragma once
#include "DEFINITIONS.h"
#include <SFML/Graphics.hpp>
#include<iostream>
#include "CPhysics.h"
#include"CBullet.h"
#include "CMob.h"
#include "CGunslinger.h"
#include "CAnimation.h"
#include"SFML/Audio.hpp"
//CLASSE qui représente un joueur
class CPlayer :  public CMob
{
private:
	//Attributs
	//S'occupe des animations du personnage
	CAnimation anim;
	//La barre de vie est une liste de sprite représentant chacun un point de vie
	std::vector<sf::Sprite> lifeBar;
	//les deux suivants servent à gérer la barre de vie
	int previouslifePoint;
	int previousMaxHealth;

	bool isMovingUp;
	bool isMovingDown;
	bool isMovingLeft;
	bool isMovingRight;

	float score;

	//grr paw
	sf::Clock bulletClock;

	sf::Clock hitClock;
	bool hittype = false;
	// Constrcuteurs et destruceurs 
	void setSprite();
	void initStat();
public:
	CGunslinger BAW;
	CPlayer();
	CPlayer(CAssetManager* a);
	virtual ~CPlayer();

	//Méthodes
	float getScore();
	void addToScore(float scoreToAdd);
	void initLifeBar();
	void updateCollision(CEntity& b);
	void gainXP(int levelofEntity);
	void updateLifeBar();
	void iNeedMoreBullet();
	void updateEntity(float dt);
	void PLYupdateMovement(sf::Event event);
	void updateMovement(float dt);
	void renderLifeBar(sf::RenderTarget& target);
	void renderEntity(sf::RenderTarget& target);
	void updateFx();
	void setAssets(CAssetManager* a);
	bool checkGlobalCollisions();
	void resetMovement();
	CGunslinger* getBAW() { return &BAW; }
};
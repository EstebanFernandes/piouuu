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
	// 
	// S'occupe des améliorations spéciales du personnage
	//S'occupe des animations du personnage
	CAnimation anim;
	//La barre de vie est une liste de sprite représentant chacun un point de vie
	std::vector<sf::Sprite> lifeBar;
	//les deux suivants servent à gérer la barre de vie
	float previouslifePoint;
	float previousMaxHealth;

	bool isMovingUp;
	bool isMovingDown;
	bool isMovingLeft;
	bool isMovingRight;
	//Booléen pour l'autoAim
	float score;

	//grr paw
	sf::Clock bulletClock;

	sf::Clock hitClock;
	bool hittype = false;
	// Constrcuteurs et destruceurs 
	void setSprite();
	void initStat();
public:
	bool hasLevelUp = false;
	bool seekForTarget=false;
	CGunslinger BAW;
	CPlayer();
	CPlayer(CAssetManager* a);
	virtual ~CPlayer();

	//Méthodes
	float getScore()
	{
		return score;
	}
	void addToScore(float scoreToAdd)
	{
		score += scoreToAdd;
	}
	void initLifeBar();
	void updateCollision(CEntity& b);
	void gainXP(int levelofEntity);
	void updateLifeBar();
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
	void traitermisc(std::string& misc);
	void updateMisc();
	void updateAfterKillingEntity();
};
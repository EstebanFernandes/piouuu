#pragma once
#include "DEFINITIONS.h"
#include <SFML/Graphics.hpp>
#include<iostream>
#include "CPhysics.h"
#include"CBullet.h"
#include "CMob.h"
#include "LaserGenerator.h"
#include "CAnimation.h"
#include"SFML/Audio.hpp"
//CLASSE qui représente un joueur
class CPlayer :  public CMob
{
private:
	//Attributs

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
	bool wantToDash=false;
	bool isDashing = false;
	//Booléen pour l'autoAim
	float score;
	sf::Vector2f dir;
	//grr paw
	sf::Clock bulletClock;
	sf::Clock dashClock;
	float cdDash = 0.5f;
	float dashDistance = 100.f;
	float distancethrought=0.f;
	float msDash = 1.f;
	sf::Clock hitClock;
	//Liste des effets sur les balles, on les ajoutes avant de tirer 
	std::vector<effetspecial*> effectByBullet;
	bool hittype = false;

	/// <summary>
	/// pointeur vers l'arme principal
	/// </summary>
	Weapon* mainWeapon = new CGunslinger();

	/// <summary>
	/// pointeur vers l'arme secondaire
	/// </summary>
	Weapon* secondaryWeapon = nullptr;

	// Constrcuteurs et destruceurs 
	void setSprite();
	void initStat();

public:

	bool hasLevelUp = false;
	bool seekForTarget=false;
	CPlayer();
	CPlayer(CAssetManager* a);
	~CPlayer();

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
	Weapon* getMainWeapon();
	void setMainWeapon(Weapon* weaponParam);
	Weapon* getSecondaryWeapon();
	void setSecondaryWeapon(Weapon* weaponParam);
	void traitermisc(std::string& misc);
	void updateMisc();
	void AAA() {
		specificites.push_back("dot");
		traitermisc(specificites.back());
	}
	void iNeedMoreBullet();
	void updateDash(float delta);
};
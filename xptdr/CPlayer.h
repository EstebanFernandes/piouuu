#pragma once
#include "DEFINITIONS.h"
#include <SFML/Graphics.hpp>
#include<iostream>
#include "CPhysics.h"
#include"CBullet.h"
#include "CMob.h"
#include "laserWeapon.h"
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
	bool isDashInvicible = false;
	float dashDamage = 0.f;
	sf::Clock hitClock;
	sf::Sprite R2Sprite;
	CAnimation R2Anim;
	sf::Vector2f R2Offset;
	//Liste des effets sur les balles, on les ajoutes avant de tirer 
	bool hittype = false;

	/// <summary>
	/// pointeur vers l'arme principal
	/// </summary>
	Weapon* mainWeapon = new CGunslinger();

	/// <summary>
	/// pointeur vers l'arme secondaire
	/// </summary>
	Weapon* secondaryWeapon = new CGunslinger();

	// Constrcuteurs et destruceurs 
	void setSprite();
	void initStat();
	void setValue(float& init, std::string modif);
	void setValue(int& init, std::string modif);
public:
	//Mouvement

	sf::Keyboard::Key upKey = sf::Keyboard::Z;
	sf::Keyboard::Key downKey = sf::Keyboard::S;
	sf::Keyboard::Key leftKey = sf::Keyboard::Q;
	sf::Keyboard::Key rightKey = sf::Keyboard::D;
	sf::Keyboard::Key dashKey = sf::Keyboard::T;
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
	void renderUI(sf::RenderTarget& target) {
		renderLifeBar(target);
	}
	void updateFx();
	void setAssets(CAssetManager* a);
	bool checkGlobalCollisions();
	void resetMovement();
	Weapon* getMainWeapon();
	void setMainWeapon(Weapon* weaponParam);
	Weapon* getSecondaryWeapon();
	void setSecondaryWeapon(Weapon* weaponParam);
	void traitermisc(std::string& misc);
	void traitermisc(std::string& misc,int type);
	void updateMisc();
	void AAA() {
		mainWeapon->typeTir = typeAim::Spin;
	}
	void iNeedMoreBullet();
	void updateDash(float delta);
	bool matchTypewithValue(std::string type, std::string value);
	void setDashDistance(float dd) { dashDistance = dd; }
	float getDashDistance() { return dashDistance; }
	void setDashDamage(float dd) { dashDamage = dd; }
	float getDashDamage() { return dashDamage; }
	void setIsDashInvicible(bool isD) { isDashInvicible = isD; }
	void moveEntity(sf::Vector2f mov) {
		if (mov.x != 0.f)
		{
			std::cout << "";
		}
		getSprite().move(mov);
		R2Sprite.move(mov);
	}
	void setPositionEntity(sf::Vector2f f)
	{
		setPositionEntity(f.x, f.y);
	}
	void setPositionEntity(float x, float y)
	{
		getSprite().setPosition(x,y);
		R2Sprite.setPosition(getGlobalBounds().left+ R2Sprite.getOrigin().x+R2Offset.x,
			getGlobalBounds().top+ R2Sprite.getOrigin().y+R2Offset.y);
		//std::cout << R2Sprite.getPosition().x << " y :" << R2Sprite.getPosition().y << std::endl;
	}
	void debugh() {
		std::cout << "Origin R2, x : " << R2Sprite.getOrigin().x << " y : " << R2Sprite.getOrigin().y << std::endl;
		std::cout << "Limite de R2, left : " << R2Sprite.getGlobalBounds().left << " top : " << R2Sprite.getGlobalBounds().top << std::endl;
	}
};
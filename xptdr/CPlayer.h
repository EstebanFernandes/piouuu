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
#include"CGrapheUpdate.h"
#include "upgradeStock.h"
//CLASSE qui représente un joueur
class CPlayer :  public CMob
{
private:
	//Attributs
	sf::Color playerColor = sf::Color(3,140,252);
	//sf::Color playerColor = sf::Color::Green;
	//S'occupe des animations du personnage
	CAnimation anim;
	sf::Clock animationTimer;
	sf::Sprite explosionSprite;
	CAnimation animExplosionSprite;
	//La barre de vie est une liste de sprite représentant chacun un point de vie
	sf::CircleShape iconCircle;
	sf::CircleShape iconCircle2;
	sf::RectangleShape lifeBarBG2;
	sf::Sprite icon;
	//les deux suivants servent à gérer la barre de vie
	float previouslifePoint;
	float previousMaxHealth;
	//Liste de graphes d'amélioration pour le joueur
	std::vector<CGrapheUpdate> Upgradegraphs;
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
	sf::Sound* planeSound;
	/// <summary>
	/// pointeur vers l'arme principal
	/// </summary>
	Weapon* mainWeapon = NULL;

	/// <summary>
	/// pointeur vers l'arme secondaire
	/// </summary>
	Weapon* secondaryWeapon = NULL;

	// Constrcuteurs et destruceurs 
	void setSprite();
	void initStat();
	void setValue(float& init, std::string modif);
	void setValue(int& init, std::string modif);
public:
	std::vector<graphComponent> curUpgrade;
	int numero = -1;
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
	void gainXP(int xp_);
	void updateLifeBar();
	void updateEntity(float dt);
	void PLYupdateMovement(sf::Event& event);
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
	/// <summary>
	/// set la position de la  bar de vie, la position correspond au haut à droite de la petite image de l'avion
	/// </summary>
	/// <param name="pos"></param>
	void setLifeBarPosition(sf::Vector2f& pos);
	/// <summary>
	/// Set le numéro du joueur, selon change les touches et la couleur
	/// </summary>
	/// <param name="i"></param>
	void setNumero(int& i);
	void setBoolLevelUp(bool a)
	{
		hasLevelUp = a;
	}
	std::vector<CGrapheUpdate>* getGraphs()
	{
		return &Upgradegraphs;
	}
	void playSound(bool areWe=true)
	{
		if (areWe && planeSound->getStatus() == sf::Sound::Stopped)
			planeSound->play();
		else if (!areWe)
			planeSound->stop();
	}
};
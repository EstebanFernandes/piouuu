#pragma once

#include "../Engine/AssetManager.h"
#include"WeaponStat.h"
#include "../Mob.h"
#include"../Buff/BuffEntity.h"
#define nbBullet 6
	typedef enum
	{
		doubleTirs1 = nbBullet,
		doubleTirs2,
		autoAim,
		gunshotAim,
		circleShot,
		bombe,
		Spin,
		doubleTirs3
	} typeAim;


	typedef enum
	{
		classic,
		explosiveBullet,
		circle
	} typeBullet;

class Weapon
{
protected:
	bool* seekForTarget = NULL;
	int typeArme = -1;
	/// <summary>
	/// définit le décalage entre la position du joueur et l'endroit où l'on doit tirer
	/// </summary>
	sf::Vector2f weaponPos;

	std::vector<effetspecial*> effetOnHit;

	WeaponStat referenceStat;
	sf::Keyboard::Key touche;
	float angleOffset;
	bool isShooting = false;
	sf::Clock angleClock;
	void updateAngle();
public:
	bool wantToShoot=false;
	Mob* pointerToPlayer;
	~Weapon();

	/// <summary>
	/// Pour définir le comportement du tir on choisit l'un de ceux ci dessous
	/// </summary>

	sf::Sound *bulletSound = NULL;
	typedef enum {
		gunslinger = 0,
		laser = 1
	}typesArme;
	AssetManager* assets;

	int typeBalle = 0;
	int typeTir = 0;

	//Méthodes 
	


	//Accesseurs

	sf::Vector2f getWeaponPos();
	void setWeaponPos(sf::Vector2f posParam);
	void setTypeArme(int type);
	int getTypeArme();
	void addBulletType(int index);
	WeaponStat& getWeaponStats();
	/// <summary>
	/// Défini la position relative de l'arme par rapport au centre de l'arme
	/// </summary>
	/// <param name="pos"></param>
	virtual void setWeaponStats(WeaponStat statsParam);
	void setTouche(sf::Keyboard::Key touche_) {
		touche = touche_;
	}
	sf::Keyboard::Key getTouche()
	{
		return touche;
	}
	std::vector<effetspecial*>& getEffect();
	// à redéfinir

	virtual void changeTarget(Mob* r) = 0;
	virtual void traiterMisc(int misc) = 0;
	virtual int checkCollisions(Mob& b) = 0;
	virtual void weaponControls(sf::Event) = 0;
	virtual void weaponShoot() = 0;
	virtual void updateWeapon(float dt) = 0;
	virtual void renderWeapon(sf::RenderTarget& target) = 0;
	virtual void setBulletAsset(std::string assetName) = 0;
	virtual std::string getBulletAsset() = 0;
	void setAimBoolean(bool* pointToBool)
	{
		seekForTarget = pointToBool;
	}
	/// <summary>
	/// Renvoie true si on vient de tirer
	/// </summary>
	/// <returns></returns>
	bool isWeaponShooting() { return isShooting; }
	void addBuff(effetspecial* newEffet)
	{
		effetOnHit.push_back(newEffet);
	}
};


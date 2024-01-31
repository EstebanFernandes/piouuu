#pragma once

#include "CAssetManager.h"
#include"CWeaponStat.h"
#include "CMob.h"

class Weapon
{
protected:
	int typeArme = -1;
	/// <summary>
	/// définit le décalage entre la position du joueur et l'endroit où l'on doit tirer
	/// </summary>
	sf::Vector2f weaponPos;

	/// <summary>
	/// On utilise cette balle pour définir le comportement de toute celle que l'on va tiré, on peut ajouter des effets dessus,
	/// modifier ses stats.
	/// </summary>
	CWeaponStat referenceStat;
public:
	~Weapon();

	/// <summary>
	/// Pour définir le comportement du tir on choisit l'un de ceux ci dessous
	/// </summary>
	typedef enum
	{
		doubleTirs1 = 1,
		doubleTirs2,
		autoAim,
		gunshotAim,
		circleShot,
		bombe
	} typeAim;


	typedef enum
	{
		classic,
		dotBullet,
		explosiveBullet,
		fire
	} typeBullet;


	sf::Sound bulletSound;
	typedef enum {
		gunslinger = 0,
		laser = 1
	}typesArme;
	CAssetManager* assets;

	int typeBalle = 0;
	int typeTir = 0;

	//Méthodes 
	


	//Accesseurs

	sf::Vector2f getWeaponPos();
	void setWeaponPos(sf::Vector2f posParam);
	void setTypeArme(int type);
	int getTypeArme();
	CWeaponStat& getWeaponStats();
	void setWeaponStats(CWeaponStat statsParam);

	// à redéfinir

	virtual void changeTarget(CMob* r) = 0;
	virtual void traiterMisc(int misc) = 0;
	virtual bool checkCollisions(CMob& b) = 0;
	virtual void weaponControls(sf::Event) = 0;
	virtual void weaponShoot() = 0;
	virtual void updateWeapon(float dt) = 0;
	virtual void renderWeapon(sf::RenderTarget& target) = 0;
	virtual void setBulletAsset(std::string assetName) = 0;
	/// <summary>
	/// Défini la position relative de l'arme par rapport au centre de l'arme
	/// </summary>
	/// <param name="pos"></param>
	void setWeaponPos(sf::Vector2f pos) { weaponPos = pos; }
};


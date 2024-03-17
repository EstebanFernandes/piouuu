#pragma once

#include "CAssetManager.h"
#include"CWeaponStat.h"
#include "CMob.h"

#define nbBullet 4
	typedef enum
	{
		doubleTirs1 = 4,
		doubleTirs2,
		autoAim,
		gunshotAim,
		circleShot,
		bombe,
		Spin
	} typeAim;


	typedef enum
	{
		classic,
		dotBullet,
		explosiveBullet,
		fire
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
	/// <summary>
	/// On utilise cette balle pour définir le comportement de toute celle que l'on va tiré, on peut ajouter des effets dessus,
	/// modifier ses stats.
	/// </summary>
	CWeaponStat referenceStat;
	sf::Keyboard::Key touche;
	float angleOffset;
public:
	~Weapon();

	/// <summary>
	/// Pour définir le comportement du tir on choisit l'un de ceux ci dessous
	/// </summary>

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
	void addBulletType(int index);
	CWeaponStat& getWeaponStats();
	/// <summary>
	/// Défini la position relative de l'arme par rapport au centre de l'arme
	/// </summary>
	/// <param name="pos"></param>
	virtual void setWeaponStats(CWeaponStat statsParam);
	void setTouche(sf::Keyboard::Key touche_) {
		touche = touche_;
	}
	sf::Keyboard::Key getTouche()
	{
		return touche;
	}
	std::vector<effetspecial*>& getEffect();
	// à redéfinir

	virtual void changeTarget(CMob* r) = 0;
	virtual void traiterMisc(int misc) = 0;
	virtual bool checkCollisions(CMob& b) = 0;
	virtual void weaponControls(sf::Event) = 0;
	virtual void weaponShoot() = 0;
	virtual void updateWeapon(float dt) = 0;
	virtual void renderWeapon(sf::RenderTarget& target) = 0;
	virtual void setBulletAsset(std::string assetName) = 0;
	void setAimBoolean(bool* pointToBool)
	{
		seekForTarget = pointToBool;
	}
};


#pragma once
#include"CBulletAuto.h"
#include "Weapon.h"
#include <bitset>
#include"dot.h"
#define Balle = true
#define Tir = false
#define nbBullet 4
#define nbAim 6
class CGunslinger : public Weapon
{
private:
	std::vector<CBulletAuto> magasine;

	//grr paw
	sf::Clock bulletClock;

	/// <summary>
	/// Fonction qui initialise tous les buffs selon les stats dans reference Stat ainsi que le nommbre "type balle"
	/// </summary>
	/// <param name="ref"></param>
	void initBuff(CBulletAuto& ref);
public:
	~CGunslinger() {
	}
	sf::Vector2f bulletScale = sf::Vector2f(1.f, 1.f);


	CGunslinger();
	void setSprite(){}
	void updateWeapon(float dt);
	void weaponControls(sf::Event event);
	void weaponShoot();
	//Setters for bullet's skin, must've been initialized before, this method will just load the bullet's skin from the asset manager.
	void setBulletAsset(std::string assetName) {
		getWeaponStats().nameImage = assetName;
	}
	void renderWeapon(sf::RenderTarget& target);
	void traiterMisc(int misc);
	bool checkCollisions(CMob& b);
	/// <summary>
	/// à terme on utilise que celle là
	/// </summary>
	/// <param name="pos"></param>
	void iNeedMoreBullets(sf::Vector2f pos);
	
	void addShootType(int type);
	void addBulletType(int type);
	/// <summary>
	/// Spécialement pour les balles autoguidés
	/// permet de changer de cible
	/// </summary>
	/// <param name="r"></param>
	void changeTarget(CMob* r) {       
		for (int i = 0; i < magasine.size(); i++)
		{
			if(!magasine[i].isMobSet)
				magasine[i].setMob(r);
		}
	}
	std::vector<CBulletAuto>* getVector() { 
			return &magasine;
	}
	std::vector<CBulletAuto>& getReferenceVector() { return magasine; }
	//Fonction qui ajoute un type de balle ou de tir, on spécifie si on veut en garder d'autres ou pas, c'est la fonction la plus importante de cette classe
	/// <summary>
	/// Fonction qu'on utilise pour parametrer notre balle avant de l'ajouter dans le magasine
	/// </summary>
	/// <param name="index"></param>
	void addByIndex(CBulletAuto&,int index);
	
	void setGunShotDistance(float e)
	{
		getWeaponStats().maxDistance = e;
	}
	/// <summary>
	/// set the penetration for any bullet
	/// </summary>
	/// <param name="param">= penetration of the ammo</param>
	void setPenetration(int param)
	{
		if (param >= 0) {
			getWeaponStats().penetration = param;
		}
	}

	/// <summary>
	///	fonction qui tire de la position de base à la position d'une cible
	/// 	
	/// </summary>
	/// <param name="initPos">la position de base</param>
	/// <param name="targetPos"> la position de la cible</param>
	/// <param name="damage"> les dommages de la balle</param>
	/// <param name="bulletSpeed">la vitesse de la balle</param>
	void shootTowardDirection(sf::Vector2f initPos, sf::Vector2f targetPos);
};


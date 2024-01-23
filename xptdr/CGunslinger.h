#pragma once
#include"CEntity.h"
#include"CBulletAuto.h"
#include <bitset>
#define Balle = true
#define tirBool = false
#define nbBullet 5
#define nbAim 5
class CGunslinger : public CEntity
{
private:
	std::vector<CBulletAuto> magasine;
	void updatebyIndex(float dt, int index);
	void pushByIndex(int index);
	float gunshotDistance;
	std::string nameBulletSkin = "";
	sf::Sound bulletSound;
sf::SoundBuffer bulletSoundBuffer;
int penetration = 0;
public:
	typedef enum
	{
		classic,
		autoAim,
		dot,
		explosiveBullet,
		gunshot
	} typeBullet;
	//�a va fonctionner comme un nombre binaire on additione selon l'indice de l'enum au carr� et apr�s on d�compose � chaque fois 

	typedef enum
	{
		doubleTirs1=1,
		doubleTirs2,
		gunshotAim,
		circleShot
	} typeAim;
	int typeTir;
	int typeBalle;
	CGunslinger();
	void setSprite(){}
	void updateEntity(float dt);
	//Setters for bullet's skin, must've been initialized before, this method will just load the bullet's skin from the asset manager.
	void setBulletAsset(std::string assetName) {
		if (assetName != "")
			nameBulletSkin = assetName;
	}
	void renderEntity(sf::RenderTarget& target);
	void updateCollision(CEntity& b);
	void iNeedMoreBullets(sf::Vector2f pos, int damage);
	void iNeedMoreBullets(sf::Vector2f pos, int damage,float bulletSpeed);
	void iNeedMoreBullets(sf::Vector2f pos, int damage, float bulletSpeed, sf::Vector2f dir);

	
	/// <summary>
	/// Sp�cialement pour les balles autoguid�s
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
	//Fonction qui ajoute un type de balle ou de tir, on sp�cifie si on veut en garder d'autres ou pas, c'est la fonction la plus importante de cette classe
	void addBulletMode(bool type,int m) {
		if (type)
		{
			if (m >= 0 && m <= nbBullet - 1)
			{
				std::bitset<nbBullet> bit = std::bitset<nbBullet>(typeBalle);
				if (bit[m] == 0)
				{
					switch (m)
					{
					case classic:
						typeBalle = 1;
						break;
					default:
						typeBalle += (int)pow(2, m);
						break;
					}
				}
				else
					std::cout << "am�lioration d�j� mise\n";
			}
		}
		else {
			if (m >= 0 && m <= nbAim-1)
			{
				std::bitset<nbAim> bit = std::bitset<nbAim>(typeTir);
				if (bit[m] == 0)
				{
					switch (m)
					{
					
					case gunshotAim:
						typeBalle += (int)pow(2, m);
						break;
					default:
						typeTir  = (int)pow(2, m);
						break;
					}
				}
				else
					std::cout << "am�lioration d�j� mise\n";
			}
		}
	}
	void setGunShotDistance(float e)
	{
		gunshotDistance = e;
	}
	/// <summary>
	/// set the penetration for any bullet
	/// </summary>
	/// <param name="param">= penetration of the ammo</param>
	void setPenetration(int param)
	{
		if (param >= 0)
			penetration = param;
	}

	/// <summary>
	///	fonction qui tire de la position de base � la position d'une cible
	/// 	
	/// </summary>
	/// <param name="initPos">la position de base</param>
	/// <param name="targetPos"> la position de la cible</param>
	/// <param name="damage"> les dommages de la balle</param>
	/// <param name="bulletSpeed">la vitesse de la balle</param>
	void shootTowardDirection(sf::Vector2f initPos, sf::Vector2f targetPos, int damage, float bulletSpeed);
};


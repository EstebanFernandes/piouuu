#pragma once
#include"CEntity.h"
#include"CBulletAuto.h"
#include <bitset>
#define Balle = true
#define tirBool = false
#define nbBullet 5
#define nbAim 4
class CGunslinger : public CEntity
{
private:
	std::vector<CBulletAuto> magasine;
	void updatebyIndex(float dt, int index);
	void pushByIndex(int index);
	float gunshotDistance;
public:
	typedef enum
	{
		classic,
		autoAim,
		dot,
		explosiveBullet,
		gunshot
	} typeBullet;

	typedef enum
	{
		doubleTirs1=1,
		doubleTirs2,
		gunshotAim
	} typeAim;
	//ça va fonctionner comme un nombre binaire on additione selon l'indice de l'enum au carré et après on décompose à chaque fois 
	int typeTir;
	int typeBalle;
	CGunslinger();
	void setSprite(){}
	void updateEntity(float dt);
	void renderEntity(sf::RenderTarget& target);
	void updateCollision(CEntity& b);
	void iNeedMoreBullets(sf::Vector2f pos, int damage);
	void iNeedMoreBullets(sf::Vector2f pos, int damage,float bulletSpeed);
	void iNeedMoreBullets(sf::Vector2f pos, int damage, float bulletSpeed, sf::Vector2f dir);

	//Spécialement pour les balles autoguidés
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
	//Fonction qui ajoute un type de balle ou de tir, on spécifie si on veut en garder d'autres ou pas, c'est la fonction la plus importante de cette classe
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
					std::cout << "amélioration déjà mise\n";
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
					case classic:
						typeTir = 1;
						break;

					case doubleTirs1:
						typeTir  = (int)pow(2, m);
						break;
					case doubleTirs2:
						typeTir = (int)pow(2, m);
						break;
					case gunshotAim:
						typeTir = (int)pow(2, m);
						typeBalle += (int)pow(2, m);
						break;
					default:
					/*	typeTir += (int)pow(2, m);
						if (bit[0] == 1)
							typeTir--;*/
						break;
					}
				}
				else
					std::cout << "amélioration déjà mise\n";
			}
		}
	}
	void setGunShotDistance(float e)
	{
		gunshotDistance = e;
	}
};


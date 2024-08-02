#pragma once
#include "SFML/Graphics.hpp"
#include "../DEFINITIONS.h"
#include "../Engine/Animation.h"
#include"../Buff/BuffEntity.h"
#include"WeaponStat.h"
class Bullet : public Mob, public BuffEntity
{
protected:
	Animation anim;
	bool isAnimated = false;
	sf::Vector2f direction;
	sf::Vector2f bulletScale;
	float bulletSpeed = 2.f;
	int damage;
	int penetration = 0;
	float distance = 0.f;
	std::vector<Mob*> entityHitting;
	Mob* target;
	bool targetSet = false;
public :

	~Bullet();
	Bullet();
	Bullet(const Bullet& bullet);
	Bullet& operator = (const Bullet& Point);


	Bullet(int damaage, sf::Vector2f pos, sf::Vector2f dir, int penetration
		,std::string nameImage, AssetManager* assetss);
	Bullet(int damaage, sf::Vector2f pos, sf::Vector2f dir, float bulletSpeed, int penetration
		,std::string nameImage, AssetManager* assetss, sf::Vector2f bulletScale);
	Bullet(WeaponStat stat, AssetManager* a);
	void setSprite(std::string nameImage);
	void updateEntity(float dt);
	void renderEntity(sf::RenderTarget& target);
	void renderUI(sf::RenderTarget& target) {

	}
	void setSprite();
	//Surchagrge pour les collisions entre objet
	int getDamage() { return damage; }
	//méthode appeler automatiquement à la fin du constructeur qui s'occupe de régler le sprite selon la direction.
	//Le sprite de la balle doit être dessiner de base de la droite vers la gauche.
	//L'appel de cette fonction suppose que la direction de la balle a été déclarée
	void setDirectionSprite();

	/// <summary>
	/// Méthode surchargé qui a un comportement différent du checkCollision de base
	/// 
	/// </summary>
	/// <param name="b"></param>
	/// <returns></returns>
	bool checkCollisions(Mob& b);
	void setBulletPos(sf::Vector2f pos) {
		getSprite().setPosition(pos);
	}
	void setDamage(int dmg) { damage = dmg; }

	void setDirection(sf::Vector2f d)
	{
		direction = d;
	}
	float getDistance() {
		return distance;
	}

	void setStat(WeaponStat& stat);
	bool isTargetSet() { return targetSet; }
	void setMob(Mob* m) {
		target = m;
		targetSet = true;
	}
};


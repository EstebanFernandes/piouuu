#pragma once
#include"Bullet.h"
//Balle qui vise toute seul
class BulletAuto : public Bullet
{
private :
	Mob* mob = NULL;
	float gunshotDistance = 0.f;
	float gunShotTotalDistance;
public:
	bool isMobSet = false;
	bool isGunShot = false;
	bool isExplosive = false;
	bool isThisIt = false;
	sf::RectangleShape hitbox;
	Animation anim;
	bool isAnimated = false;
	int count = 0;
	BulletAuto();
	BulletAuto(WeaponStat stat, AssetManager* a);
	BulletAuto(int damage, float bulletSpeed, sf::Vector2f dir,int penetration, std::string nameImage, sf::Vector2f bulletScale_, AssetManager* a);

	//méthode classico classique
	BulletAuto(int daamg, sf::Vector2f pos, float bulletSpeeed, sf::Vector2f dir,int penetration, std::string nameImage, AssetManager* as, sf::Vector2f bulletScale) :
		Bullet(daamg, pos, dir, bulletSpeeed, penetration,nameImage, as, bulletScale) {
		if (bulletSpeeed != 0.f)
			bulletSpeed = bulletSpeeed;
	}

	// méthode utilisée par les bombes ennemis
	BulletAuto(int daamg, sf::Vector2f pos, float bulletSpeeed, sf::Vector2f dir, int penetration, std::string nameImage, AssetManager* as, sf::Vector2f bulletScale, bool isABombe);

	//Méthode utilisée pour le gunshot
	BulletAuto(int daamg, sf::Vector2f pos, sf::Vector2f dir,float bulletSpeeed, float totaldistance,int penetration, std::string nameImage, AssetManager* as, sf::Vector2f bulletScale) :
		Bullet(daamg, pos, dir, bulletSpeeed, penetration,nameImage, as, bulletScale) {
		if(bulletSpeeed!=0.f)
			bulletSpeed = bulletSpeeed;
		gunShotTotalDistance = totaldistance;
		isGunShot = true;
	}
	~BulletAuto() {
		
	}

	void updateEntity(float dt);



	void setAnimation(Animation e);
	void setSprite(std::string n) { Bullet::setSprite(n); }
	void setSprite(){}
	void setGunShotDistance(float distance) {
		gunShotTotalDistance = distance;
		isGunShot = true;
	}
	bool checkCollisions(Mob& b);
	void renderEntity(sf::RenderTarget& target);
	float getGunshotDistance() { return gunshotDistance; }
	float getGunshotTotalDistance() { return gunShotTotalDistance; }
};


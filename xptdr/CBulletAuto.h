#pragma once
#include"CBullet.h"
#include"CWeaponStat.h"
class CBulletAuto : public CBullet
{
private :
	CMob* mob = NULL;
	float gunshotDistance = 0.f;
	float gunShotTotalDistance;
public:
	bool isMobSet = false;
	bool isGunShot = false;
	bool isExplosive = false;
	bool isThisIt = false;
	sf::RectangleShape hitbox;
	CBulletAuto();
	CBulletAuto(CWeaponStat stat, CAssetManager* a);
	CBulletAuto(int damage, float bulletSpeed, sf::Vector2f dir,int penetration, std::string nameImage, sf::Vector2f bulletScale_, CAssetManager* a);

	//méthode classico classique
	CBulletAuto(int daamg, sf::Vector2f pos, float bulletSpeeed, sf::Vector2f dir,int penetration, std::string nameImage, CAssetManager* as, sf::Vector2f bulletScale) :
		CBullet(daamg, pos, dir, bulletSpeeed, penetration,nameImage, as, bulletScale) {
		if (bulletSpeeed != 0.f)
			bulletSpeed = bulletSpeeed;
		setRotation();
	}

	// méthode utilisée par les bombes ennemis
	CBulletAuto(int daamg, sf::Vector2f pos, float bulletSpeeed, sf::Vector2f dir, int penetration, std::string nameImage, CAssetManager* as, sf::Vector2f bulletScale, bool isABombe);

	//Méthode utilisée pour le gunshot
	CBulletAuto(int daamg, sf::Vector2f pos, sf::Vector2f dir,float bulletSpeeed, float totaldistance,int penetration, std::string nameImage, CAssetManager* as, sf::Vector2f bulletScale) :
		CBullet(daamg, pos, dir, bulletSpeeed, penetration,nameImage, as, bulletScale) {
		if(bulletSpeeed!=0.f)
			bulletSpeed = bulletSpeeed;
		gunShotTotalDistance = totaldistance;
		isGunShot = true;
		setRotation();
	}
	void setDirection(sf::Vector2f d)
	{
		direction = d;
	}
	void updateEntity(float dt);
	void setMob(CMob* m) {
		mob = m;
		isMobSet = true;
		setRotation();
	}
	void setRotation() {
	}

	void setSprite(std::string n) { CBullet::setSprite(n); }
	void setSprite(){}
	void setGunShotDistance(float distance) {
		gunShotTotalDistance = distance;
		isGunShot = true;
	}
	bool checkCollisions(CMob& b);
	void renderEntity(sf::RenderTarget& target);
};


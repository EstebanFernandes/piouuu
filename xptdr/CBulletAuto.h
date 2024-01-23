#pragma once
#include"CBullet.h"
#include"CMob.h"
class CBulletAuto : public CBullet
{
private :
	CMob* mob = NULL;
	float gunshotDistance = 0.f;
	float gunShotTotalDistance;
public:
	bool isMobSet = false;
	bool isGunShot = false;
	void setSprite() {
	}
	CBulletAuto();

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
	
	void updateEntity(float dt);
	void setMob(CMob* m) {
		mob = m;
		isMobSet = true;
		setRotation();
	}
	void setRotation() {
	}

};


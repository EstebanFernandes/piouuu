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
	CBulletAuto(int daamg, sf::Vector2f pos, float bulletSpeeed, sf::Vector2f dir,int penetration, std::string nameImage, CAssetManager* as) :
		CBullet(daamg, pos, dir,penetration,nameImage, as) {
		if (bulletSpeeed != 0.f)
			bulletSpeed = bulletSpeeed;
		setRotation();
	}

	//Méthode utilisée pour le gunshot
	CBulletAuto(int daamg, sf::Vector2f pos, sf::Vector2f dir,float bulletSpeeed, float totaldistance,int penetration, std::string nameImage, CAssetManager* as) :
		CBullet(daamg, pos, dir,penetration,nameImage, as) {
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


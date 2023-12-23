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
	CBulletAuto();
	CBulletAuto(int daamg, sf::Vector2f pos, CAssetManager* as) :
		CBullet(daamg,pos,sf::Vector2f(1.f,0.f),as){

	}
	CBulletAuto(int daamg, sf::Vector2f pos, sf::Vector2f dir, CAssetManager* as) :
		CBullet(daamg, pos, dir, as) {

	}
	CBulletAuto(int daamg, sf::Vector2f pos, sf::Vector2f dir,float totaldistance, CAssetManager* as) :
		CBullet(daamg, pos, dir, as) {
		gunShotTotalDistance = totaldistance;
		isGunShot = true;
	}
	CBulletAuto(int daamg, sf::Vector2f pos, float bulletSpeeed, sf::Vector2f dir, CAssetManager* as) :
		CBullet(daamg, pos, dir, as) {
		if (bulletSpeeed != 0.f)
			bulletSpeed = bulletSpeeed;
	}

	CBulletAuto(int daamg, sf::Vector2f pos, sf::Vector2f dir,float bulletSpeeed, float totaldistance, CAssetManager* as) :
		CBullet(daamg, pos, dir, as) {
		if(bulletSpeeed!=0.f)
			bulletSpeed = bulletSpeeed;
		gunShotTotalDistance = totaldistance;
		isGunShot = true;
	}
	//CBulletAuto(int damaage, sf::Vector2f pos, sf::Vector2f dir, float bS, float tDistance, CMob* playerPointer, CAssetManager* as);
	CBulletAuto(int damaage, sf::Vector2f pos, CMob* mobPosition, CAssetManager* assetss);
	CBulletAuto(int damaage, sf::Vector2f pos, CMob* mobPosition, float bulletSpeed, CAssetManager* assetss);
	void updateEntity(float dt);
	void setMob(CMob* m) {
		mob = m;
		isMobSet = true;
	}
};


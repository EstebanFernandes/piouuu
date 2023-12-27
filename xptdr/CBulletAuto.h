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
	CBulletAuto(int daamg, sf::Vector2f pos, std::string nameImage, CAssetManager* as) :
		CBullet(daamg,pos,sf::Vector2f(1.f,0.f),nameImage,as){
		setRotation();
	}
	CBulletAuto(int daamg, sf::Vector2f pos, sf::Vector2f dir, std::string nameImage, CAssetManager* as) :
		CBullet(daamg, pos, dir,nameImage, as) {
		setRotation();
	}
	CBulletAuto(int daamg, sf::Vector2f pos, sf::Vector2f dir,float totaldistance, std::string nameImage, CAssetManager* as) :
		CBullet(daamg, pos, dir,nameImage, as) {
		gunShotTotalDistance = totaldistance;
		isGunShot = true;
		setRotation();
	}

	//méthode classico classique
	CBulletAuto(int daamg, sf::Vector2f pos, float bulletSpeeed, sf::Vector2f dir, std::string nameImage, CAssetManager* as) :
		CBullet(daamg, pos, dir,nameImage, as) {
		if (bulletSpeeed != 0.f)
			bulletSpeed = bulletSpeeed;
		setRotation();
	}

	//Méthode utilisée pour le gunshot
	CBulletAuto(int daamg, sf::Vector2f pos, sf::Vector2f dir,float bulletSpeeed, float totaldistance, std::string nameImage, CAssetManager* as) :
		CBullet(daamg, pos, dir,nameImage, as) {
		if(bulletSpeeed!=0.f)
			bulletSpeed = bulletSpeeed;
		gunShotTotalDistance = totaldistance;
		isGunShot = true;
		setRotation();
	}
	//CBulletAuto(int damaage, sf::Vector2f pos, sf::Vector2f dir, float bS, float tDistance, CMob* playerPointer, CAssetManager* as);
	CBulletAuto(int damaage, sf::Vector2f pos, CMob* mobPosition, std::string nameImage, CAssetManager* assetss);
	CBulletAuto(int damaage, sf::Vector2f pos, CMob* mobPosition, float bulletSpeed, std::string nameImage, CAssetManager* assetss);
	void updateEntity(float dt);
	void setMob(CMob* m) {
		mob = m;
		isMobSet = true;
		setRotation();
	}
	void setRotation() {
	}
};


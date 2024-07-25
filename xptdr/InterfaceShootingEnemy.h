#pragma once
#include"bulletStorage.h"
class InterfaceShootingEnemy
{
protected:
	bulletStorage* bulletstorage;
	CGunslinger BAW;
	sf::Clock bulletClock;
public:

	void setBulletStorage(bulletStorage* e) {
		bulletstorage = e;
	}
	 virtual ~InterfaceShootingEnemy() { 
		std::cout << "interface destructor called !\n";
		transferBullet(BAW); 
	}
	void updateShootWithPlayer(CPlayer& player);
	void transferBullet(CGunslinger& r) { bulletstorage->saveBullets(r); }
	/*void setAttackSpeed(float attackSpeedParam) {
		BAW.getWeaponStats().attackSpeed = attackSpeedParam;
	}*/
};


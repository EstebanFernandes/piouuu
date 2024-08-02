#pragma once
#include"bulletStorage.h"
class InterfaceShootingEnemy
{
protected:
	bulletStorage* bulletstorage;
	Gunslinger BAW;
	sf::Clock bulletClock;
public:

	void setBulletStorage(bulletStorage* e) {
		bulletstorage = e;
	}
	 virtual ~InterfaceShootingEnemy() { 
		std::cout << "interface destructor called !\n";
		transferBullet(BAW); 
	}
	void updateShootWithPlayer(Player& player);
	void transferBullet(Gunslinger& r) { bulletstorage->saveBullets(r); }
	/*void setAttackSpeed(float attackSpeedParam) {
		BAW.getWeaponStats().attackSpeed = attackSpeedParam;
	}*/
};


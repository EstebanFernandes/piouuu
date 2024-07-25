#pragma once
#include"Weapon.h"
#include"LaserGenerator.h"
class laserWeapon : public Weapon
{
private:
	bool isActive = false;
	std::list<LaserGenerator> lasers;
	sf::Clock bulletClock2;
public:
	laserWeapon();
	laserWeapon(CAssetManager* assets);
	void changeActivity();
	void changeTarget(CMob* r);
	void traiterMisc(int misc);
	void addShootType(int type);
	int checkCollisions(CMob& b);
	void weaponControls(sf::Event);
	void weaponShoot();
	void updateWeapon(float dt);
	void renderWeapon(sf::RenderTarget& target);
	void setBulletAsset(std::string assetName);
	std::string getBulletAsset();
};


#pragma once
#include"LaserGenerator.h"
class laserWeapon : public Weapon
{
private:
	bool isActive = false;
	std::list<LaserGenerator> lasers;
	sf::Clock bulletClock2;
public:
	laserWeapon();
	laserWeapon(AssetManager* assets);
	void changeActivity();
	void changeTarget(Mob* r);
	void traiterMisc(int misc);
	void addShootType(int type);
	int checkCollisions(Mob& b);
	void weaponControls(sf::Event);
	void weaponShoot();
	void updateWeapon(float dt);
	void renderWeapon(sf::RenderTarget& target);
	void setBulletAsset(std::string assetName);
	std::string getBulletAsset();
};


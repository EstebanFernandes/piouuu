#pragma once

#include "CAssetManager.h"

class Weapon
{
private:
	int typeArme = -1;
	sf::Vector2f weaponPos;
public:
	typedef enum {
		gunslinger = 0,
		laser = 1
	}typesArme;
	CAssetManager* assets;
	void setTypeArme(int type);
	int getTypeArme();

	virtual void updateWeapon(float dt) = 0;
	virtual void renderWeapon(sf::RenderTarget& target) = 0;
	virtual void setBulletAsset(std::string assetName) = 0;
};


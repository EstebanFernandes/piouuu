#pragma once

#include "CAssetManager.h"

class Weapon
{
protected:
	int typeArme = -1;
	/// <summary>
	/// d�finit le d�calage entre la position du joueur et l'endroit o� l'on doit tirer
	/// </summary>
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
	/// <summary>
	/// D�fini la position relative de l'arme par rapport au centre de l'arme
	/// </summary>
	/// <param name="pos"></param>
	void setWeaponPos(sf::Vector2f pos) { weaponPos = pos; }
};


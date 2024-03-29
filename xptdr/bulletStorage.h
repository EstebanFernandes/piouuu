#pragma once
#include"CEnemy.h"
/// <summary>
/// Enemy sp�cial qui r�colte les balles laiss�es par les ennemis tu�s
/// </summary>
class bulletStorage : public CEnemy
{
	CGunslinger saveBullet;
public:
	bulletStorage(){}
	bulletStorage(CAssetManager* a) {
		saveBullet.assets = a;
	}
	void updateMovement(float delta){}
	void enemyShoot(){}
	void updatewPlayer(float delta, CPlayer& player);
	void updateEntity(float delta) { saveBullet.updateWeapon(delta); }
	void renderEntity(sf::RenderTarget& target) { saveBullet.renderWeapon(target); }
	void saveBullets(CGunslinger& otherGunslinger);
	CEnemy* clone() override {
		return new bulletStorage(*this);
	}
};


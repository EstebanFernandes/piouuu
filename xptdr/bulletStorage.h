#pragma once
#include"CEnemy.h"
/// <summary>
/// Enemy spécial qui récolte les balles laissées par les ennemis tués
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
	void updateEntity(float delta) { saveBullet.updateEntity(delta); }
	void renderEntity(sf::RenderTarget& target) { saveBullet.renderEntity(target); }
	void saveBullets(CGunslinger& otherGunslinger);
};


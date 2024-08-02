#pragma once
#include"Enemy.h"
/// <summary>
/// Enemy spécial qui récolte les balles laissées par les ennemis tués
/// </summary>
class bulletStorage : public Enemy
{

	Gunslinger saveBullet;
public:
	bulletStorage(){}
	bulletStorage(AssetManager* a) {
		saveBullet.assets = a;
	}
	void updateMovement(float delta){}
	void enemyShoot(){}
	void updatewPlayer(float delta, Player& player);
	void updateEntity(float delta) { saveBullet.updateWeapon(delta); }
	void renderEntity(sf::RenderTarget& target) { saveBullet.renderWeapon(target); }
	void saveBullets(Gunslinger& otherGunslinger);
	Enemy* clone() override {
		return new bulletStorage(*this);
	}
};


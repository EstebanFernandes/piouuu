#pragma once
#include"Enemy.h"
/// <summary>
/// Enemy sp�cial qui r�colte les balles laiss�es par les ennemis tu�s
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


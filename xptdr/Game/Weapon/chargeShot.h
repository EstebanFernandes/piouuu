#pragma once
#include"Gunslinger.h"
class chargeShot : public Gunslinger
{
private:
	sf::Clock chargeClock;
	float maxChargedTime = 0.5f;
	float maxPlusScaleFactor = 2.5f;
	BulletAuto chargingBall;
	bool isCharging;

	void sendBullet();
public:
	chargeShot(AssetManager* asset);
	void weaponControls(sf::Event event);
	void updateWeapon(float dt);
	void renderWeapon(sf::RenderTarget& target);
};


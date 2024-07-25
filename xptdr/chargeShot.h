#pragma once
#include"CGunslinger.h"
class chargeShot : public CGunslinger
{
private:
	sf::Clock chargeClock;
	float maxChargedTime = 0.5f;
	float maxPlusScaleFactor = 2.5f;
	CBulletAuto chargingBall;
	bool isCharging;

	void sendBullet();
public:
	chargeShot(CAssetManager* asset);
	void weaponControls(sf::Event event);
	void updateWeapon(float dt);
	void renderWeapon(sf::RenderTarget& target);
};


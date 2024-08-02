#include "Gunshot.h"

Gunshot::Gunshot(AssetManager* asset)
	:Gunslinger()
{
	assets = asset;
}

void Gunshot::updateWeapon(float dt)
{
	if (wantToShoot == true)
		weaponShoot();
	for (Bullet* bullet : bullets) {
		bullet->updateEntity(dt);
		if (bullet->getDistance() >= referenceStat.maxDistance || bullet->checkGlobalCollisions())
			bullet->needDelete = true;
		if (bullet->needDelete)
		{
			delete bullet;
		}
	}
	updateAngle();
}

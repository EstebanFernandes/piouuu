#include "WeaponHandler.h"

void WeaponHandler::setNewWeapon(Weapon* replacement, bool isFirstTime)
{
	if (!isFirstTime && &weapon != nullptr)
	{
		std::string bulletAssets = weapon->getBulletAsset();
		sf::Keyboard::Key t = weapon->getTouche();
		WeaponStat a = weapon->getWeaponStats();
		delete (weapon);
		replacement->setWeaponStats(a);
		replacement->setBulletAsset(bulletAssets);
		replacement->setTouche(t);
	}
	weapon = replacement;
	weapon->assets = assets;
	assets->addSFX("bulletSound", &(weapon->bulletSound));
	weapon->pointerToPlayer = pointerToMob;
	weapon->setAimBoolean(&seekForTarget);
	weapon->setPointerToOnHitEffect(&effetOnHit);
	weapon->setWeaponStats()
}

void WeaponHandler::traitermisc(std::string misc)
{
	std::vector < std::string> listeArme = {"Gunslinger", "Chargeshot", "Laser", "Gunshot"};
}

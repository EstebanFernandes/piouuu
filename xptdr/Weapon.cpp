#include "Weapon.h"

Weapon::~Weapon()
{
	//assets->deleteSound(&bulletSound);
}

sf::Vector2f Weapon::getWeaponPos()
{
	return weaponPos;
}

void Weapon::setWeaponPos(sf::Vector2f posParam)
{
	weaponPos = posParam;
}

void Weapon::setTypeArme(int type)
{
	if (type == gunslinger || type == laser) {
		typeArme = type;
	}
}

int Weapon::getTypeArme()
{
	return typeArme;
}

CWeaponStat& Weapon::getWeaponStats()
{
	return referenceStat;
}

void Weapon::setWeaponStats(CWeaponStat statsParam)
{
	referenceStat = statsParam;
}

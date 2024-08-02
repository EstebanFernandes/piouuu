#include "Weapon.h"
#include <bitset>

void Weapon::updateAngle()
{
	if (angleClock.getElapsedTime().asSeconds() >= 0.05f && typeTir == typeAim::Spin)
	{
		angleClock.restart();
		if (angleOffset != 359.f)
		{
			angleOffset++;
		}
		else
			angleOffset = 0;

	}
}

Weapon::~Weapon()
{
	if(bulletSound!=NULL)
		assets->deleteSound(bulletSound);
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

void Weapon::addBulletType(int type)
{
	if (type >= 0 && type <= nbBullet - 1)
	{
		std::bitset<nbBullet> bit = std::bitset<nbBullet>(typeBalle);
		if (bit[type] == 0)
		{
			typeBalle += (int)pow(2, type);
		}
		else
			std::cout << "amélioration déjà mise\n";
	}
}

WeaponStat& Weapon::getWeaponStats()
{
	return referenceStat;
}

void Weapon::setWeaponStats(WeaponStat statsParam)
{
	referenceStat = statsParam;
}

std::vector<effetspecial*>& Weapon::getEffect()
{
	std::vector<effetspecial*> res;
	for (int i = 0; i < effetOnHit.size(); i++)
	{
		res.push_back(effetOnHit[i]->clone());
	}
	return res;
}

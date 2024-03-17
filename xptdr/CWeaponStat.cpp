#include "CWeaponStat.h"

CWeaponStat::CWeaponStat()
{
	bulletDamage = 0.f;
	bulletSpeed = 0.f;
	penetration = 0;
	dotDamage = 0.f;
	dotCD = 0.f;
	dotTimer=0.f;
	bulletScale = sf::Vector2f(1.f, 1.f);
}

CWeaponStat::CWeaponStat(float bulletDamage_, float bulletSpeed_, sf::Vector2f dir_, unsigned int penetration_, std::string nameImage_, sf::Vector2f bulletScale_, float attackSpeedParam)
{
	bulletDamage = bulletDamage_;
	bulletSpeed = bulletSpeed_;
	dir = dir_;
	penetration = penetration_;
	nameImage = nameImage_;
	bulletScale = bulletScale_;
	attackSpeed = attackSpeedParam;
}

void CWeaponStat::paramDot(float dotDamage_, float dotCD_, float dotTimer_)
{
	dotDamage = dotDamage_;
	dotCD = dotCD_;
	dotTimer = dotTimer_;
}

void CWeaponStat::addDir(sf::Vector2f& dir_)
{
	dir2.push_back(dir_);
}

void CWeaponStat::changeDir(sf::Vector2f& dir, int index)
{
	if (index == 0)
		this->dir = dir;
		dir2[index] = dir;
}

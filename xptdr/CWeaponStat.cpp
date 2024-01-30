#include "CWeaponStat.h"

CWeaponStat::CWeaponStat()
{
	bulletDamage = 0.f;
	bulletSpeed = 0.f;
	penetration = 0;
	dotDamage = 0.f;
	dotCD = 0.f;
	dotTimer=0.f;
}

CWeaponStat::CWeaponStat(float bulletDamage_, float bulletSpeed_, sf::Vector2f dir_, unsigned int penetration_, std::string nameImage_, sf::Vector2f bulletScale_)
{
	bulletDamage = bulletDamage_;
	bulletSpeed = bulletSpeed_;
	dir = dir_;
	penetration = penetration_;
	nameImage = nameImage_;
	bulletScale = bulletScale_;
}

void CWeaponStat::paramDot(float dotDamage_, float dotCD_, float dotTimer_)
{
	dotDamage = dotDamage_;
	dotCD = dotCD_;
	dotTimer = dotTimer_;
}

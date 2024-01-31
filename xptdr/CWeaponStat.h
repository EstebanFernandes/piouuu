#pragma once
#include"SFML/Graphics.hpp"
/// <summary>
/// Classe qui représente les stats offensive d'une unité
/// </summary>
class CWeaponStat
{
public:
	float bulletDamage;
	float bulletSpeed;
	sf::Vector2f dir;
	unsigned int penetration;
	std::string nameImage;
	sf::Vector2f bulletScale;
	float maxDistance = -1;
	float dotDamage;
	float dotCD;
	float dotTimer;
	float attackSpeed = 1.f;
	CWeaponStat();
	CWeaponStat(float bulletDamage_, float bulletSpeed_, sf::Vector2f dir_, unsigned int penetration_, std::string nameImage_, sf::Vector2f bulletScale_, float attackSpeedParam);
	void paramDot(float dotDamage_, float dotCD_, float dotTimer_);
};


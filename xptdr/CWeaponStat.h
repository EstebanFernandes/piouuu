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
	sf::Vector2f dir= sf::Vector2f(0.f,0.f);
	//Stock les directions de l'arme (pour les armes qui tire plusieurs fois)
	std::vector<sf::Vector2f> dir2;
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
	void addDir(sf::Vector2f& dir);
	void changeDir(sf::Vector2f& dir, int index = 0);
};


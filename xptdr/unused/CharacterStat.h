#pragma once
//On va copier lol parce que c'est plus simple de faire comme ça vis à vis du parser etc.
//Cette classe sert à regrouper toutes les statistiques sur un personnage.
class CCharacterStat
{
private:
	int level;
	int xp;
	int maxXp;
	int healthPoint;
	float damagePerBullet;
	float canonNumber;
	float attackSpeed;
	float bulletSpeed;
};


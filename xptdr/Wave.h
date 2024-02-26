#pragma once
#include<vector>
#include"CEnemy.h"
/// <summary>
/// Classe qui gère
/// </summary>

struct enemy{
	CEnemy* enemy;
	float spawnerTiming;
};
class Wave
{
private:
	float duration;
	bool needDelete = false;
	bool notTimeDep;
	//Entier qui définit le nombre d'ennemi restant dans cette wave
public:
	std::vector<enemy> enemyList;
	Wave();
	Wave(float duration_);
	float getDuration() { return duration; }
	bool updateWave(float clock, std::vector<CHittingEntity*>* ennemyList);
	void checkEntity();
	void addEnemy(enemy& enemyToAdd) { enemyList.push_back(enemyToAdd);}
};

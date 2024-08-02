#pragma once
#include"Wave.h"
#include <string>
class Pattern
{
private:
	float clockOffset;
	float duration;
	int order;
	std::string nameOfPattern;
	std::vector<Wave> waveList;
	std::vector<Wave> waveListStock;
	bool isRandom = false;
	bool notTimeDep;//Le pattern ne dépend pas du temps
	unsigned int difficulty = 1;
public:
	void startPattern();
	bool updatePattern(float clock, std::vector<HittingEntity*>* ennemyList);
	Pattern(float duration_, int order_, std::string name, bool isRandom_);
	//2 méthodes utilisées pour stockés les waves dans le pattern
	void addWave(Wave& waveToAdd) { waveListStock.push_back(waveToAdd); }
	void addEnemy(enemy& enemyToAdd) { 
		waveListStock.back().addEnemy(enemyToAdd); 
	}
	float getDuration() { return duration; }
	int getWaveSize() { return (int)waveList.size(); }
	int getOrder() { return order; }
	Wave* getCurrentWave() { return &waveList[0]; }
	std::string getName() { return nameOfPattern; }
	unsigned int getDifficulty() { return difficulty; }
	void setDifficulty(unsigned int diffucultyParam) { difficulty = diffucultyParam; }
};


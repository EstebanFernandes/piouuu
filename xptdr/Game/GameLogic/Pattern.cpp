#include "Pattern.h"


void Pattern::startPattern()
{
	waveList = waveListStock;
	for (int i = 0; i < waveList.size(); i++)
	{
		for (int j = 0; j < waveList[i].enemyList.size(); j++)
		{
			waveList[i].enemyList[j].enemy = waveList[i].enemyList[j].enemy->clone();
		}
	}
}

bool Pattern::updatePattern(float clock, std::vector<HittingEntity*>* ennemyList)
{
	if (duration > clock||notTimeDep==true) //Cas normal, on ne dépend pas du tout ou le temps n'a pas été atteint
	{
		Wave& wave = waveList[0];
		if(wave.updateWave(clock - clockOffset, ennemyList) == true)
		{
			if (!wave.enemyList.empty())
			{
				for (int i = 0; i < wave.enemyList.size(); i++)
				{
					wave.enemyList[i].spawnerTiming = -1.f;
				}
			}
			waveList.erase(waveList.begin());
			clockOffset += clock;
			
			if (waveList.size() == 0)
				return true;
			return false;
		}
	return false;
	}
	else 
	{
		return true;
	}

}

Pattern::Pattern(float duration_, int order_, std::string name, bool isRandom_)
	:duration(duration_), order(order_), nameOfPattern(name), isRandom(isRandom_)
{
	if (duration == -1)
		notTimeDep = true;
	else
		notTimeDep = false;
	clockOffset = 0.f;

}

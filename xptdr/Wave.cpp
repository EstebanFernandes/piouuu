#include "Wave.h"

Wave::Wave()
{
	duration = -1.f;
	notTimeDep = true;
}

Wave::Wave(float duration_)
	:duration(duration_)
{
	if (duration == -1.f)
	{
		notTimeDep = true;
	}
	else
		notTimeDep = false;
}

bool Wave::updateWave(float clock, std::vector<CHittingEntity*>* ennemyList)
{
	if (duration >= clock || notTimeDep == true)
	{
		if (enemyList.size() == 0)
			return true;
		int temp = (int)enemyList.size();
		for (int i = 0; i < temp; i++)
		{
			if (enemyList[i].spawnerTiming <= clock && enemyList[i].spawnerTiming >= 0.f)
			{
				ennemyList->push_back(enemyList[i].enemy);
				enemyList[i].spawnerTiming = -0.5f;
			}
		}
		return false;
	}
	else if (duration <= clock)
	{
		return true;
	}
}

void Wave::checkEntity()
{
	int temp = (int)enemyList.size();
	for (int i = 0; i < temp; i++)
	{
			if (enemyList[i].enemy->needDelete == true)
			{
			enemyList.erase(enemyList.begin() + i);
			i--;
			temp--;
			}
	}
}

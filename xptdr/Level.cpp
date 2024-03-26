#include "Level.h"

bool Level::updateLevel()
{
	Pattern& pat = patternList[0];
	if (patternList.size() == 1 && isInfinite==true)
	{//Si la liste des pattern est quasiment vide
		if (!isRandom)
		{
			int index = pat.getOrder();
			if (pat.getOrder() == patternListStock.size())
				index = 0;
			patternList.push_back(patternListStock[index]);
		}
		else {
			int min = 0;
			int max = (int)patternListStock.size()-1;
			patternList.push_back(patternListStock[min + std::rand() % (max - min + 1)]);
		}
	}
	// Pour que ça fonctionne en release mdrr
	//pat = patternList.at(0);
		if(pat.updatePattern(*clock - offset, ennemyList) == true)
		{
			patternList.erase(patternList.begin());
			offset = *clock;
			std::cout << "Off set de la clock du niveau : " << offset << std::endl;
			std::cout << "Nom du niveau = " << patternList.begin()->getName() << std::endl;
			if (patternList.size() == 0)
				return true;
			patternList[0].startPattern();
		}
	if (patternList.size() == 0 && isInfinite == false)
		return true;

	return false;
}

void Level::deleteEnemy(CHittingEntity* entity)
{
		patternList[0].getCurrentWave()->checkEntity();
}

void Level::startLevel()
{
	patternList = patternListStock;
	patternList[0].startPattern();
}

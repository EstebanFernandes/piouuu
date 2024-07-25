#include "Level.h"

bool Level::updateLevel()
{
	// On vérifie si il est temps de changer de difficulté
	if (difficultClock.getElapsedTime().asSeconds() > nextDifficultyClock && !maxDifficultyReached) {
		std::cout << "je change de difficulté ! " << std::endl;
		changeDifficulty();
	} 
	if (patternList.size() <= 1 && isInfinite==true)
	{//Si la liste des pattern est quasiment vide
			// On prend un niveau aléatoirement parmi la range de difficulté
		int min = 0;
		int max = (int)patternListStock.size()-1;
		patternList.push_back(patternListStock[min + std::rand() % (max - min + 1)]);
	}
	// Pour que ça fonctionne en release mdrr
	Pattern& pat = patternList.at(0);
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
	if (isInfinite) {
		if (totalPatternNumber <= 3) {
			maxDifficultyReached = true;
		}
		else {
			patternListStock = getPatternsOfDifficulties(1, 1);
			if (patternListStock.size() < 3 && !maxDifficultyReached) {
				changeDifficulty();
			}
		}
	}
	patternList = patternListStock;
	patternList[0].startPattern();
}

std::vector<Pattern> Level::getPatternsOfDifficulties(int min, int max)
{
	if (min > max) {
		throw (std::exception("Bornes non valides"));
	}
	std::vector<Pattern> patternList;
	for (int i = min; i <= max; i++) {
		try {
			std::vector<Pattern> patternsToAdd = patternsPerDifficulty.at(i);
			patternList.insert(std::end(patternList), std::begin(patternsToAdd), std::end(patternsToAdd));;
		}
		catch (std::exception) {
			std::cout << "pas de difficulte " << i << std::endl;
		}
	}
	return patternList;
}

void Level::changeDifficulty()
{
	if (actualMaxDiff != maxDifficultyPattern) {
		int countMax = 1;
		std::vector<Pattern> newCollection = getPatternsOfDifficulties(actualMinDiff, actualMaxDiff + countMax);
		while (newCollection.size() < 3 && actualMaxDiff+countMax != maxDifficultyPattern) {
			newCollection = getPatternsOfDifficulties(actualMinDiff, actualMaxDiff + countMax);
			countMax += 1;
		}
		newCollection = getPatternsOfDifficulties(actualMinDiff + 1, actualMaxDiff + countMax);
		if (newCollection.size() >= 3 && actualMaxDiff != 1) {
			// On change la difficulté minimum
			actualMinDiff += 1;
		}
		else {
			newCollection = getPatternsOfDifficulties(actualMinDiff, actualMaxDiff + countMax);
		}
		actualMaxDiff += countMax;

		if (newCollection.size() < 3 && actualMaxDiff == maxDifficultyPattern) {
			throw(std::exception());
		}
		// On update la liste des patterns
		patternListStock = getPatternsOfDifficulties(actualMinDiff, actualMaxDiff);
		difficultClock.restart();
	}
	else if (actualMinDiff != maxDifficultyPattern - 1) {
		std::vector<Pattern> newCollection = getPatternsOfDifficulties(actualMinDiff + 1, actualMaxDiff);
		if (newCollection.size() >= 3) {
			actualMinDiff += 1;
			// On update la liste des patterns
			patternListStock = newCollection;
			difficultClock.restart();
		}
		else {
			maxDifficultyReached = true;
		}
	}
	else {
		maxDifficultyReached = true;
	}
}

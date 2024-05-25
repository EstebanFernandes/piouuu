#pragma once
#include"Pattern.h"
/// <summary>
/// Cette classe représente un niveau, soit une succesion de patternes et de vagues d'ennemis.
/// Le remplissage de cette classe se fait selon un fichier XML, donc on ajoute au mur et à fesure
/// 
/// </summary>

class Level
{
private:
	std::string name ="";
	std::vector<Pattern> patternListStock;
	std::vector<Pattern> patternList;
	float* clock;
	float offset = 0.f;
	std::vector<CHittingEntity*>* ennemyList;
	bool isRandom = false;
	/// <summary>
	/// Asset nécessaire pour ce niveau, ils sont stockés en une string séparé d'un tiret
	/// </summary>
	std::vector<std::string> assets;
public:

	/// <summary>
	/// Borne minimum de la difficulté
	/// </summary>
	unsigned int actualMinDiff = 1;
	/// <summary>
	/// Borne maximum de la difficulté
	/// </summary>
	unsigned int actualMaxDiff = 1;
	/// <summary>
	/// variable stockant la valeure maximale des difficultés des patterns
	/// </summary>
	unsigned int maxDifficultyPattern;

	unsigned int totalPatternNumber = 0;

	bool maxDifficultyReached = false;

	/// <summary>
	/// map permettant de répertorier les patterns par leur difficulté
	/// </summary>
	std::map<unsigned int, std::vector<Pattern>> patternsPerDifficulty;

	sf::Clock difficultClock;

	/// <summary>
	/// temps entre deux augmentations de difficultés
	/// </summary>
	float nextDifficultyClock;

	bool isLevelSet = false;
	bool isInfinite = false;
	Level() {}
	//Cette méthode suppose que l'on a passé la clock, sinon ça plante
	bool updateLevel();
	/// <summary>
	/// Cette méthode supprime un ennemi et on regarde avant qu'il soit sur la wave en cours ou pas
	/// </summary>
	/// <param name="it"></param>
	void deleteEnemy(CHittingEntity* entity);
	void startLevel();
	//Getter et setter
	void setEnnemyList(std::vector<CHittingEntity*>* ennemyList_) { ennemyList = ennemyList_; }
	void setClock(float* pointerToclock) { clock = pointerToclock; }
	void setName(std::string n) { name = n; }
	std::string getName() { return name; }
	void addAsset(std::string& assetToAdd) { assets.push_back(assetToAdd); }
	void addPattern(Pattern& patternToAdd) 
	{ 
		patternListStock.push_back(patternToAdd);
	}
	void setRandom(int i) { isRandom = i; }
	void addWave(Wave& wavetoAdd) { patternListStock.back().addWave(wavetoAdd); }
	void addEnemy(enemy& enemyToAdd) { 
		patternListStock.back().addEnemy(enemyToAdd); }
	std::vector<Pattern> getPatterns() { return patternList; }
	std::vector<Pattern> getPatternStock() { return patternListStock; }
	/// <summary>
	/// Renvoie tous les patterns des difficultés comprises entre min et max (min < max)
	/// </summary>
	/// <param name="min">Borne minimum</param>
	/// <param name="max">Borne maximum</param>
	/// <returns></returns>
	std::vector<Pattern> getPatternsOfDifficulties(int min, int max);
	/// <summary>
	/// Augmente la difficulté tout en gardant au minimum 3 patterns dans le stock
	/// </summary>
	void changeDifficulty();
};
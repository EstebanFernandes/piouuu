#pragma once
#include"Pattern.h"
/// <summary>
/// Cette classe repr�sente un niveau, soit une succesion de patternes et de vagues d'ennemis.
/// Le remplissage de cette classe se fait selon un fichier XML, donc on ajoute au mur et � fesure
/// 
/// </summary>

class Level
{
private:
	std::string name;
	std::vector<Pattern> patternListStock;
	std::vector<Pattern> patternList;
	float* clock;
	float offset = 0.f;
	std::vector<CHittingEntity*>* ennemyList;
	bool isRandom = false;
	/// <summary>
	/// Asset n�cessaire pour ce niveau, ils sont stock�s en une string s�par� d'un tiret
	/// </summary>
	std::vector<std::string> assets;
public:
	bool isInfinite = false;
	Level() {}
	//Cette m�thode suppose que l'on a pass� la clock, sinon �a plante
	bool updateLevel();
	/// <summary>
	/// Cette m�thode supprime un ennemi et on regarde avant qu'il soit sur la wave en cours ou pas
	/// </summary>
	/// <param name="it"></param>
	void deleteEnemy(CHittingEntity* entity);
	void startLevel();
	//Getter et setter
	void setEnnemyList(std::vector<CHittingEntity*>* ennemyList_) { ennemyList = ennemyList_; }
	void setClock(float* pointerToclock) { clock = pointerToclock; }
	void setName(std::string n) { name = n; }
	void addAsset(std::string& assetToAdd) { assets.push_back(assetToAdd); }
	void addPattern(Pattern& patternToAdd) 
	{ 
		patternListStock.push_back(patternToAdd);
	}
	void setRandom(int i) { isRandom = i; }
	void addWave(Wave& wavetoAdd) { patternListStock.back().addWave(wavetoAdd); }
	void addEnemy(enemy& enemyToAdd) { 
		patternListStock.back().addEnemy(enemyToAdd); }
};
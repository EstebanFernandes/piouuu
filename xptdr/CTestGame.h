#pragma once
#include"CGameState.h"
#include"bulletStorage.h"
#include"CGrapheUpdate.h"
class CTestGame : public CGameState
{
private:
	std::vector<CGrapheUpdate> Upgradegraphs;
	//std::vector<CBulletAuto*> persistant;
	int currentLevelOfplayer = 0;
	bool isThistheEnd = false;
	bool hasLevelUp = false;
	bulletStorage bulletstorage;
	/// <summary>
	/// Possibilities :
	///	 -roaming, a standard enemy
	///	 -shooter, an enemy with a big GUN PIOU PIOU
	/// - bomber, a bomber man
	/// - bomberInverse, a bomberman, mon cousin félix who start to the oposite side
	/// - rusher, a quick guy			qu'est-ce qu'ils sont beaux
	///	 -boss, first prototype of a boss
	/// </summary>
	void addEnemy(std::string enemyName);
public:

	CTestGame(GameDataRef _data); 
	CTestGame(GameDataRef _data, CCharacter characterParam);

	void STEInit();
	void initAssets();
	void STEHandleInput();
	void STEUpdate(float delta);
	void addPowerUp();
	void STEDraw(float delta);
	void GameOver();
	void STEResume();
	void STEPause();
};


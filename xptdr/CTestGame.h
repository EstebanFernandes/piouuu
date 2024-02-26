#pragma once
#include"CGameState.h"
#include"bulletStorage.h"
#include"CGrapheUpdate.h"
class CTestGame : public CGameState
{
private:
	/// <summary>
	/// Possibilities :
	///	 -roaming, a standard enemy
	///	 -shooter, an enemy with a big GUN PIOU PIOU
	/// - bomber, a bomber man
	/// - bomberInverse, a bomberman, mon cousin félix who start to the oposite side
	/// - rusher, a quick guy			qu'est-ce qu'ils sont beaux
	///	 -boss, first prototype of a boss
	/// </summary>
public:

	CTestGame(GameDataRef _data); 
	CTestGame(GameDataRef _data, CCharacter characterParam);

	void STEInit();
	void initAssets();
	void STEHandleInput();

	void addPowerUp();
	void GameOver();
	void STEUpdate(float delta);
};


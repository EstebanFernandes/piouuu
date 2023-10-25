#pragma once
#include "CState.h"
#include <string>
#include "CJeu.h"
//état qui gère les améliorations du joueur 1
class CUpgradeState : public CState
{
private:
	GameDataRef data;
public:
	CUpgradeState(GameDataRef d);
	void STEInit(); 
	void STEUpdate(float delta);
	void STEDraw(float delta);
};


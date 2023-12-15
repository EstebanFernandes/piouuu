#pragma once

#include "CEnemy.h"
#include "CGameState.h"

class Boss : public CEnemy
{
private:
	CGameState* gameState;
public:
	Boss(CGameState& stateParam);

	//définition de méthodes virtuelles

	void updateMovement(float delta);
	void enemyShoot() {};
};


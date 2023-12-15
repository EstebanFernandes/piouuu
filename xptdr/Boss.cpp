#include "Boss.h"

Boss::Boss(CGameState& stateParam)
{
	gameState = &stateParam;
	//initEnnemy(gameState->getData())
}

void Boss::updateMovement(float delta)
{
}

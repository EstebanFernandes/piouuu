#pragma once
#include "CPlayer.h"
#include "CEntity.h"
//entit� qui doivent rentrer en collision avec le joueur.
class CHittingEntity : public CEntity
{
public:
	virtual void updatewPlayer(float delta, CPlayer& player)=0;
};


#pragma once
#include "CPlayer.h"
//entit� qui doivent rentrer en collision avec le joueur.
class CHittingEntity : public CMob
{
public:
	CHittingEntity(){}
	//Cette m�thode est � appeler sur chaque entit� qui rentre en contact avec le joueur
	virtual void updatewPlayer(float delta, CPlayer& player)=0;
};


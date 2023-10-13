#pragma once
#include "CPlayer.h"
//entité qui doivent rentrer en collision avec le joueur.
class CHittingEntity : public CMob
{
public:
	CHittingEntity(){}
	//Cette méthode est à appeler sur chaque entité qui rentre en contact avec le joueur
	virtual void updatewPlayer(float delta, CPlayer& player)=0;
};


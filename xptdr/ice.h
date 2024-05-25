#pragma once
#include"effetspecial.h"
class ice : public effetspecial
{
private:
	float baseMS;
	float baseAS;
	bool hasBeenApplied;
	float factor;
	sf::Color baseColor;
public:
	ice(CMob* targetparam, float duration, float factor);
	void update(float delta);
	void action();
	//Méthode qui remet les stats de base au personnage
	void retrieveBasisStat();
	effetspecial* clone() const override { return new ice(*this); }
};


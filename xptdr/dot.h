#pragma once
#include"effetspecial.h"
class dot : public effetspecial
{
private:
	float timer;
	float damage;
public:
	dot(CCharacter* targetparam, float damage, float timer,float duration);
	void update(float delta);
	void action();
	effetspecial* clone() const override { return new dot(*this); }
};


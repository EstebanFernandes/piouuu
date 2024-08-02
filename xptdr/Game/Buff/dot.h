#pragma once
#include"effetspecial.h"
class dot : public effetspecial
{
protected:
	float timer;
	float damage;
public:
	dot(Mob* targetparam, float damage, float timer,float duration);
	dot(int type_) :effetspecial(type_)
	{
	}
	void update(float delta);
	void action();
	effetspecial* clone() const override { return new dot(*this); }
};


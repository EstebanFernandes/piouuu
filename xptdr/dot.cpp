#include "dot.h"

dot::dot(CCharacter* targetparam, float damage, float timer, float duration)
{
	target = targetparam;
	this->damage = damage;
	this->timer = timer;
	this->duration = duration;
	clock.restart();
}

void dot::update(float delta)
{
	float clockTimer = clock.getElapsedTime().asSeconds();
	if (clockTimer >= timer && current+clockTimer <= duration)
	{
		clock.restart();
		current += clockTimer;
		action();
	}
	else if (current + clockTimer >= duration)
		needDelete = true;
}

void dot::action()
{
		float newHP = target->getLifePoint() - damage;
		target->setLifePoint(newHP);
}

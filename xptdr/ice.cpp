#include "ice.h"

ice::ice(CMob* targetparam, float duration,float factor)
	: effetspecial(typeEffet::ice)
{
	target = targetparam;
	this->duration = duration;
	clock.restart();
	hasBeenApplied = false;
	this->factor = factor;
}

void ice::update(float delta)
{
	if (clock.getElapsedTime().asSeconds() >= duration)
	{
		needDelete = true;
		retrieveBasisStat();
	}
}

void ice::action()
{
	if (!hasBeenApplied&&target!=NULL)
	{
		baseAS = target->getAttackSpeed();
		baseMS = target->getMoveSpeed();
		baseColor = target->getBaseColor();
		target->setAttackSpeed(baseAS * factor);
		target->setMoveSpeed(baseMS * factor);
		target->setBaseColor(sf::Color(128,186,241));
		hasBeenApplied = true;
	}
}

void ice::retrieveBasisStat()
{
	target->setAttackSpeed(baseAS );
	target->setMoveSpeed(baseMS);
	target->setBaseColor(baseColor);
}

#pragma once
#include"SFML/Graphics.hpp"
#include"../Mob.h"


class effetspecial 
{
protected:
	enum typeEffet
	{
		null,
		dot,
		fire,
		ice,
		thunder
	};
	Mob* target;
	float duration;
	float current=0.f;
	sf::Clock clock;
public:
	const int type = null;
	bool hasGlobal=false;
	bool needDelete = false;
	bool hasSprite = false;
	virtual void update(float delta) = 0;
	virtual void action()=0;
	virtual effetspecial* clone() const = 0;
	virtual void changeTarget(Mob* newTarget) { target = newTarget; }
	void resetClock() {
		clock.restart();
	}
	effetspecial(int type_)
		:type(type_)
	{
	}
	virtual void renderBuff(sf::RenderTarget& target){}
	virtual void globalMethod(std::vector<Mob*>& entityList){}
};


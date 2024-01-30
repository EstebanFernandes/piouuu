#pragma once
#include"SFML/Graphics.hpp"
#include"CCharacter.h"
class effetspecial 
{
protected:
	CCharacter* target;
	float duration;
	float current=0.f;
	sf::Clock clock;
public:
	bool needDelete = false;
	virtual void update(float delta) = 0;
	virtual void action()=0;
	void changeTarget(CCharacter* newTarget) { target = newTarget; }
	void resetClock() {
		clock.restart();
	}
};


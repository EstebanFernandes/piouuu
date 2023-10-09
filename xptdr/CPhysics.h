#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class CPhysics
{
private:
	//Attributs
	sf::Vector2f velocity;
	float acceleration;
	float drag;
	float velocityMax;
	float velocityMin;
	float velocityMaxY;
	float gravity;
public:
	//Constructeurs et destructeurs
	CPhysics();
	void initPhysics();
	void move(const float dir_x, const float dir_y);
	sf::Vector2f updatePhysics();
	void resetVelocityY();
	void resetVelocityX() { velocity.x = 0.f; }
	float getvelocityX();
	float getvelocityY() {
		return velocity.y;
	}
};


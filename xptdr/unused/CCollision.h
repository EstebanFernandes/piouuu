#pragma once
#include<SFML/Graphics.hpp>
//Interface qui permet de check les collisions
//PLUS UTILE
class CCollision
{
public:
	virtual ~CCollision() {};
	virtual void updateEntity(float dt) = 0;
	virtual void renderEntity(sf::RenderTarget& target) = 0;
};


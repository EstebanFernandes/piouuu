#include "CPhysics.h"

CPhysics::CPhysics()
{
	initPhysics();
}

void CPhysics::initPhysics()
{
	velocityMax = 2.f;
	velocityMin = 0.25f;
	acceleration = 0.50f;
	drag = 0.70f;
	gravity = 2.f;
	velocityMaxY = 15.f;
}

void CPhysics::move(const float dir_x, const float dir_y)
{
	//Acceleration
	velocity.x += dir_x * acceleration;
	velocity.y += dir_y * acceleration;
	std::cout << getvelocityX()<<std::endl;
	//Limit velocity
	if (std::abs(velocity.x) > velocityMax)
	{
		velocity.x = velocityMax * ((velocity.x <0.f) ? -1.f : 1.f);
		std::cout << getvelocityX();
	}
	if (std::abs(velocity.y) > velocityMax)
	{
		velocity.y = velocityMax * ((velocity.y < 0.f) ? -1.f : 1.f);
	}
}

sf::Vector2f CPhysics::updatePhysics()
{
	//Gravity
	/*velocity.y = 1.0 * gravity;
	if (std::abs(velocity.y) > velocityMaxY)
	{
		velocity.y = velocityMaxY * ((velocity.y < 0.f) ? -1.f : 1.f);

	}*/
	//Deceleration
	velocity *=drag;
	std::cout<<" Ici on met le l'aspi " << getvelocityX();
	//Limit Deceleration
	if (std::abs(velocity.x) < velocityMin) velocity.x = 0.f;
	if (std::abs(velocity.y) < velocityMin) velocity.y = 0.f;
	return velocity;
}

void CPhysics::resetVelocityY()
{
	velocity.y = 0.f;
}

float CPhysics::getvelocityX()
{
	return velocity.x;
}

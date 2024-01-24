#pragma once

#include "CGunslinger.h"

class LaserGenerator : public CGunslinger
{
private:
	sf::ConvexShape triangle = sf::ConvexShape(3);
	sf::RectangleShape laserZone;

public:
	LaserGenerator();

	void renderEntity(sf::RenderTarget& target);
};


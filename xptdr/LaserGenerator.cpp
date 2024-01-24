#include "LaserGenerator.h"

LaserGenerator::LaserGenerator()
{
	triangle.setPosition(500, 500);
	triangle.setOrigin(triangle.getLocalBounds().width/2.f, triangle.getLocalBounds().height / 2.f);
	triangle.setFillColor(sf::Color(255, 255, 255, 128));

	laserZone = sf::RectangleShape(sf::Vector2f(500, 500));
	laserZone.setPosition(50, 50);
	laserZone.setFillColor(sf::Color(255, 255, 255, 128));
}

void LaserGenerator::renderEntity(sf::RenderTarget& target)
{
	target.draw(triangle);
	target.draw(laserZone);
}

#pragma once
#include "lifeForEntity.h"
#include "SFML/Graphics.hpp"
class lifeBarForEntity : public lifeForEntity
{
private:
	sf::RectangleShape lifeBar;
	sf::RectangleShape lifeBarBackground;
public:
	void setLifeBar() {
		lifeBar = sf::RectangleShape(sf::Vector2f(100.f, 10.f));
		lifeBar.setFillColor(sf::Color::Red);
		lifeBarBackground = sf::RectangleShape(sf::Vector2f(100.f, 10.f));
		lifeBarBackground.setFillColor(sf::Color::Black);
	}
	void updateLifeBar() {
		lifeBar.setSize(sf::Vector2f(100.f * iENTLifePoint / maxhealth, 10.f));
	}
	void movelifeBar(sf::Vector2f move)
	{
		lifeBar.move(move);
		lifeBarBackground.move(move);
	}
	void renderLifeBar(sf::RenderTarget& target) {
		target.draw(lifeBarBackground);
		target.draw(lifeBar);
	}
};


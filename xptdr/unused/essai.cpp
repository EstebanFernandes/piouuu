#include "essai.h"

essai::essai()
{
	_rectangle.setSize(sf::Vector2f(200, 150));
	_rectangle.setFillColor(sf::Color::Red);
	_rectangle.setPosition(20, 20);
}

void essai::Update(sf::Time deltaTime)
{
	// The rectangle moves with time
	_rectangle.move(0.2f * deltaTime.asMilliseconds(),
		0.2f * deltaTime.asMilliseconds());

	// Pause the state when the rectangle nears the bottom
	// of the screen
	if (_rectangle.getGlobalBounds().left > 300) {
		SetPaused(true);
	}
}

void essai::Draw(const std::shared_ptr<sf::RenderWindow>& window)
{
	window->draw(_rectangle);
}

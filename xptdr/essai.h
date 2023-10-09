#pragma once
#include <SFML/Graphics.hpp>
#include "StateMachine/State.hpp"
#include "StateMachine/StateMachine.hpp"
class essai : public sm::State
{
private :
	sf::RectangleShape _rectangle;
public :
	// Constructor initialises the state
	essai();
private:
	// Update function contains state-specific logic
	void Update(sf::Time deltaTime);

	// Draw function contains SFML draw calls
	void Draw(const std::shared_ptr<sf::RenderWindow>& window);

};


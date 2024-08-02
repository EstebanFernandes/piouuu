#include "InputManager.h"

bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(button))
    {
        sf::IntRect tempRect((int)object.getPosition().x,
            (int)object.getPosition().y, (int)object.getGlobalBounds().width,
            (int)object.getGlobalBounds().height);
        if (tempRect.contains(sf::Mouse::getPosition(window))) {
            return true;
        }
    }
    return false;
}

sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& window)
{
    return sf::Mouse::getPosition( window);
}

bool InputManager::IsTextClicked(sf::Text text, sf::Mouse::Button button, sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(button))
    {
        sf::IntRect tempRect((int)text.getPosition().x,
            (int)text.getPosition().y, (int)text.getGlobalBounds().width,
            (int)text.getGlobalBounds().height);
        if (tempRect.contains(sf::Mouse::getPosition(window))) return true;
    }
    return false;
}

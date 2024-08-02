#include "Carousel.h"

sf::FloatRect Carousel::getGlobalBounds()
{
    return ellipse.getGlobalBounds();
  /*  sf::FloatRect result;
    float x = 10000.f, y = ellipse.getPosition().y, xMax = 0.f, yMax = 0.f;
    for (int i = 0; i < cards.size(); i++)
    {
        sf::FloatRect temp =
        if (temp.left < x)
            x = temp.left;
        if (temp.left + temp.width > xMax)
            xMax = temp.left + temp.width;
        if (temp.top + temp.height > yMax)
            yMax = temp.top + temp.height;
    }
    return sf::FloatRect(x, y, xMax - x, yMax - y);*/
}

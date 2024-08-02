#pragma once
#include<SFML/Graphics.hpp>
//Classe qui représente une ellipse d'après les codes de sfml
class EllipseShape : public sf::Shape
{

private:
    size_t point = 200;
    sf::Vector2f m_radius;
public:
    explicit EllipseShape(const sf::Vector2f& radius = sf::Vector2f(0, 0)) :
        m_radius(radius)
    {
        update();
    }

    void setPointCount(size_t r)
    {
        point = r;
    }
    void setRadius(const sf::Vector2f& radius)
    {
        m_radius = radius;
        update();
    }

    const sf::Vector2f& getRadius() const
    {
        return m_radius;
    }

     size_t getPointCount() const
    {
        return point; 
    }

    sf::Vector2f getPoint(size_t index) const
    {
        static const float pi = 3.141592654f;

        float angle = index * 2 * pi / getPointCount() - pi / 2;
        float x = std::cos(angle) * m_radius.x;
        float y = std::sin(angle) * m_radius.y;

        return sf::Vector2f(m_radius.x + x, m_radius.y + y);
    }

    sf::Vector2f moveToNextIndex(int index) {
        int nextindex = index++;
        if (nextindex == point )
            nextindex = 0;
        sf::Vector2f returnValue;
        returnValue.x = getPoint(index).x - getPoint(nextindex).x;
        returnValue.y = getPoint(index).y - getPoint(nextindex).y;
        return returnValue;
    }
};


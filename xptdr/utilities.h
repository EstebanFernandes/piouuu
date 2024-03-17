#pragma once
#include"SFML/Graphics.hpp"
/// <summary>
/// Namespace qui contient des méthodes utilisés à différents niveaux du codes
/// </summary>
namespace utilities {
	/// <summary>
	/// Pour 2 positions passer en paramètre cette fonction renvoie la direction vers B depuis A
	/// </summary>
	/// <param name="A"></param>
	/// <param name="B"></param>
	/// <returns>un sf::Vector2f de la direction de A vers B</returns>
	inline sf::Vector2f dirAtoB(sf::Vector2f A, sf::Vector2f B)
	{
		sf::Vector2f dir;
		sf::Vector2f otherPos = B-A;
		//Trivial case
		if (otherPos.x == 0.f && otherPos.y == 0.f)
			return sf::Vector2f(0.f, 0.f);
		if (otherPos.x == 0.f)
			return sf::Vector2f(0.f, otherPos.y/abs(otherPos.y));
		if (otherPos.y == 0.f)
			return sf::Vector2f(otherPos.x / abs(otherPos.x), 0.f);
		
		//Else
		float normVect = (float)std::sqrt(std::pow(otherPos.x, 2)+ std::pow(otherPos.y, 2));
		dir = otherPos / normVect;
		return dir;
		//
		float a = otherPos.y / otherPos.x;
		float sqrt = (float)std::sqrt(1 + std::pow(a, 2));
		dir.x = -1.f / (float)std::sqrt(1 + std::pow(a, 2));
		dir.y = a * dir.x;

		/*if (otherPos.x < 0) {
			dir.x = dir.x * -1;
			dir.y = dir.y * -1;
		}*/
		return dir;
	}
	/// <summary>
	/// return the angle in degree from a direction 
	/// </summary>
	/// <param name="dir"></param>
	/// <returns></returns>
	inline float getAngleFromDirection(sf::Vector2f dir)
	{
		float firstPart = atan2(dir.y, dir.x);
		float angle = (180.f / 3.1415926535897932384626f) * firstPart;
		//ce premier cas de figure induit que le sprite va de droite à gauche, dans ce cas si son angle
		// est supérieur à 90 degré il faut le flip pour qu'il soit dans le bon sens
		while (angle < 0.f)
		{
			angle += 360.f;
		}
		return angle;
	}
	/// <summary>
	/// return the direction in float from an angle 
	/// </summary>
	/// <param name="dir"></param>
	/// <returns></returns>
	inline sf::Vector2f getDirectionFromAngle(float angle)
	{
		float temp = angle * (3.14159265358979323846264338327950f / 180.f);
		return sf::Vector2f(cos(temp), sin(temp));
	}
	inline float renvoieNormeVecteur(sf::Vector2f dir) {
		return (float)sqrt(pow(dir.x,2) + pow(dir.y,2));
	}
	/// <summary>
	/// This function return a position based on a position
	/// an angle a width
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="widthFromPos"></param>
	/// <param name="angle"></param>
	/// <returns></returns>
	inline sf::Vector2f shootPos(const sf::Vector2f& pos, float widthFromPos, float angle)
	{
		float angle_radians = (float)fmod(angle, 360.0) * 3.1415926535897932384626f / 180.f;
		// Calculate new position
		sf::Vector2f ret(pos.x + widthFromPos * cos(angle_radians),pos.y + widthFromPos * sin(angle_radians));
		
			return ret;
	}
	/// <summary>
	/// the SFML f unction setPosition is sometimes incorrect so this function correct it
	/// </summary>
	/// <param name="text"></param>
	/// <param name="pos"></param>
	/// <returns></returns>
	inline bool readaptText(sf::Text& text,sf::Vector2f pos)
	{
		text.setPosition(pos);
		sf::FloatRect textBounds = text.getGlobalBounds();
		pos -= sf::Vector2f(textBounds.left - pos.x, textBounds.top - pos.y);
		text.setPosition(pos);
		return true;
	}
}

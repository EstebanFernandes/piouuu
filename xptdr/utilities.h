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
		sf::Vector2f otherPos = A - B;
		float a = otherPos.y / otherPos.x;
		float sqrt = (float)std::sqrt(1 + std::pow(a, 2));
		dir.x = -1.f / (float)std::sqrt(1 + std::pow(a, 2));
		dir.y = a * dir.x;

		if (otherPos.x < 0) {
			dir.x = dir.x * -1;
			dir.y = dir.y * -1;
		}
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
	inline float renvoieNormeVecteur(sf::Vector2f dir) {
		return (float)sqrt(pow(dir.x,2) + pow(dir.y,2));
	}
}

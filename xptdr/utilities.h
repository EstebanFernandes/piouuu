#pragma once
#include "SFML/Graphics.hpp"
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
	/// the SFML function setPosition is sometimes incorrect so this function correct it
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
	inline float getDistancefrom2Pos(const sf::Vector2f& posA, const sf::Vector2f& posB)
	{
		sf::Vector2f tempDistance = posA - posB;
		tempDistance.x = std::abs(tempDistance.x);
		tempDistance.y = std::abs(tempDistance.y);
		return (float)std::sqrt(pow(tempDistance.x, 2) + pow(tempDistance.y, 2));
	}
	/// <summary>
	/// Return the maximum width in float from a vector of text
	/// </summary>
	/// <param name="textes"></param>
	/// <returns></returns>
	inline float getMaxWidth(std::vector<sf::Text>& textes)
	{
		float maxWidth = 0;
		for (int i = 0; i < textes.size(); i++)
		{
			if (maxWidth < textes[i].getGlobalBounds().width)
				maxWidth = textes[i].getGlobalBounds().width;
		}
		return maxWidth;
	}



	/// <summary>
	/// Return the maximum height in a float from a vector of text
	/// </summary>
	/// <param name="textes"></param>
	/// <returns></returns>
	inline float getMaxHeight(std::vector<sf::Text>& textes)
	{
		float maxHeight = 0;
		for (int i = 0; i < textes.size(); i++)
		{
			if (maxHeight < textes[i].getGlobalBounds().height)
				maxHeight = textes[i].getGlobalBounds().height;
		}
		return maxHeight;
	}
	/// <summary>
	/// Fonction qui renvoie un float aléatoire entre le min et le max indiqué
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	inline float RandomFloat(float min, float max)
	{
		float random = ((float)rand()) / (float)RAND_MAX;

		// generate (in your case) a float between 0 and (4.5-.78)
		// then add .78, giving you a float between .78 and 4.5
		float range = max - min;
		return (random * range) + min;
	}
	inline int whereisAngle(sf::Vector2f pos, float angle)
	{

	}
	inline //Fonction qui renverse le sprite selon une symétrie axiale
		void flipSprite(sf::Sprite& Sprite,bool horizontal=true) {
		if(horizontal)
		{
			sf::IntRect temp(Sprite.getTextureRect());
			if (temp.left != 0)
			{
				temp.left = 0;
			}
			else
			{
				temp.left = temp.width;
			}
			temp.width = -temp.width;
			Sprite.setTextureRect(temp);
		}
		else {
			sf::IntRect temp(Sprite.getTextureRect());
			if (temp.top != 0)
			{
				temp.top = 0;
			}
			else
			{
				temp.top = temp.height;
			}
			temp.height = -temp.height;
			Sprite.setTextureRect(temp);
		}
	}
	/// <summary>
	/// Renvoie un float à X% près de chaque côté
	/// </summary>
	/// <param name="x"></param>
	/// <param name="value"></param>
	/// <returns></returns>
	inline float RandomatXPerc(float x,float value)
	{
		return RandomFloat(value - x, value + x);
	}
	inline void centerObject(sf::Shape& lala) {
		lala.setOrigin(lala.getLocalBounds().width / 2.f,
			lala.getLocalBounds().height / 2.f);
	}

	inline bool isNumberBetween(int min, int max, int value)
	{
		return (value > min && value < max);
	}

	inline void centerObject(sf::Sprite& lala) {
		lala.setOrigin(lala.getLocalBounds().width / 2.f,
			lala.getLocalBounds().height / 2.f);
	}
	inline void centerObject(sf::Text& lala) {
		lala.setOrigin(lala.getLocalBounds().width / 2.f,
			lala.getLocalBounds().height / 2.f);
	}
	inline void normalizeVector(sf::Vector2f& direction)
	{
		direction = direction / (float)std::sqrt(std::pow(direction.x, 2) + std::pow(direction.y, 2));
	}
	inline bool intersects(sf::CircleShape& circle, sf::FloatRect rect)
	{
		sf::Vector2f circleDistance;
		float cornerDistance_sq;

		// Get the center positions of the circle and the rectangle
		sf::Vector2f circleCenter = circle.getPosition();

		sf::Vector2f rectCenter(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);

		// Calculate the distance between the centers
		circleDistance.x = std::abs(circleCenter.x - rectCenter.x);
		circleDistance.y = std::abs(circleCenter.y - rectCenter.y);

		// Check if the circle is too far from the rectangle
		if (circleDistance.x > (rect.width / 2.f + circle.getRadius())) { return false; }
		if (circleDistance.y > (rect.height / 2.f + circle.getRadius())) { return false; }

		// Check if the circle is close enough to intersect the rectangle
		if (circleDistance.x <= (rect.width / 2.f)) { return true; }
		if (circleDistance.y <= (rect.height / 2.f)) { return true; }

		// Check for collision at the rectangle corners
		cornerDistance_sq = std::pow(circleDistance.x - rect.width / 2.f, 2.f) +
			std::pow(circleDistance.y - rect.height / 2.f, 2.f);

		return (cornerDistance_sq <= std::pow(circle.getRadius(), 2.f));
	}
	inline float minimumDistance(const sf::FloatRect& rect1, const sf::FloatRect& rect2) {
		// Si les rectangles se chevauchent, la distance minimale est 0
		if (rect1.intersects(rect2)) {
			return 0.0f;
		}

		// Calculer la distance entre les bords les plus proches
		float left = std::max(rect1.left, rect2.left);
		float right = std::min(rect1.left + rect1.width, rect2.left + rect2.width);
		float top = std::max(rect1.top, rect2.top);
		float bottom = std::min(rect1.top + rect1.height, rect2.top + rect2.height);

		// Cas où un rectangle est entièrement à gauche ou à droite de l'autre
		float horizontalDistance = std::max(0.0f, std::max(rect1.left - (rect2.left + rect2.width), rect2.left - (rect1.left + rect1.width)));

		// Cas où un rectangle est entièrement au-dessus ou en dessous de l'autre
		float verticalDistance = std::max(0.0f, std::max(rect1.top - (rect2.top + rect2.height), rect2.top - (rect1.top + rect1.height)));

		// Distance minimum entre les bords
		float edgeDistance = std::sqrt(horizontalDistance * horizontalDistance + verticalDistance * verticalDistance);

		// Vérifier la distance entre les coins
		float cornerDistance = std::numeric_limits<float>::max();

		// Les coins de rect1
		sf::Vector2f corners1[] = {
			{rect1.left, rect1.top},
			{rect1.left + rect1.width, rect1.top},
			{rect1.left, rect1.top + rect1.height},
			{rect1.left + rect1.width, rect1.top + rect1.height}
		};

		// Les coins de rect2
		sf::Vector2f corners2[] = {
			{rect2.left, rect2.top},
			{rect2.left + rect2.width, rect2.top},
			{rect2.left, rect2.top + rect2.height},
			{rect2.left + rect2.width, rect2.top + rect2.height}
		};

		// Comparer chaque coin de rect1 avec chaque coin de rect2
		for (const auto& c1 : corners1) {
			for (const auto& c2 : corners2) {
				cornerDistance = std::min(cornerDistance, getDistancefrom2Pos(c1, c2));
			}
		}

		// La distance minimale est la plus petite des deux distances trouvées
		return std::min(edgeDistance, cornerDistance);
	}

	inline sf::Vector2f glslCoord(sf::Vector2f baseCoord,float yWindowSize)
	{
		return sf::Vector2f(baseCoord.x, yWindowSize - baseCoord.y);
	}
}

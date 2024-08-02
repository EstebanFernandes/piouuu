#pragma once

#include "Gunslinger.h"
/// <summary>
/// Associe une clock à une entité
/// </summary>
struct lasersCible {
	Entity* entity;
	sf::Clock damageCooldown;
};
class LaserGenerator 
{
private:
	AssetManager* assets;
	float bulletScale = 1;
	/// <summary>
	/// True si le laser va jusqu'au bout de l'écran
	/// </summary>
	bool laserUnlimitedRange = true;
	int aa = 0;
	/// <summary>
	/// Répertorie les cibles touchées par le laser pour ne pas lui faire des dégats toutes les frames
	/// </summary>
	std::vector<lasersCible> ciblesLasers;
	sf::RectangleShape laserZone;
	Animation bLaserAnim;
	sf::Sprite beginLaser;
	Animation fLaserAnim;
	sf::Sprite fullLaser;
	Animation eLaserAnim;
	sf::Sprite endLaser;
	float baseHeight = 96;
	sf::Vector2f laserScale;
	float laserHeight = 40;
	float laserWidth = 500;
	//0 = bas droite, 1= bas gauche, 2 = haut gauche et 3= haute droite
	float anglesToCorner[4];
	/// <summary>
	/// Renvoie la distance entre la position et le bord lié à l'angle
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="angle"></param>
	/// <returns></returns>
	float lengthToBound(sf::Vector2f& pos, float& angle);
	/// <summary>
	/// Update les angles liés au corner, ces mesures nous servent dans le calcul de la distance 
	/// </summary>
	/// <param name="pos"></param>
	void updateAngles(sf::Vector2f& pos);
	/// <summary>
	/// Retourne un int correspondant au bord de l'écran concerné, 0 pour droite, 1 pour en bas etc
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="angle"></param>
	/// <returns></returns>
	int whichBound(sf::Vector2f& pos, float& angle);
public:
	LaserGenerator();
	LaserGenerator(AssetManager* assetsParam);

	 void renderWeapon(sf::RenderTarget& target);

	void updateWeapon(float dt,sf::Vector2f weaponPos, float &angle);
	void updateLasers(float delta, sf::Vector2f playerPos, int screenWidth,float &angle);
	bool checkCollisions(Mob& b);
};


#pragma once

#include "CGunslinger.h"

/// <summary>
/// Associe une clock � une entit�
/// </summary>
struct lasersCible {
	CEntity* entity;
	sf::Clock damageCooldown;
};
class LaserGenerator : public Weapon
{
private:
	/// <summary>
	/// True si le laser va jusqu'au bout de l'�cran
	/// </summary>
	bool laserUnlimitedRange = true;
	/// <summary>
	/// R�pertorie les cibles touch�es par le laser pour ne pas lui faire des d�gats toutes les frames
	/// </summary>
	std::vector<lasersCible> ciblesLasers;
	sf::RectangleShape laserZone;
	bool isActive = false;
	float laserHeight = 80;
	float laserWidth = 500;
	sf::CircleShape  triangle = sf::CircleShape(laserHeight, 3);

public:
	LaserGenerator();

	void renderWeapon(sf::RenderTarget& target);
	//void CGunslinger::iNeedMoreBullets(sf::Vector2f pos, int damage, float bulletSpeed, sf::Vector2f dir, sf::Vector2f bulletScale);
	void updateWeapon(float dt);
	void updateLasers(float delta, sf::Vector2f playerPos, int screenWidth);
	bool checkCollisions(CEntity& b);

	//red�finitions de Weapon
	void setBulletAsset(std::string assetName) {};

	bool isLaserActive();
	void changeActivity();
};


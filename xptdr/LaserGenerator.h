#pragma once

#include "CGunslinger.h"
#include "CAnimation.h"

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
	CAnimation bLaserAnim;
	sf::Sprite beginLaser;
	CAnimation fLaserAnim;
	sf::Sprite fullLaser;
	CAnimation eLaserAnim;
	sf::Sprite endLaser;
	bool isActive = false;
	float baseHeight = 96;
	sf::Vector2f laserScale;
	float laserHeight = 80;
	float laserWidth = 500;

public:
	LaserGenerator();
	LaserGenerator(CAssetManager* assetsParam);

	

	//red�finitions de Weapon
	void setBulletAsset(std::string assetName) {};
	void traiterMisc(int misc) {}; void renderWeapon(sf::RenderTarget& target);
	void weaponControls(sf::Event event);
	void weaponShoot();
	void updateWeapon(float dt);
	void updateLasers(float delta, sf::Vector2f playerPos, int screenWidth);
	bool checkCollisions(CMob& b);
	void changeTarget(CMob* r) {};

	bool isLaserActive();
	void changeActivity();
};


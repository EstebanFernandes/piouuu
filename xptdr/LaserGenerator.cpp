#include "LaserGenerator.h"

LaserGenerator::LaserGenerator()
{
	setTypeArme(laser);
	triangle.setPosition(500, 500);
	triangle.setOrigin(triangle.getLocalBounds().width / 2.f, triangle.getLocalBounds().height / 2.f);
	triangle.rotate(-90);
	//triangle.setPosition();
	triangle.setOrigin(triangle.getLocalBounds().width/2.f, triangle.getLocalBounds().height / 2.f);
	triangle.setFillColor(sf::Color(255, 0, 0, 100));


	laserZone = sf::RectangleShape(sf::Vector2f(laserWidth, laserHeight));
	laserZone.setOrigin(0, laserZone.getLocalBounds().height / 2.f);
	laserZone.setFillColor(sf::Color(255, 0, 0, 100));
}

void LaserGenerator::renderWeapon(sf::RenderTarget& target)
{
	if (isActive) {
		target.draw(triangle);
		target.draw(laserZone);
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="delta">delta</param>
/// <param name="laserStartingPos">Postion d'où part le laser, souvent devant l'avion</param>
void LaserGenerator::updateLasers(float delta, sf::Vector2f laserStartingPos, int screenWidth)
{
	sf::Vector2f laserPos;
	laserPos.x = laserStartingPos.x + triangle.getGlobalBounds().width / 2.f;
	laserPos.y = laserStartingPos.y;
	triangle.setPosition(laserPos);
	/*
	sf::Vector2f laserSize;
	laserSize.y = laserHeight;
	laserSize.x = (float)screenWidth - (triangle.getPosition().x + (triangle.getGlobalBounds().width) / 2.f);
	laserZone.setSize(laserSize);
	*/
	if (laserUnlimitedRange) {
		laserWidth = (float)screenWidth - (triangle.getPosition().x + (triangle.getGlobalBounds().width / 2.f));
	}
	sf::Vector2f laserSize;
	laserSize.y = laserHeight;
	laserSize.x = laserWidth;
	laserZone.setSize(laserSize);

	sf::Vector2f laserZonePos;
	laserZonePos.x = triangle.getPosition().x + triangle.getGlobalBounds().width / 2.f;
	laserZonePos.y = triangle.getPosition().y;
	laserZone.setPosition(laserZonePos);
}

bool LaserGenerator::checkCollisions(CEntity& b)
{
	//étape 1 : vérifier si l'entité est déjà dans la liste
	bool present = false;
	int index = -1;
	if(!ciblesLasers.empty())
	{
		for (int i = 0; i < ciblesLasers.size(); i++) {
			if (ciblesLasers[i].entity->needDelete) {
				ciblesLasers.erase(ciblesLasers.begin() + i);
			}
			else if (ciblesLasers[i].entity == &b) {
				present = true;
				index = i;
			}
			
		}
	}
	//On vérifie si un ennemie se trouve dans la zone
	if (b.Enemy &&  isActive && (triangle.getGlobalBounds().intersects(b.getSprite().getGlobalBounds()) || laserZone.getGlobalBounds().intersects(b.getSprite().getGlobalBounds()))) {
		

		if (!present) {
			lasersCible cible;
			cible.entity = &b;
			cible.damageCooldown = sf::Clock();
			ciblesLasers.push_back(cible);
			index = ciblesLasers.size() - 1;
			return true;
		}

		if (ciblesLasers[index].damageCooldown.getElapsedTime().asSeconds() >= 1.f / 1.f) {
			ciblesLasers[index].damageCooldown.restart();
			return true;
		}
	}
	else if (present) {
	}
	return false;
}

bool LaserGenerator::isLaserActive()
{
	return isActive;
}

void LaserGenerator::changeActivity()
{
	isActive = !isActive;
}

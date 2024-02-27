#include "LaserGenerator.h"

LaserGenerator::LaserGenerator()
{
	setTypeArme(laser);
}

LaserGenerator::LaserGenerator(CAssetManager* assetsParam) 
	: LaserGenerator()
{
	assets = assetsParam;
	beginLaser.setTexture(assets->GetTexture("beginLaser"));
	bLaserAnim = CAnimation(&beginLaser, sf::IntRect(0, 0, 96, 400), 4, 0.16f);
	bLaserAnim.isHorizontal = false;
	fullLaser.setTexture(assets->GetTexture("fullLaser"));
	fLaserAnim = CAnimation(&fullLaser, sf::IntRect(0, 0, 1824, 400), 4, 0.16f);
	fLaserAnim.isHorizontal = false;
	//endLaser.setTexture(assets->GetTexture("endLaser"));
	//eLaserAnim = CAnimation(&endLaser, sf::IntRect(0, 0, 153, 400), 4, 0.16f);
	laserZone = sf::RectangleShape(sf::Vector2f(beginLaser.getGlobalBounds().width+fullLaser.getGlobalBounds().width, baseHeight));
	laserZone.setOrigin(0, laserZone.getLocalBounds().height / 2.f);
	beginLaser.setOrigin(0, beginLaser.getLocalBounds().height / 2.f);
	fullLaser.setOrigin(0, fullLaser.getLocalBounds().height / 2.f);
}

void LaserGenerator::renderWeapon(sf::RenderTarget& target)
{
	if (isActive) {
		target.draw(beginLaser);
		target.draw(fullLaser);
		//target.draw(endLaser);
	}
}

void LaserGenerator::weaponControls(sf::Event event)
{
	if (sf::Keyboard::isKeyPressed(touche) && !isLaserActive()) {
		weaponShoot();
	}
	else if (!sf::Keyboard::isKeyPressed(touche) && isLaserActive()) {
		
		weaponShoot();
	}
}

void LaserGenerator::weaponShoot()
{
	changeActivity();
}

void LaserGenerator::updateWeapon(float dt)
{
	updateLasers(dt, getWeaponPos(), assets->sCREEN_WIDTH);
	bLaserAnim.updateAnimation();
	fLaserAnim.updateAnimation();
}

/// <summary>
/// 
/// </summary>
/// <param name="delta">delta</param>
/// <param name="laserStartingPos">Postion d'où part le laser, souvent devant l'avion</param>
void LaserGenerator::updateLasers(float delta, sf::Vector2f laserStartingPos, int screenWidth)
{
	sf::Vector2f laserPos = laserStartingPos;
	beginLaser.setPosition(laserStartingPos);
	laserZone.setPosition(laserStartingPos);
	laserPos.x += beginLaser.getGlobalBounds().width;
	fullLaser.setPosition(laserPos);
	/*
	sf::Vector2f laserSize;
	laserSize.y = laserHeight;
	laserSize.x = (float)screenWidth - (triangle.getPosition().x + (triangle.getGlobalBounds().width) / 2.f);
	laserZone.setSize(laserSize);
	*/
	if (laserUnlimitedRange) {
		laserWidth = (float)screenWidth - beginLaser.getPosition().x;
	}
	sf::Vector2f laserSize;
	laserSize.y = baseHeight;
	laserSize.x = laserWidth;
	laserZone.setSize(laserSize);
}

bool LaserGenerator::checkCollisions(CMob& b)
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
	if (b.Enemy &&  isActive && laserZone.getGlobalBounds().intersects(b.getSprite().getGlobalBounds())) {
		

		if (!present) {
			lasersCible cible;
			cible.entity = &b;
			cible.damageCooldown = sf::Clock();
			ciblesLasers.push_back(cible);
			index = (int)ciblesLasers.size() - 1;
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

#include "LaserGenerator.h"

LaserGenerator::LaserGenerator()
{

}

LaserGenerator::LaserGenerator(CAssetManager* assetsParam) 
	: LaserGenerator()
{
	float timeFrames = 0.1f;
	bulletScale=laserHeight / baseHeight;
	assets = assetsParam;
	beginLaser.setTexture(assets->GetTexture("beginLaser"));

	bLaserAnim = CAnimation(&beginLaser, sf::IntRect(0, 0, (int)baseHeight, 400), 4, timeFrames);
	bLaserAnim.isHorizontal = false;
	fullLaser.setTexture(assets->GetTexture("fullLaser"));
	fLaserAnim = CAnimation(&fullLaser, sf::IntRect(0, 0, 1824, 400), 4, timeFrames);
	fLaserAnim.isHorizontal = false;
	//endLaser.setTexture(assets->GetTexture("endLaser"));
	//eLaserAnim = CAnimation(&endLaser, sf::IntRect(0, 0, 153, 400), 4, 0.16f);
	beginLaser.setOrigin(0, beginLaser.getLocalBounds().height / 2.f);
	fullLaser.setOrigin(0, fullLaser.getLocalBounds().height / 2.f);
	fullLaser.setScale(bulletScale, bulletScale);
	beginLaser.setScale(bulletScale, bulletScale);
	laserZone = sf::RectangleShape(sf::Vector2f(beginLaser.getGlobalBounds().width+fullLaser.getGlobalBounds().width, laserHeight));
	laserZone.setOrigin(0, laserZone.getLocalBounds().height / 2.f);
}

LaserGenerator::LaserGenerator(CAssetManager* assetsParam, sf::Vector2f direction)
	:LaserGenerator(assetsParam)
{

}

void LaserGenerator::setWeaponStats(CWeaponStat statsParam)
{
	/*std::string nameI = referenceStat.nameImage;
	sf::Vector2f temp = referenceStat.bulletScale;
	Weapon::setWeaponStats(statsParam);
	referenceStat.bulletScale = temp;
	referenceStat.nameImage = nameI;*/
}

void LaserGenerator::renderWeapon(sf::RenderTarget& target)
{
	target.draw(beginLaser);
	target.draw(fullLaser);
}

void LaserGenerator::weaponControls(sf::Event event)
{
	/*if (sf::Keyboard::isKeyPressed(touche) && !isLaserActive()) {
		weaponShoot();
	}
	else if (!sf::Keyboard::isKeyPressed(touche) && isLaserActive()) {
		
		weaponShoot();
	}*/
}

void LaserGenerator::weaponShoot()
{
	//changeActivity();
}

void LaserGenerator::updateWeapon(float dt,sf::Vector2f weaponPos,float &angle)
{
	if (aa++ == 1)
	{
		bLaserAnim.setSprite(&beginLaser);
		fLaserAnim.setSprite(&fullLaser);
	}
	updateLasers(dt, weaponPos, assets->sCREEN_WIDTH,angle);
	bLaserAnim.updateAnimation();
	fLaserAnim.updateAnimation();
}

/// <summary>
/// 
/// </summary>
/// <param name="delta"></param>
/// <param name="laserStartingPos">Postion d'où part le laser, souvent devant l'avion</param>
void LaserGenerator::updateLasers(float delta, sf::Vector2f laserStartingPos, int screenWidth,float &angle)
{
	beginLaser.setPosition(laserStartingPos);
	beginLaser.setRotation(angle);
	laserZone.setPosition(laserStartingPos);
	laserZone.setRotation(angle);
	fullLaser.setPosition(utilities::shootPos(laserStartingPos, bLaserAnim.getCurrentFrame()->width*bulletScale, angle));
	fullLaser.setRotation(angle);

	if (laserUnlimitedRange) {
		laserWidth = (float)screenWidth - fullLaser.getGlobalBounds().left;
	}
	sf::Vector2f laserSize;
	laserSize.y = laserHeight;
	laserSize.x = laserWidth;
	laserZone.setSize(laserSize);
	fLaserAnim.getCurrentFrame()->width = (int)(laserWidth* 1.f/bulletScale);
	fLaserAnim.switchFrames();
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
	if (b.Enemy  && laserZone.getGlobalBounds().intersects(b.getSprite().getGlobalBounds())) {
		

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




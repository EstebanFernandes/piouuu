#include "LaserGenerator.h"

LaserGenerator::LaserGenerator()
{

}

LaserGenerator::LaserGenerator(AssetManager* assetsParam) 
	: LaserGenerator()
{
	float timeFrames = 0.1f;
	bulletScale=laserHeight / baseHeight;
	assets = assetsParam;
	beginLaser.setTexture(assets->GetTexture("beginLaser"));

	bLaserAnim = Animation(&beginLaser, sf::Vector2i( (int)baseHeight, 400), sf::Vector2i(1,4), timeFrames);
	bLaserAnim.isHorizontal = false;
	fullLaser.setTexture(assets->GetTexture("fullLaser"));
	fLaserAnim = Animation(&fullLaser, sf::Vector2i(1824, 400), sf::Vector2i(1, 4), timeFrames);
	fLaserAnim.isHorizontal = false;
	beginLaser.setOrigin(0, beginLaser.getLocalBounds().height / 2.f);
	fullLaser.setOrigin(0, fullLaser.getLocalBounds().height / 2.f);
	fullLaser.setScale(bulletScale, bulletScale);
	beginLaser.setScale(bulletScale, bulletScale);
	laserZone = sf::RectangleShape(sf::Vector2f(beginLaser.getGlobalBounds().width+fullLaser.getGlobalBounds().width, laserHeight));
	laserZone.setOrigin(0, laserZone.getLocalBounds().height / 2.f);
}





void LaserGenerator::renderWeapon(sf::RenderTarget& target)
{
	target.draw(beginLaser);
	target.draw(fullLaser);
}

void LaserGenerator::updateWeapon(float dt,sf::Vector2f weaponPos,float &angle)
{
	if (aa++ == 1)
	{
		bLaserAnim.setSprite(&beginLaser);
		fLaserAnim.setSprite(&fullLaser);
	}
	updateLasers(dt, weaponPos, Engine::SCREEN_WIDTH,angle);
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
	int screenheight = Engine::SCREEN_HEIGHT;
	beginLaser.setPosition(laserStartingPos);
	beginLaser.setRotation(angle);
	laserZone.setPosition(laserStartingPos);
	laserZone.setRotation(angle);
	sf::Vector2f posFLaser = utilities::shootPos(laserStartingPos, bLaserAnim.getCurrentFrame()->width * bulletScale, angle);
	fullLaser.setPosition(posFLaser);
	fullLaser.setRotation(angle);

	if (laserUnlimitedRange) {// adapté à l'angle
		laserWidth = lengthToBound(posFLaser, angle)+laserHeight;
	}
	sf::Vector2f laserSize;
	laserSize.y = laserHeight;
	laserSize.x = laserWidth;
	laserZone.setSize(laserSize);
	fLaserAnim.getCurrentFrame()->width = (int)(laserWidth* 1.f/bulletScale);
	fLaserAnim.switchFrames();
}

bool LaserGenerator::checkCollisions(Mob& b)
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
	if (laserZone.getGlobalBounds().intersects(b.getSprite().getGlobalBounds())) {
		

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

float LaserGenerator::lengthToBound(sf::Vector2f& pos, float& angle)
{
		// Récupérer les dimensions de l'écran
	float largeurEcran = (float)Engine::SCREEN_WIDTH;
		float hauteurEcran = (float)Engine::SCREEN_HEIGHT;


		// Convertir l'angle en radians
		float angleEnRadians = angle * 3.14159265f / 180.f;
		int bound = whichBound(pos, angle);
		// Calculer la pente de la droite
		float m = std::tan(angleEnRadians);

		// Calculer la position projetée sur la droite en fonction de l'angle
		// Pour les bords gauche et droit de l'écran
		float yOnLeftEdge = pos.y - (pos.x * m);
		float yOnRightEdge = pos.y + ((largeurEcran - pos.x) * m);

		// Pour les bords haut et bas de l'écran
		float xOnTopEdge = pos.x - (pos.y / m);
		float xOnBottomEdge = pos.x + (((hauteurEcran - pos.y)) / m);
		sf::Vector2f projection;
		switch(bound)
		{
		case 0://Droite
			projection.x = largeurEcran;
			projection.y = yOnRightEdge;
			break;
		case 1://Bas
			projection.x = xOnBottomEdge;
			projection.y = hauteurEcran;
			break;
		case 2://Gauche
			projection.x =  0.f ;
			projection.y = yOnLeftEdge;
			break;
		case 3://Haut
			projection.x = xOnTopEdge;
			projection.y = 0.f;
			break;
		}

		return utilities::getDistancefrom2Pos(pos,projection);
}

void LaserGenerator::updateAngles(sf::Vector2f& pos)
{
	float width = (float)Engine::SCREEN_WIDTH; 
	float height = (float)Engine::SCREEN_HEIGHT;
	sf::Vector2f secondPos(width, height);
	anglesToCorner[0] = utilities::getAngleFromDirection(utilities::dirAtoB(pos, secondPos));
	secondPos.x = 0.f;
	anglesToCorner[1] = utilities::getAngleFromDirection(utilities::dirAtoB(pos, secondPos));
	secondPos.y = 0.f;
	anglesToCorner[2] = utilities::getAngleFromDirection(utilities::dirAtoB(pos, secondPos));
	secondPos.x = width;
	anglesToCorner[3] = utilities::getAngleFromDirection(utilities::dirAtoB(pos, secondPos));
}

int LaserGenerator::whichBound(sf::Vector2f& pos, float& angle)
{
	updateAngles(pos);
	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			if (angle<anglesToCorner[i] || angle>anglesToCorner[3])
			return 0;
		}
		else if (angle < anglesToCorner[i])
			return i;
	}
}




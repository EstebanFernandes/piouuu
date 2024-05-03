#include "laserWeapon.h"

laserWeapon::laserWeapon()
{
	setTypeArme(laser);
}

laserWeapon::laserWeapon(CAssetManager* assets)
	:laserWeapon()
{
	this->assets = assets;
	addShootType(classic);
}

void laserWeapon::changeActivity()
{
		//opérateur XOR
	isActive ^= true;// = !isActive;
}

void laserWeapon::changeTarget(CMob* r)
{

}

void laserWeapon::traiterMisc(int misc)
{
	switch (misc)
	{
	case 0:
		//auto aim
		addShootType(autoAim);
		break;
		//Velocity up
	case 1:

		break;
		//doubleTirs1
	case 2:
		addShootType(doubleTirs1);
		break;
		//doubleTirs2
	case 3:
		addShootType(doubleTirs2);
		break;
		//gunshot
	case 4:
		addShootType(gunshotAim);
		break;
	case 5: //Dot
		addBulletType(dotBullet);
		referenceStat.dotCD = 0.2f;
		referenceStat.dotDamage = 2.f;
		referenceStat.dotTimer = 5.f;
		break;
	case 7: //explosiveBullet
		addBulletType(explosiveBullet);
		break;
	case 8: //Spin
		addShootType(Spin);
		break;
	}
	//Okay okay
}

void laserWeapon::addShootType(int type)
{
	typeTir = type;
	switch (typeTir) {
	case classic:
	{
		sf::Vector2f ttr(1.f, 0.f);
		referenceStat.addDir(ttr);
		lasers.push_back(LaserGenerator(assets));
		break;
	}
	case doubleTirs1:
	{
		int prevSize = (int)referenceStat.dir2.size();
		for (int i = 0; i < prevSize; i++)
		{
			sf::Vector2f temp = referenceStat.dir2[i];
			if (temp.y == 0)
			{
				temp.y = 0.75f;
				referenceStat.changeDir(temp, i);
				temp.y = -0.75f;
				referenceStat.addDir(temp);
				lasers.push_back(LaserGenerator(assets));
			}
			if (temp.x == 0)
			{
				temp.x = 0.75f;
				referenceStat.changeDir(temp, i);
				temp.x = -0.75f;
				referenceStat.addDir(temp);
				lasers.push_back(LaserGenerator(assets));
			}
		}
	}
	break;
	case doubleTirs2:
	{
		sf::Vector2f temp = referenceStat.dir;
		int prevSize = (int)referenceStat.dir2.size();
		for (int i = 0; i < prevSize; i++)
		{
			referenceStat.changeDir(temp, i);
		}
	}
	break;
	case gunshotAim:
	{
		sf::Vector2f temp = referenceStat.dir2[0];
		referenceStat.dir2.clear();
		float yDirection = -0.75f;
		for (int i = 0; i < 7; i++)
		{
			temp.y = yDirection;
			yDirection += 0.25f;
			referenceStat.dir2.push_back(temp);
			lasers.push_back(LaserGenerator(assets));
		}
	}
	break;
	}
}

bool laserWeapon::checkCollisions(CMob& b)
{
	if (isActive)
	{
		for (std::list<LaserGenerator>::iterator it = lasers.begin(); it != lasers.end(); ++it) {
			if (it->checkCollisions(b))
				return true;
		}
	}
	return false;
}

void laserWeapon::weaponControls(sf::Event)
{
	if (sf::Keyboard::isKeyPressed(touche) && !isActive) {
		weaponShoot();
	}
	else if (!sf::Keyboard::isKeyPressed(touche) && isActive) 
	{	
		weaponShoot();
	}
}

void laserWeapon::weaponShoot()
{
	changeActivity();
}

void laserWeapon::updateWeapon(float dt)
{
	if (isActive) 
	{
		int i = 0;
		for (std::list<LaserGenerator>::iterator it = lasers.begin(); it != lasers.end(); ++it) 
		{//Corrigé je crois, jsp si ça passe
			float angle= utilities::getAngleFromDirection( referenceStat.dir2[i]);
			if (typeTir == Spin)
				angle +=angleOffset;
			it->updateWeapon(dt, weaponPos,angle);
			i++;
		}
	}
	//à refaire 
	if (bulletClock2.getElapsedTime().asSeconds() >= 0.05f && typeTir == typeAim::Spin)
	{
		bulletClock2.restart();
		if (angleOffset != 359.f)
		{
			angleOffset++;
		}
		else
			angleOffset = 0;
		//std::cout << angleOffset << std::endl;
	}
}

void laserWeapon::renderWeapon(sf::RenderTarget& target)
{
	if (isActive)
	{
		for (std::list<LaserGenerator>::iterator it = lasers.begin(); it != lasers.end(); ++it) {
			it->renderWeapon(target);
		}
	}
}

void laserWeapon::setBulletAsset(std::string assetName)
{
}

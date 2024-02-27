#include "CGunslinger.h"
#include <bitset>

void CGunslinger::initBuff(CBulletAuto& ref)
{
	ref.getBuffs().clear();
	std::bitset<nbBullet> temp = std::bitset<nbBullet>(typeBalle);
	for (int i = 0; i < temp.size(); i++)
	{
		if (temp[i] != 0)
		{
			addByIndex(ref, i);
		}
	}
}

CGunslinger::CGunslinger()
{
	setTypeArme(gunslinger);
	typeTir = 0;
	typeBalle = (int)pow(2, 0);
	
}

void CGunslinger::updateWeapon(float dt)
{
	for (size_t i = 0; i < magasine.size(); i++)
	{
		if (magasine[i].needDelete == true)
		{
			magasine.erase(magasine.begin() + i);
			if (i != 0)
				i--;
			break;
		}
		magasine[i].updateEntity(dt);
		if (magasine[i].checkGlobalCollisions() == true)
			magasine[i].needDelete = true;
		if (magasine[i].needDelete == true)
		{
			magasine.erase(magasine.begin() + i);
			if (i != 0)
				i--;
		}
	}
	if (bulletClock2.getElapsedTime().asSeconds() >= 0.05f&&typeTir==typeAim::Spin)
	{
		bulletClock2.restart();
		if (angleOffset != 359.f)
		{
			angleOffset++;
		}
		else
			angleOffset = 0;
		std::cout << angleOffset << std::endl;
	}
}

void CGunslinger::weaponControls(sf::Event event )
{
	if (sf::Keyboard::isKeyPressed(touche))
	{
		weaponShoot();
	}
}

void CGunslinger::weaponShoot()
{
	if (bulletClock.getElapsedTime().asSeconds() >= 1.f / getWeaponStats().attackSpeed) {
		//Calcul de la pos de l'arme
		iNeedMoreBullets(getWeaponPos());

		// vient juste le restart le timer � la fin 
		bulletClock.restart();
	}
}


void CGunslinger::iNeedMoreBullets(sf::Vector2f pos)
{
	CBulletAuto reference(getWeaponStats(), assets);
	reference.setBulletPos(pos);
	initBuff(reference);
	for (int i = 0; i < referenceStat.dir2.size(); i++)
	{
		sf::Vector2f tempDirection = referenceStat.dir2[i];
		if (typeTir == Spin)
			tempDirection = utilities::getDirectionFromAngle(utilities::getAngleFromDirection(tempDirection)+angleOffset);
		reference.setDirection(tempDirection);
		reference.setDirectionSprite();
		magasine.push_back(reference);
		bulletSound.play();
	}
}


void CGunslinger::setWeaponStats(CWeaponStat statsParam) 
{
	Weapon::setWeaponStats(statsParam);
	addShootType(classic);
}

void CGunslinger::renderWeapon(sf::RenderTarget& target)
{
		for (size_t i = 0; i < magasine.size(); i++)
		{
			magasine[i].renderEntity(target);
		}
}

void CGunslinger::traiterMisc(int misc)
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
		setGunShotDistance(250.f);
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
	}
}

bool CGunslinger::checkCollisions(CMob& b)
{
	for (size_t i = 0; i < magasine.size(); i++)
	{

		if (magasine[i].checkCollisions(b))
		{
			return true;
		}
	}
	return false;
}

void CGunslinger::addShootType(int type)
{
	if (type >= 0)
	{
		typeTir = type;
		switch (typeTir) {
		case classic:
			referenceStat.addDir(referenceStat.dir);
			break;
		case doubleTirs1:
		{
			int prevSize = (int)referenceStat.dir2.size();
			for(int i=0;i<prevSize;i++)
			{
				sf::Vector2f temp = referenceStat.dir2[i];
				if(temp.y==0)
				{
				temp.y = 0.75f;
				referenceStat.changeDir(temp,i);
				temp.y = -0.75f;
				referenceStat.addDir(temp);
				}
				if (temp.x == 0)
				{
					temp.x = 0.75f;
					referenceStat.changeDir(temp,i);
					temp.x = -0.75f;
					referenceStat.addDir(temp);
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
			referenceStat.changeDir(temp,i);
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
			}
		}
		break;
		}
	}
}

void CGunslinger::addByIndex(CBulletAuto& ref , int index)
{
	switch (index)
	{
	case classic:
		break;
	case dotBullet:
		ref.addBuff(new dot(NULL, getWeaponStats().dotDamage, getWeaponStats().dotCD, getWeaponStats().dotTimer), false);
		break;
	case explosiveBullet:
		ref.isExplosive = true;
		break;
	}
}





void CGunslinger::shootTowardDirection(sf::Vector2f initPos, sf::Vector2f targetPos)
{
	sf::Vector2f newDir = utilities::dirAtoB(initPos, targetPos);
	for (int i = 0; i < referenceStat.dir2.size(); i++)
	{
		referenceStat.dir2[i] = newDir;
	}
	//std::cout << "direction in x : " << dir.x << " in y : " << dir.y<<std::endl;
	iNeedMoreBullets(initPos);
}

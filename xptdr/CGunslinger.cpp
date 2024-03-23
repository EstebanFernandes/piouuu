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

void CGunslinger::setAnimation(CBulletAuto &ref)
{
	if (getWeaponStats().nameImage == "bulletImageRancoeur")
	{
		CAnimation temp(ref.getPointerSprite(), sf::IntRect(0, 0, 30, 22), 4, 0.2f);
		temp.pxbetFrames = 2;
		ref.setAnimation(temp);
	}
}

CGunslinger::CGunslinger()
	:Weapon()
{
	setTypeArme(gunslinger);
	typeTir = 0;
	typeBalle = (int)pow(2, 0);
	
}

void CGunslinger::updateWeapon(float dt)
{
	for (std::list<CBulletAuto>::iterator it = magasine.begin(); it != magasine.end(); /*++it*/) {
		it->updateEntity(dt);
		if (typeTir == bombe)
			it->rotate(0.2f);
		if (it->isMobSet == false && typeTir == autoAim)
			*seekForTarget = true;
		if (it->checkGlobalCollisions())
			it->needDelete = true;
		if (it->needDelete)
			it = magasine.erase(it);
		else
			++it;
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
		//std::cout << angleOffset << std::endl;
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

		// vient juste le restart le timer à la fin 
		bulletClock.restart();
	}
}


void CGunslinger::iNeedMoreBullets(sf::Vector2f pos)
{
	CBulletAuto reference(getWeaponStats(), assets);
	reference.setBulletPos(pos);
	initBuff(reference);
	if(typeTir==autoAim)	
		*seekForTarget = true;
	for (int i = 0; i < referenceStat.dir2.size(); i++)
	{
		sf::Vector2f& tempDirection = referenceStat.dir2[i];
		if (typeTir == Spin)
			tempDirection = utilities::getDirectionFromAngle(utilities::getAngleFromDirection(tempDirection)+angleOffset);
		if (typeTir != bombe)
		{
		reference.setDirection(tempDirection);
		reference.setDirectionSprite();
		}
		magasine.push_back(reference);
	setAnimation(magasine.back());
		bulletSound->play();
	}
}


void CGunslinger::setWeaponStats(CWeaponStat statsParam) 
{
	Weapon::setWeaponStats(statsParam);
	addShootType(classic);
}

void CGunslinger::renderWeapon(sf::RenderTarget& target)
{
	for (std::list<CBulletAuto>::iterator it = magasine.begin(); it != magasine.end(); ++it) {
		it->renderEntity(target);
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
	case 8: //Spin
		addShootType(Spin);
		break;
	}
}

bool CGunslinger::checkCollisions(CMob& b)
{
	for (std::list<CBulletAuto>::iterator it = magasine.begin(); it != magasine.end(); ++it) {
		if (it->checkCollisions(b))
			return true;
	}
	return false;
}

void CGunslinger::addShootType(int type)
{
	if (type >= 0)
	{
		typeTir = type;
		switch (typeTir) {
		case bombe:
			setBulletAsset("bombe");
			break;
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

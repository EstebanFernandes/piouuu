#include "CGunslinger.h"
#include"fire.h"
#include"ice.h"
#include"thunder.h"
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
		CAnimation temp(ref.getPointerSprite(), sf::Vector2i( 30, 22), 4, 0.2f);
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
	isShooting = true;
	CBulletAuto reference(referenceStat, assets);
	reference.setBulletPos(pos);
	if(typeTir==autoAim)	
		*seekForTarget = true;
	for (int i = 0; i < referenceStat.dir2.size(); i++)
	{
		initBuff(reference);
		sf::Vector2f tempDirection = referenceStat.dir2[i];
		if (typeTir == gunshotAim)
		{
			tempDirection = utilities::getDirectionFromAngle(utilities::RandomatXPerc(15.f,utilities::getAngleFromDirection(tempDirection)));
			reference.setGunShotDistance(utilities::RandomatXPerc(15.f,reference.getGunshotTotalDistance() ));
			reference.setBulletSpeed(utilities::RandomatXPerc(0.5f, reference.getBulletSpeed()));
		}
		if (typeTir == Spin)
		{
			tempDirection = utilities::getDirectionFromAngle(utilities::getAngleFromDirection(tempDirection) + angleOffset);
		}
		if (typeTir == doubleTirs2)
		{
			if(i==0)
				reference.setBulletPos(sf::Vector2f(pos.x, pos.y - 7.f));
			else
				reference.setBulletPos(sf::Vector2f(pos.x, pos.y + 7.f));
		}
		if (typeTir != bombe)
		{
		reference.setDirection(tempDirection);
		reference.setDirectionSprite();
		}
		magasine.push_back(reference);
	setAnimation(magasine.back());
		bulletSound->play();
		if (typeTir == gunshotAim)
		{
			reference.setGunShotDistance(referenceStat.maxDistance);
			reference.setBulletSpeed(referenceStat.bulletSpeed);
		}
	}
	reference.isReference = true;
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
	if (isShooting)
		isShooting = false;
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
	case 9: //doubleTirs3 = ie Triple tirs
		addShootType(doubleTirs3);
		break;
	case 10: //Fire
		addBulletType(fireBullet);
		referenceStat.dotCD = 0.2f;
		referenceStat.dotDamage = 2.f;
		referenceStat.dotTimer = 2.5f;
		break;
	case 11: //Ice
		addBulletType(iceBullet);
		referenceStat.dotCD = 0.2f;
		referenceStat.dotDamage = 2.f;
		referenceStat.dotTimer = 2.5f;
		break;
	case 12: //doubleTirs3 = ie Triple tirs
		addBulletType(thunderBullet);
		break;
	}
}

int CGunslinger::checkCollisions(CMob& b)
{
	for (std::list<CBulletAuto>::iterator it = magasine.begin(); it != magasine.end(); ++it) {
		if (it->checkCollisions(b))
		{
			return it->getDamage();
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
		case doubleTirs3:
		{
			sf::Vector2f tempLast = referenceStat.dir;
			referenceStat.dir2.clear();
			referenceStat.addDir(tempLast);
			for (int i = 0; i < 1; i++)
			{
				sf::Vector2f temp = referenceStat.dir2[i];
				sf::Vector2f addDir;
				if (temp.y == 0)
				{
					temp.y = 0.75f;
					addDir = temp;
					utilities::normalizeVector(addDir);
					referenceStat.changeDir(addDir, i);
					temp.y = -0.75f;
					addDir = temp;
					utilities::normalizeVector(addDir);
					referenceStat.addDir(temp);
				}
				if (temp.x == 0)
				{
					temp.x = 0.75f;
					addDir = temp;
					utilities::normalizeVector(addDir);
					referenceStat.changeDir(temp, i);
					temp.x = -0.75f;
					addDir = temp;
					utilities::normalizeVector(addDir);
					referenceStat.addDir(temp);
				}
			}
			referenceStat.addDir(tempLast);
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
	case fireBullet:
	{
		fire* temp = new fire(NULL, getWeaponStats().dotDamage, getWeaponStats().dotCD, getWeaponStats().dotTimer, assets);
		temp->hasGlobal = true;
		ref.addBuff(temp, false);
		break;
	}
	case iceBullet:
	{
		ice* tempi = new ice(NULL, getWeaponStats().dotTimer, 0.3f);
		ref.addBuff(tempi, false);
		break;
	}
	case thunderBullet:
	{
		thunder* tempi = new thunder(NULL, NULL, getWeaponStats().bulletDamage * 0.2f, 50.f, assets);		
		tempi->hasGlobal = true;
		ref.addBuff(tempi, false);
		break;
	}
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

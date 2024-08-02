#include "Gunslinger.h"
#include"../Buff/fire.h"
#include"../Buff/ice.h"
#include"../Buff/thunder.h"
#include <bitset>

void Gunslinger::setAnimation(BulletAuto &ref)
{
	if (getWeaponStats().nameImage == "bulletImageRancoeur")
	{
		Animation temp(ref.getPointerSprite(), sf::Vector2i( 30, 22), 4, 0.2f);
		temp.pxbetFrames = 2;
		ref.setAnimation(temp);
	}
}

Bullet* Gunslinger::getAllocatedBullet()
{
	switch (typeBalle)
	{
	case typeBullet::classic:
		return new Bullet(referenceStat, assets);
		break;
	case typeBullet::explosiveBullet :

			break; 
	case typeBullet::circle :

		break;

	}
	return NULL;
}

Gunslinger::Gunslinger()
	:Weapon()
{
	setTypeArme(gunslinger);
	typeTir = 0;
	typeBalle = 0;
}

Gunslinger::~Gunslinger()
{
	//Allocated  by new but it has the last bullet we fire so we cant delete it
	//delete refBullet;
}

void Gunslinger::updateWeapon(float dt)
{
	if (wantToShoot==true)
		weaponShoot();
	int index = 0;
	for (std::list<Bullet*>::iterator bullet = bullets.begin(); bullet != bullets.end(); /*++it*/) {
		(*bullet)->updateEntity(dt);

		if ((*bullet)->needDelete)
		{
			delete (*bullet);
			bullet = bullets.erase(bullet);
		}
		else
			bullet++;
	}
	updateAngle();
}

void Gunslinger::weaponControls(sf::Event event )
{

	switch (event.type)
	{
		case sf::Event::KeyPressed:
		{
			if (event.key.code == touche)
				wantToShoot = true;
			break;
		}
		case sf::Event::KeyReleased:
		{
			if (event.key.code == touche)
				wantToShoot = false;
			break;
		}
	}
}

void Gunslinger::weaponShoot()
{
	if (bulletClock.getElapsedTime().asSeconds() >= 1.f / getWeaponStats().attackSpeed) {
		//Calcul de la pos de l'arme
		iNeedMoreBullets(getWeaponPos());

		// vient juste le restart le timer à la fin 
		bulletClock.restart();
	}
}


void Gunslinger::iNeedMoreBullets(sf::Vector2f pos)
{
	isShooting = true;
	if (typeTir == autoAim)
		*seekForTarget = true;
	for (int i = 0; i < referenceStat.dir2.size(); i++)
	{
		Bullet* newBullet = getAllocatedBullet();
		newBullet->setBulletPos(pos);
		initBuff(newBullet);
		//Pas besoin si c'est un pointeur, il faut juste bien redéfinir les opérateur = et le constructeur de copie
		//initBuff(newBullet);
		sf::Vector2f tempDirection = referenceStat.dir2[i];
		if (typeTir == gunshotAim)
		{
			tempDirection = utilities::getDirectionFromAngle(utilities::RandomatXPerc(15.f, utilities::getAngleFromDirection(tempDirection)));
			newBullet->setBulletSpeed(utilities::RandomatXPerc(0.5f, newBullet->getBulletSpeed()));
		}
		if (typeTir == Spin)
		{
			tempDirection = utilities::getDirectionFromAngle(utilities::getAngleFromDirection(tempDirection) + angleOffset);
		}
		if (typeTir == doubleTirs2)
		{
			if (i == 0)
				newBullet->setBulletPos(sf::Vector2f(pos.x, pos.y - 7.f));
			else
				newBullet->setBulletPos(sf::Vector2f(pos.x, pos.y + 7.f));
		}
		if (typeTir != bombe)
		{
			newBullet->setDirection(tempDirection);
			newBullet->setDirectionSprite();
		}
		bullets.push_back(newBullet);
		//setAnimation(magasine.back());
		bulletSound->play();
	}
}


void Gunslinger::setWeaponStats(WeaponStat statsParam) 
{
	Weapon::setWeaponStats(statsParam);
	addShootType(classic);
}

void Gunslinger::renderWeapon(sf::RenderTarget& target)
{
	for (Bullet* bullet : bullets)
		bullet->renderEntity(target);
	if (isShooting)
		isShooting = false;
}

void Gunslinger::traiterMisc(int misc)
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
		referenceStat.dotCD = 0.2f;
		referenceStat.dotDamage = 2.f;
		referenceStat.dotTimer = 5.f;
		addBuff(new dot(NULL, referenceStat.dotDamage, referenceStat.dotCD, referenceStat.dotTimer));
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
		referenceStat.dotCD = 0.2f;
		referenceStat.dotDamage = 2.f;
		referenceStat.dotTimer = 2.5f;
		addBuff(new fire(NULL, 2, 0.2f, 2.5f, assets));
		break;
	case 11: //Ice
		referenceStat.dotCD = 0.2f;
		referenceStat.dotDamage = 2.f;
		referenceStat.dotTimer = 2.5f;
		addBuff(new ice(NULL,2.5f,2.f));
		break;
	case 12: //doubleTirs3 = ie Triple tirs
		addBuff(new thunder(NULL, NULL, referenceStat.dotDamage, 100, assets));
		break;
	}
}

int Gunslinger::checkCollisions(Mob& b)
{
	for (Bullet* bullet : bullets) {
		if (bullet->checkCollisions(b))
		{
			return bullet->getDamage();
		}
	}
	return false;
}

void Gunslinger::addShootType(int type)
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

void Gunslinger::shootTowardDirection(sf::Vector2f initPos, sf::Vector2f targetPos)
{
		sf::Vector2f newDir = utilities::dirAtoB(initPos, targetPos);
	for (int i = 0; i < referenceStat.dir2.size(); i++)
	{
		referenceStat.dir2[i] = newDir;
	}
	iNeedMoreBullets(initPos);
}

void Gunslinger::initBuff(Bullet* bullet)
{
	for (int i = 0; i < effetOnHit.size(); i++)
	{
		bullet->addBuff(effetOnHit[i]->clone(), false);
	}
}

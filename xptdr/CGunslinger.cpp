#include "CGunslinger.h"

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
}


void CGunslinger::iNeedMoreBullets(sf::Vector2f pos)
{
	pos += weaponPos;
	CBulletAuto reference(referenceStat, assets);
	reference.setBulletPos(pos);
	initBuff(reference);
	switch (typeTir) {
		case classic:
		case autoAim:

			magasine.push_back(reference);
			break;
		case doubleTirs1:
		{
			for (int i = 0; i < 2; i++)
			{
				if (i == 0)
				{
					reference.setDirection(sf::Vector2f(1.f, -0.75f));
					magasine.push_back(reference);
					bulletSound.play();
				}
				else {
					initBuff(reference);
					reference.setDirection(sf::Vector2f(1.f, 0.75f));
					magasine.push_back(reference);
				}
			}
		}
		break;
		case doubleTirs2:
		{
			std::cout << "Erreur lors du chargement du son de tir." << std::endl;
		}
	}
}


void CGunslinger::renderWeapon(sf::RenderTarget& target)
{
		for (size_t i = 0; i < magasine.size(); i++)
		{
			magasine[i].renderEntity(target);
		}
}

void CGunslinger::addShootType(int type)
{
	if (type >= 0 && type <= nbAim - 1)
	{
		typeTir = type;
	}
}

void CGunslinger::addBulletType(int type)
{
	if (type >= 0 && type <= nbBullet - 1)
	{
		std::bitset<nbBullet> bit = std::bitset<nbBullet>(typeBalle);
		if (bit[type] == 0)
		{
				typeBalle += (int)pow(2, type);
		}
		else
			std::cout << "am�lioration d�j� mise\n";
	}
}

void CGunslinger::addByIndex(CBulletAuto& ref , int index)
{
	switch (index)
	{
	case classic:
		break;
	case dotBullet:
		ref.addBuff(new dot(NULL, referenceStat.dotDamage, referenceStat.dotCD, referenceStat.dotTimer), false);
	}
}


void CGunslinger::shootTowardDirection(sf::Vector2f initPos, sf::Vector2f targetPos)
{
	referenceStat.dir = utilities::dirAtoB(initPos, targetPos);
	//std::cout << "direction in x : " << dir.x << " in y : " << dir.y<<std::endl;
	iNeedMoreBullets(initPos);
}

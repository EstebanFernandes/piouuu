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
	typeTir = 0;
	typeBalle = (int)pow(2, 0);
	setType(Gunslinger);
	
}

void CGunslinger::updateEntity(float dt)
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

void CGunslinger::renderEntity(sf::RenderTarget& target)
{
		for (size_t i = 0; i < magasine.size(); i++)
		{
			magasine[i].renderEntity(target);
		}
}

void CGunslinger::iNeedMoreBullets(sf::Vector2f pos)
{
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
			if(i==0)
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
		for (int i = 0; i < 2; i++)
		{
			if (i == 0)
			{
				pos.y += 3.f;
				reference.setBulletPos(pos);
				magasine.push_back(reference);
			}
			else {
				initBuff(reference);
				pos.y -= 6.f;
				reference.setBulletPos(pos);
				magasine.push_back(reference);
				bulletSound.play();
			}
		}
		
	}
	break;
	case gunshotAim:
	{
		float yDirection = -0.75f;
		for (int i = 0; i < 7; i++)
		{
			if(i!=0)
			{
				initBuff(reference);
				bulletSound.play();
			}
		reference.setDirection(sf::Vector2f(1.f, yDirection));
		yDirection += 0.25f;
		magasine.push_back(reference);
		}
	}
	break;
	case bombe:
	{
		magasine.push_back(reference);
	}
		break;
	}
	bulletSound.play();
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
			std::cout << "amélioration déjà mise\n";
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
	sf::Vector2f dir;
	sf::Vector2f otherPos = initPos - targetPos;
	/*
	if (targetPos.x < initPos.x) {
		dir.x = -1;
	}
	else if (targetPos.x > initPos.x) {
		dir.x = 1;
	}
	else {
		dir.x = 0;
	}
	*/
	float a = otherPos.y / otherPos.x;

	dir.x = -1.f / (float)std::sqrt(1 + std::pow(a, 2));
	dir.y = a * dir.x;

	if (otherPos.x < 0) {
		dir.x = dir.x * -1;
		dir.y = dir.y * -1;
	}

	/*
	dir = targetPos - initPos;
	float max = std::abs(std::min(dir.x, dir.y));
	dir = dir / max;
	*/
	referenceStat.dir = dir;
	std::cout << "direction in x : " << dir.x << " in y : " << dir.y<<std::endl;
	iNeedMoreBullets(initPos);
}

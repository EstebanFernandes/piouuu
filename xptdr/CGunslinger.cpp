#include "CGunslinger.h"

CGunslinger::CGunslinger()
{
	setType(Gunslinger);
}

void CGunslinger::updateEntity(float dt)
{
	for (size_t i = 0; i < magazine.size(); i++)
	{
		if (magazine[i].needDelete == true)
		{
			magazine.erase(magazine.begin() + i);
			if (i != 0)
				i--;
			break;
		}
		magazine[i].updateEntity(dt);
		if(magazine[i].checkGlobalCollisions()==true)
		if (magazine[i].needDelete == true)
		{
			magazine.erase(magazine.begin() + i);
			if (i != 0)
				i--;
		}
	}
}

void CGunslinger::renderEntity(sf::RenderTarget& target)
{
	for (size_t i = 0; i < magazine.size(); i++)
	{
		magazine[i].renderEntity(target);
	}
}

void CGunslinger::updateCollision(CEntity& b)
{
	for (size_t i = 0; i < magazine.size(); i++)
	{
		magazine[i].updateCollision(b);

	}
}

void CGunslinger::iNeedMoreBullets(sf::Vector2f pos)
{
	magazine.push_back(CBullet(4, pos, sf::Vector2f(1, 0), assets));
}

void CGunslinger::iNeedMoreBullets(sf::Vector2f pos, int damage)
{
	magazine.push_back(CBullet(damage, pos, sf::Vector2f(1, 0), assets));
}

void CGunslinger::iNeedMoreBullets(sf::Vector2f pos, int damage, sf::Vector2f direction)
{

		magazine.push_back(CBullet(damage, pos, direction, assets));
}

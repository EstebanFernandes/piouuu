#include "CBulletAuto.h"

CBulletAuto::CBulletAuto()
{
}


//Pour update une balle chargée (qui peut avoir des comportements différents)
void CBulletAuto::updateEntity(float dt)
{
	//Auto Aim
	if (mob != NULL && mob->isDead == false)
	{
		sf::Vector2f pos = getSprite().getPosition();
		sf::Vector2f posMob = mob->getSprite().getPosition();
		sf::Vector2f dir;
		dir.x = posMob.x - pos.x;
		dir.y = posMob.y - pos.y;
		float max = std::abs(std::max(dir.x, dir.y));
		dir = dir / max;
		direction = dir;
		setDirectionSprite();
	}
	else if (mob != NULL && mob->isDead == true)
	{
		isMobSet = false;
		mob = NULL;
	}

	//Gunshot
	if (isGunShot)
	{
		if (gunshotDistance >= gunShotTotalDistance)
			needDelete = true;
	}

	//Normal behavior
	sf::Vector2f temp = direction;
	temp = temp * bulletSpeed * dt * 60.f;
	if (isGunShot)
		gunshotDistance += temp.x;
	getSprite().move(temp);
}


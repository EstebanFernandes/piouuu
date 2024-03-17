#include "InterfaceShootingEnemy.h"

void InterfaceShootingEnemy::updateShootWithPlayer(CPlayer& player)
{
	std::list<CBulletAuto>* bullets = BAW.getList();
	size_t temp = bullets->size();
	for (std::list<CBulletAuto>::iterator bullet = bullets->begin(); bullet != bullets->end(); /*++bullet*/) {
		if (bullet->checkCollisions(player))
		{
			player.reduceHP((float)bullet->getDamage());
			bullet = bullets->erase(bullet);
		}
		else
			++bullet;
	}
}

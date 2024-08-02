#include "InterfaceShootingEnemy.h"

void InterfaceShootingEnemy::updateShootWithPlayer(Player& player)
{
	for (Bullet* bullet : *BAW.getList())
	{
		if (bullet->checkCollisions(player))
		{
			player.reduceHP((float)bullet->getDamage());
			if (bullet->needDelete)
			{
				delete bullet;
			}
		}
	}


	//std::list<BulletAuto>* bullets = BAW.getList();
	//size_t temp = bullets->size();zz
	//for (std::list<BulletAuto>::iterator bullet = bullets->begin(); bullet != bullets->end(); /*++bullet*/) {
	//	if (bullet->checkCollisions(player))
	//	{
	//		player.reduceHP((float)bullet->getDamage());
	//		bullet = bullets->erase(bullet);
	//	}
	//	else
	//		++bullet;
	//}
}

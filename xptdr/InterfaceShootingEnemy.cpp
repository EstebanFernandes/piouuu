#include "InterfaceShootingEnemy.h"

void InterfaceShootingEnemy::updateShootWithPlayer(CPlayer& player)
{
	std::vector<CBulletAuto>* bullets = BAW.getVector();
	size_t temp = bullets->size();
	for (int i = 0; i < temp; i++) {
		if (player.checkCollisions((*bullets)[i])) {
			player.reduceHP((float)(*bullets)[i].getDamage());
			bullets->erase(bullets->begin() + i);
			if (i != 0)
				i--;
			temp--;
		}
	}
}

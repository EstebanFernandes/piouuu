#include "bulletStorage.h"

void bulletStorage::updatewPlayer(float delta, Player& player)
{

	for (Bullet* bullet : *saveBullet.getList())
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

	//std::list<BulletAuto>* bullets = saveBullet.getList();
	//size_t temp = bullets->size();
	//for (std::list<BulletAuto>::iterator it = bullets->begin(); it != bullets->end(); /*++it*/) {
	//	if (player.checkCollisions(*it)) {
	//		player.reduceHP((float)it->getDamage());
	//		it = bullets->erase(it);
	//	}
	//	else
	//		it++;
	//}
}

void bulletStorage::saveBullets(Gunslinger& otherGunslinger)
{
	//std::list<BulletAuto>& temp = otherGunslinger.getReferenceList();
	std::list<Bullet*>& temp = otherGunslinger.getReferenceList();
	if (!temp.empty())
	{
		std::copy(temp.begin(), temp.end(), std::back_inserter(saveBullet.getReferenceList()));
	}
}

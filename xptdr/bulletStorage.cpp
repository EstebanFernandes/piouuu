#include "bulletStorage.h"

void bulletStorage::updatewPlayer(float delta, CPlayer& player)
{
	std::list<CBulletAuto>* bullets = saveBullet.getList();
	size_t temp = bullets->size();
	for (std::list<CBulletAuto>::iterator it = bullets->begin(); it != bullets->end(); /*++it*/) {
		if (player.checkCollisions(*it)) {
			player.reduceHP((float)it->getDamage());
			it = bullets->erase(it);
		}
		else
			it++;
	}
}

void bulletStorage::saveBullets(CGunslinger& otherGunslinger)
{
	std::list<CBulletAuto>& temp = otherGunslinger.getReferenceList();
	if (!temp.empty())
	{
		std::copy(temp.begin(), temp.end(), std::back_inserter(saveBullet.getReferenceList()));
	}
}

#include "bulletStorage.h"

void bulletStorage::updatewPlayer(float delta, CPlayer& player)
{
	std::vector<CBulletAuto>* bullets = saveBullet.getVector();
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

void bulletStorage::saveBullets(CGunslinger& otherGunslinger)
{
	std::vector<CBulletAuto>& temp = otherGunslinger.getReferenceVector();
	if (!temp.empty())
	{
		for (int i = 0; i < temp.size();)
		{
			saveBullet.getReferenceVector().push_back(temp[i]);
			temp.erase(temp.begin() + i);
		}

	}
}

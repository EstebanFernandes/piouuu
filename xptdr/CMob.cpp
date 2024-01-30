#include "CMob.h"

void CMob::onHit(CMob& b)
{
	for (std::vector<buff>::iterator it = buffs.begin();
		it != buffs.end();)
	{
		it->effet->changeTarget(&b);
		b.addBuff(it->effet, true);;
		it = buffs.erase(it);
	}
}

CMob::CMob()
{ 
	healthPoint = 0;
	maxHealthPoint = 0;
}

void CMob::updateStates(CCharacter characterParam)
{
	imageName = characterParam.getImageName();
	name = characterParam.getName();
	description = characterParam.getDescription();
	//Character related

	//On remet l'xp et le level à 0
	level = 0;
	xp = 0;
	maxXp = characterParam.getMaxXp();
	healthPoint = characterParam.getLifePoint();
	maxHealthPoint = characterParam.getMaxHealth();
	moveSpeed = characterParam.getMoveSpeed();
	isAnimated = characterParam.getAnimated();

	canonNumber = characterParam.getCanonNumber();
	//Bullet 
	damagePerBullet = characterParam.getDamagePerBullet();
	attackSpeed = characterParam.getAttackSpeed();
	bulletSpeed = characterParam.getBulletSpeed();
}

void CMob::updateBuff(float delta)
{
	for (int index=0; index <buffs.size(); index++)
	{
		
		effetspecial* temp = buffs[index].effet;
		temp->update(delta);
		if (temp->needDelete)
		{
			delete(temp);
			buffs.erase(buffs.begin() + index);
		if (index != 0)
			index--;
		}
	}
}


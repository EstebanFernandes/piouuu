#include "CMob.h"

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
	level = characterParam.getLevel();
	xp = characterParam.getXp();
	maxXp = characterParam.getMaxXp();
	healthPoint = characterParam.getLifePoint();
	maxHealthPoint = characterParam.getMaxHealth();
	//float moveSpeed = characterParam.get;
	isAnimated = characterParam.getAnimated();

	//float canonNumber = characterParam.get;
	//Bullet 
	damagePerBullet = characterParam.getDamagePerBullet();
	//float attackSpeed = characterParam.get;
	//float bulletSpeed = characterParam.get;
}



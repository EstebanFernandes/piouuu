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

	specificites = characterParam.specificites;
}



#include "CCharacter.h"

CCharacter::CCharacter(std::string imagePathParam, std::string nameParam, std::string descriptionParam, bool animated)
{
	imageName = imagePathParam;
	name = nameParam;
	description = descriptionParam;
	isAnimated = animated;

	moveSpeed = 0.5f;
	maxHealthPoint = 20;
	healthPoint = maxHealthPoint;
	xp = 0;
	maxXp = 10;
	damagePerBullet = 5;
	attackSpeed = 8.f;
	level = 0;
	canonNumber = 1;
	bulletSpeed = 2.0f;
}

CCharacter::CCharacter()
{
	isAnimated = false;
	moveSpeed = 0.5f;
	maxHealthPoint = 20;
	healthPoint = maxHealthPoint;
	xp = 0;
	maxXp = 10;
	damagePerBullet = 5;
	attackSpeed = 8.f;
	level = 0;
	canonNumber = 1;
	bulletSpeed = 2.0f;
}

void CCharacter::setCharacterStats(int maxHealthPointParam, float moveSpeedParam, int canonNumberParam, int damagePerBulletParam, float attackSpeedParam, float BulletSpeedParam)
{
	maxHealthPoint = maxHealthPointParam;
	moveSpeed = moveSpeedParam;
	canonNumber = canonNumberParam;
	damagePerBullet = damagePerBulletParam;
	attackSpeed = attackSpeedParam;
	bulletSpeed = BulletSpeedParam;
	healthPoint = maxHealthPoint;
}

std::string CCharacter::getImageName()
{
	return imageName;
}

std::string CCharacter::getName()
{
	return name;
}

std::string CCharacter::getDescription()
{
	return description;
}

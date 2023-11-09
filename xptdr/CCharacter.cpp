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
}

CCharacter::CCharacter()
{
	moveSpeed = 0.5f;
	maxHealthPoint = 20;
	healthPoint = maxHealthPoint;
	xp = 0;
	maxXp = 10;
	damagePerBullet = 5;
	attackSpeed = 8.f;
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

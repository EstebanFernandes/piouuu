#include "CCharacter.h"

CCharacter::CCharacter(std::string imagePathParam, std::string nameParam, std::string descriptionParam)
{
	imagePath = imagePathParam;
	name = nameParam;
	description = descriptionParam;
}

CCharacter::CCharacter()
{
}

std::string CCharacter::getImagePath()
{
	return imagePath;
}

std::string CCharacter::getName()
{
	return name;
}

std::string CCharacter::getDescription()
{
	return description;
}

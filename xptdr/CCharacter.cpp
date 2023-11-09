#include "CCharacter.h"

CCharacter::CCharacter(std::string imagePathParam, std::string nameParam, std::string descriptionParam)
{
	imageName = imagePathParam;
	name = nameParam;
	description = descriptionParam;
}

CCharacter::CCharacter()
{
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

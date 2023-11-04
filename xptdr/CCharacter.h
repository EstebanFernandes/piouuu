#pragma once
#include <string>

class CCharacter
{
public:
	CCharacter(std::string imagePathParam, std::string nameParam, std::string descriptionParam);
	CCharacter();

	std::string getImagePath();
	std::string getName();
	std::string getDescription();
private :
	std::string imagePath;
	std::string name;
	std::string description;
};


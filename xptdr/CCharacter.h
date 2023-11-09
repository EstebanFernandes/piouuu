#pragma once
#include <string>
//Cette classe contient tous les élements nécessaire pour faire fonctionner un personnage (allié ou ennemie)
class CCharacter
{
protected :
	//Information for system
	std::string imageName;
	std::string name;
	std::string description;
	//Character related
	int level;
	int xp;
	int maxXp;
	int healthPoint;
	int maxHealthPoint;
	float moveSpeed;
	bool isAnimated;

	float canonNumber;
	//Bullet 
	int damagePerBullet;
	float attackSpeed;
	float bulletSpeed;

	//Misc
	//Jsp quoi mettre pour l'instant
public:
	CCharacter(std::string imagePathParam, std::string nameParam, std::string descriptionParam, bool animated);
	CCharacter();

	std::string getImageName();
	std::string getName();
	std::string getDescription();
	int getMaxHealth() { return maxHealthPoint; }
	int getLifePoint() { return healthPoint; }
	int getLevel() { return level; }
	int getXp() { return xp; }
	int getMaxXp() { return maxXp; }
	int getDamagePerBullet() { return damagePerBullet; }
	bool getAnimated() { return isAnimated; }

};


#pragma once
#include <string>
#include <vector>
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

	int canonNumber;
	//Bullet 
	int damagePerBullet;
	float attackSpeed;
	float bulletSpeed;

	//Misc

public:
	//static const std::vector<std::string> typeString;
	int nbspecifities = 0;
	std::vector<std::string> specificites;
	CCharacter(std::string imagePathParam, std::string nameParam, std::string descriptionParam, bool animated);
	CCharacter();

	void setCharacterStats(int maxHealthPointParam, float moveSpeedParam, int canonNumberParam, int damagePerBulletParam, float attackSpeedParam, float BulletSpeedParam);

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
	float getMoveSpeed() { return moveSpeed;  }

	int getCanonNumber() { return canonNumber;  }
	float getAttackSpeed() { return attackSpeed; }
	float getBulletSpeed() { return bulletSpeed; }
	bool matchTypewithValue(std::string type, std::string value);
	static std::string returnTypeStylish(std::string type,std::string value);
};


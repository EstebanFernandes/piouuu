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
	float healthPoint;
	float maxHealthPoint;
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
	std::vector<std::string> specificites;
	CCharacter(std::string imagePathParam, std::string nameParam, std::string descriptionParam, bool animated);
	CCharacter();

	void setCharacterStats(float maxHealthPointParam, float moveSpeedParam, int canonNumberParam, int damagePerBulletParam, float attackSpeedParam, float BulletSpeedParam);

	std::string getImageName();
	std::string getName();
	std::string getDescription();

	float getMaxHealth() { return maxHealthPoint; }
	void setMaxHealth(float maxHealthParam) { maxHealthPoint = maxHealthParam; healthPoint = maxHealthParam; }

	float getLifePoint() { return healthPoint; }
	void setLifePoint(float lifePointParam) { 
		if (lifePointParam < 0)
			healthPoint = 0;
		else
			healthPoint = lifePointParam;
	}

	int getLevel() { return level; }
	void setLevel(int levelParam) { level = levelParam; }

	int getXp() { return xp; }
	int getMaxXp() { return maxXp; }

	int getDamagePerBullet() { return damagePerBullet; }
	void setDamagePerBullet(int damagePerBulletParam) { damagePerBullet = damagePerBulletParam; }

	bool getAnimated() { return isAnimated; }

	float getMoveSpeed() { return moveSpeed;  }
	void setMoveSpeed(float moveSpeedParam) { moveSpeed = moveSpeedParam; }

	int getCanonNumber() { return canonNumber;  }

	float getAttackSpeed() { return attackSpeed; }
	void setAttackSpeed(float attackSpeedParam) { attackSpeed = attackSpeedParam; }

	float getBulletSpeed() { return bulletSpeed; }
	void setBulletSpeed(float bulletSpeedParam) { bulletSpeed = bulletSpeedParam; }
	bool matchTypewithValue(std::string type, std::string value);
	static std::string returnTypeStylish(std::string type,std::string value);
};


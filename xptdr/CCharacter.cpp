#include "CCharacter.h"
#include<string>
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

bool CCharacter::matchTypewithValue(std::string type, std::string value)
{
	std::vector<std::string> typeString = {"maxXp","healthPoint","maxHealthPoint",
										"moveSpeed","canonNumber","damagePerBullet",
											"attackSpeed","bulletSpeed","misc"};
	int pos = (int)(std::find(typeString.begin(), typeString.end(), type) - typeString.begin());
	if (pos >= typeString.size()) {
		return false;
	}
	else {
		if (value != "")
		{
			switch (pos)
			{
			case 0: //Max XP
				switch (value[0])
				{
				case '*':
					maxXp = maxXp * std::stoi(value.substr(1));
					break;
				case '+':
					maxXp = maxXp + std::stoi(value.substr(1));
					break;
				case '-':
					maxXp = maxXp - std::stoi(value.substr(1));
					break;
				default:
					maxXp = std::stoi(value);
					break;
				}
				break;
			case 1:  //Health Point
				switch (value[0])
				{
				case '*':
					healthPoint = healthPoint * std::stoi(value.substr(1));
					break;
				case '+':
					healthPoint = healthPoint + std::stoi(value.substr(1));
					break;
				case '-':
					healthPoint = healthPoint - std::stoi(value.substr(1));
					break;
				default:
					healthPoint = std::stoi(value);
					break;
				}
				break;
			case 2: // Max HealthPoint
				switch (value[0])
				{
				case '*':
					maxHealthPoint = maxHealthPoint * std::stoi(value.substr(1));
					break;
				case '+':
					maxHealthPoint = maxHealthPoint + std::stoi(value.substr(1));
					break;
				case '-':
					maxHealthPoint = maxHealthPoint - std::stoi(value.substr(1));
					break;
				default:
					maxHealthPoint = std::stoi(value);
					break;
				}
				break;
			case 3: //move Speed
				switch (value[0])
				{
				case '*':
					moveSpeed = moveSpeed * std::stof(value.substr(1));
					break;
				case '+':
					moveSpeed = moveSpeed + std::stof(value.substr(1));
					break;
				case '-':
					moveSpeed = moveSpeed - std::stof(value.substr(1));
					break;
				default:
					moveSpeed = std::stof(value);
					break;
				}
				break;
			case 4: //canon number
				switch (value[0])
				{
				case '*':
					canonNumber = canonNumber * std::stoi(value.substr(1));
					break;
				case '+':
					canonNumber = canonNumber + std::stoi(value.substr(1));
					break;
				case '-':
					canonNumber = canonNumber - std::stoi(value.substr(1));
					break;
				default:
					canonNumber = std::stoi(value);
					break;
				}
				break;
			case 5: //DamagePerBullet
				switch (value[0])
				{
				case '*':
					damagePerBullet = damagePerBullet * std::stoi(value.substr(1));
					break;
				case '+':
					damagePerBullet = damagePerBullet + std::stoi(value.substr(1));
					break;
				case '-':
					damagePerBullet = damagePerBullet - std::stoi(value.substr(1));
					break;
				default:
					damagePerBullet = std::stoi(value);
					break;
				}
				break;
			case 6: //attack speed
					switch (value[0])
				{
				case '*':
					attackSpeed = attackSpeed * std::stof(value.substr(1));
					break;
				case '+':
					attackSpeed = attackSpeed + std::stof(value.substr(1));
					break;
				case '-':
					attackSpeed = attackSpeed - std::stof(value.substr(1));
					break;
				default:
					attackSpeed = std::stof(value);
					break;
				}
				break;
			case 7: // bullet speed
				switch (value[0])
				{
				case '*':
					bulletSpeed = bulletSpeed * std::stof(value.substr(1));
					break;
				case '+':
					bulletSpeed = bulletSpeed + std::stof(value.substr(1));
					break;
				case '-':
					bulletSpeed = bulletSpeed - std::stof(value.substr(1));
					break;
				default:
					bulletSpeed = std::stof(value);
					break;
				}
				break;
			case 8: //misc
				switch (value[0])
				{
				case '*':
					return false;
					break;
				case '+':
					return false;
					break;
				case '-':
					return false;
					break;
				default:
					specificites.push_back(value);
					break;
				}
				break;
			}
		}
		return true;
	}
}

std::string CCharacter::getImageName()
{
	return imageName;
}

std::string CCharacter::getName()
{
	return name;
}

std::string CCharacter::getDescription(){
	return description;
}

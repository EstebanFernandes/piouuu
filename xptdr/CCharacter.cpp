#include "CCharacter.h"
#include<string>
CCharacter::CCharacter(std::string imagePathParam, std::string nameParam, std::string descriptionParam, bool animated)
{
	imageName = imagePathParam;
	name = nameParam;
	description = descriptionParam;
	isAnimated = animated;

	moveSpeed = 0.5f;
	maxHealthPoint = 20.f;
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
	canonNumber = 40;
	bulletSpeed = 2.0f;
}

void CCharacter::setCharacterStats(float maxHealthPointParam, float moveSpeedParam, int canonNumberParam, int damagePerBulletParam, float attackSpeedParam, float BulletSpeedParam)
{
	maxHealthPoint = maxHealthPointParam;
	moveSpeed = moveSpeedParam;
	canonNumber = canonNumberParam;
	damagePerBullet = damagePerBulletParam;
	attackSpeed = attackSpeedParam;
	bulletSpeed = BulletSpeedParam;
	healthPoint = maxHealthPoint;
}

void CCharacter::setCharacterStats(CCharacter ch)
{
	maxHealthPoint = ch.maxHealthPoint;
	moveSpeed = ch.moveSpeed;
	canonNumber = ch.canonNumber;
	damagePerBullet = ch.damagePerBullet;
	attackSpeed = ch.attackSpeed;
	bulletSpeed = ch.bulletSpeed;
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
					healthPoint = std::stof(value);
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
					maxHealthPoint = std::stof(value);
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
/// <summary>
/// Méthode qui prend en paramètre un des types d'améliorations avec le nom interne et renvoie le nom jolie
/// </summary>
/// <param name="type"></param>
/// <param name="value"></param>
/// <returns></returns>
std::string CCharacter::returnTypeStylish(std::string type, std::string value)
{
	std::string operatorandvalue;
	std::string returnType;
	std::vector<std::string> typeString = { "maxXp","healthPoint","maxHealthPoint",
	"moveSpeed","damagePerBullet","attackSpeed","bulletSpeed",
		"misc","dashDistance","dashDamage","isDashInvicible",
	"dotCD","dotTimer","dotDamage","factor","penetration" };
	int pos = (int)(std::find(typeString.begin(), typeString.end(), type) - typeString.begin());
	if (type == "dotDamage")
		pos = 13;
	if (pos >= typeString.size()) {
		return "";
	}
	else {
		if (value != "")
		{
			bool isMisc = false;
			float fvalue = 0.f;
			int ivalue = 0;
			switch (value[0])
			{
			case '*':
				fvalue = std::stof(value.substr(1));
				ivalue = 0;
				if (fvalue > 1.f)
				{
					ivalue = (int)((fvalue - 1.f) * 100.f);
					operatorandvalue = "+" + std::to_string(ivalue) + "%";
				}
				else
				{
					ivalue = (int)(ceil((double)(abs(fvalue - 1.f) * 100.f)));
					operatorandvalue = "-" + std::to_string(ivalue) + "%";
				}
				break;
			case '+':
				operatorandvalue = "+" + value.substr(1);
				break;
			case '-':
				operatorandvalue = "-" + value.substr(1);
				break;
			default:
				operatorandvalue = value;
				break;
			}
			switch (pos)
			{
			case 0: //Max XP
				returnType = "Max xp : ";
				break;
			case 1:  //Health Point
				returnType = "Point de vie : ";
				break;
			case 2: // Max HealthPoint
				returnType = "Point de vie maximum : ";
				break;
			case 3: //move Speed
				returnType = "Vitesse de déplacement : ";
				break;
			case 4: //DamagePerBullet
				returnType = "Dégat par balles : ";
				break;
			case 5: //attack speed
				returnType = "Vitesse d'attaque : ";
				break;
			case 6: // bullet speed
				returnType = "Vitesse d'une balle : ";
				break;
			case 7: //misc
				returnType = "Spécifité : ";
				isMisc = true;
				break;
			case 8: //dash distance
				returnType = "Distance de dash : ";
				break;

			case 9: // dash damage
				returnType = "Dégat du dash : ";
				break;
			case 10: //isDashInvicible
				bool temp;
				if (value == "true" || value == "1")
				{
				returnType = "Le dash rend invincible : ";
				}
				else if (value == "false" || value == "0")
				{
					returnType = "Le dash ne rend plus in : ";
				}
				break;
			case 11: //dotCD
				returnType = "Dégats tous les ";
				operatorandvalue = value + " s";
				break;
			case 12: //dotTimer
				returnType = "Temps total du buff : ";
				operatorandvalue = value + " s";
				break;
			case 13: // dotDamage
				returnType = "Dégat du buff : ";
				break;
			case 14: //Factor(j'attends le merge avec mathéo)
				returnType = "Facteur du buff : ";
				break;
			case 15: //Penetration(j'attends le merge avec mathéo)
				returnType = "Penetration de la balle : ";
				break;
			} 
			if (isMisc)
			{
				const std::vector<std::string> supportedMisc{ "autoAim","doubleTirs1","doubleTirs2",
				"gunshot","dot", "laser","explosiveBullet","spin","doubleTirs3","fire","ice","thunder" };
				 pos = (int)(std::find(supportedMisc.begin(), supportedMisc.end(), value) - supportedMisc.begin());
				switch (pos)
				{
				case 0: //Max XP
					operatorandvalue = "Visée automatique";
					break;
				case 1:  //Health Point
					operatorandvalue = "Double tirs v1";
					break;
				case 2: // Max HealthPoint
					operatorandvalue = "Double tirs v2";
					break;
				case 3: //move Speed
					operatorandvalue = "Tir courte portée";
					break;
				case 4: //DamagePerBullet
					operatorandvalue = "Dégat sur la durée";
					break;
				case 5: //attack speed
					operatorandvalue = "Puissant laser";
					break;
				case 6: // bullet speed
					operatorandvalue = "Balle explosive";
					break;
				case 7: //misc
					operatorandvalue = "Merry go round";
					break;
				case 8: //dash distance
					operatorandvalue = " Triple tirs ";
					break;

				case 9: // dash damage
					operatorandvalue = "Feu ";
					break;
				case 10: //isDashInvicible
					operatorandvalue = "Glace";
					break;
				case 11: //dotCD
					operatorandvalue = "Foudre";
					break;
			
				}
			}
		}
		return returnType + operatorandvalue;
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

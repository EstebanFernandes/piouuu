#include "CBulletAuto.h"

CBulletAuto::CBulletAuto() : CBullet()
{

}

CBulletAuto::CBulletAuto(CWeaponStat stat,CAssetManager* a)
{
	penetration = stat.penetration;
	damage = (int)stat.bulletDamage;
	bulletSpeed = stat.bulletSpeed;
	direction = stat.dir;
	setType(FriendlyFire);
	assets = a;
	setSprite(stat.nameImage);
	getSprite().setScale(stat.bulletScale);
	bulletScale = stat.bulletScale;
	if (stat.maxDistance != -1)
	{
		isGunShot = true;
		gunShotTotalDistance = stat.maxDistance;
	}
}

CBulletAuto::CBulletAuto(int damage, float bulletSpeed, sf::Vector2f dir, int penetration, std::string nameImage, sf::Vector2f bulletScale_, CAssetManager* a)
{
	this->penetration = penetration;
	this->damage = damage;
	this->bulletSpeed = bulletSpeed;
	direction = dir;
	setType(FriendlyFire);
	assets = a;
	setSprite(nameImage);
	getSprite().setScale(bulletScale_);
	bulletScale = bulletScale_;

}

CBulletAuto::CBulletAuto(int daamg, sf::Vector2f pos, float bulletSpeeed, sf::Vector2f dir, int penetration, std::string nameImage, CAssetManager* as, sf::Vector2f bulletScale, bool isABombe) : CBullet(daamg, pos, dir, bulletSpeeed, penetration, nameImage, as, bulletScale)
{
	isABombe = true;
	CEntity::setRotation(0);
}


//Pour update une balle chargée (qui peut avoir des comportements différents)
void CBulletAuto::updateEntity(float dt)
{
	//Auto Aim
	if (mob != NULL && mob->isDead == false)
	{
		sf::Vector2f pos = getSprite().getPosition();
		sf::Vector2f posMob = mob->getSprite().getPosition();
		sf::Vector2f dir;
		dir.x = posMob.x - pos.x;
		dir.y = posMob.y - pos.y;
		float max = std::abs(std::max(dir.x, dir.y));
		dir = dir / max;
		direction = dir;
		setDirectionSprite();
	}
	else if (mob != NULL && mob->isDead == true)
	{
		isMobSet = false;
		mob = NULL;
	}

	//Gunshot
	if (isGunShot)
	{
		if (gunshotDistance >= gunShotTotalDistance)
			needDelete = true;
	}

	//Normal behavior
	sf::Vector2f temp = direction;
	if (!isABombe) {
		temp.x = temp.x * bulletSpeed * dt * 60.f;
	}
	else {
		temp.y = temp.y * bulletSpeed * dt * 60.f;
	}
	if (isGunShot)
		gunshotDistance += temp.x;
	getSprite().move(temp);
}


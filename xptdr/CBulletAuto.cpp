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

CBulletAuto::CBulletAuto(int daamg, sf::Vector2f pos, float bulletSpeeed, sf::Vector2f dir, int penetration, std::string nameImage, CAssetManager* as, sf::Vector2f bulletScale, bool isABombe) 
	: CBullet(daamg, pos, dir, bulletSpeeed, penetration, nameImage, as, bulletScale)
{
	direction = sf::Vector2f(0.f, 1.f);
	setRotation(0);
}


//Pour update une balle chargée (qui peut avoir des comportements différents)
void CBulletAuto::updateEntity(float dt)
{
	if (isThisIt)
	{
		penetration--;
		if (penetration == -2)
			needDelete = true;
	}
	else {
		//Auto Aim
		if (mob != NULL && mob->isDead == false)
		{
			sf::Vector2f pos = getSprite().getPosition();
			sf::Vector2f posMob = mob->getSprite().getPosition();
			direction = utilities::dirAtoB(pos, posMob);
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
		temp = temp * bulletSpeed * dt * 60.f;
		if (isAnimated)
		{
			anim.updateAnimation();
			//anim.debug();
		}

		if (isGunShot)
			gunshotDistance += temp.x;
		getSprite().move(temp);
	}
}

void CBulletAuto::setAnimation(CAnimation e)
{
	isAnimated = true;
	anim = e;
	//anim.setSprite(getPointerSprite());
}

bool CBulletAuto::checkCollisions(CMob& b)
{
	if (isThisIt)
	{
		if(!b.isDead)
		{
			if (b.getSprite().getGlobalBounds().intersects(hitbox.getGlobalBounds()))
				return true;
		}
		return false;
	}
	bool result = CBullet::checkCollisions(b);
	if(result&& isExplosive&& needDelete)//On a une balle explose en fin de vie
	{

		isThisIt = true;
		hitbox.setFillColor(sf::Color(255, 255, 255, 100));
		hitbox.setSize(sf::Vector2f(200.f, 200.f));
		hitbox.setOrigin(hitbox.getLocalBounds().width / 2.f, hitbox.getLocalBounds().height / 2.f );
		hitbox.setPosition(getSprite().getPosition());
		needDelete = false;
	}
	else {
		return result;
	}
	return result;
}

void CBulletAuto::renderEntity(sf::RenderTarget& target)
{
	//if (isThisIt)
		target.draw(hitbox);
	CBullet::renderEntity(target);
}


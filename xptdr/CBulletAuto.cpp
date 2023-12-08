#include "CBulletAuto.h"

CBulletAuto::CBulletAuto()
{
}

CBulletAuto::CBulletAuto(int damaage, sf::Vector2f pos, CMob* mob_, CAssetManager* assetss) :
	CBullet(damaage,pos,sf::Vector2f(1.f,0.f),assetss)
{
	mob = mob_;
}

CBulletAuto::CBulletAuto(int damaage, sf::Vector2f pos, CMob* mob_, float bulletSpeed, CAssetManager* assetss) :
	CBullet(damaage, pos, sf::Vector2f(1.f, 0.f),bulletSpeed, assetss)
{
	mob = mob_;
}

void CBulletAuto::updateEntity(float dt)
{
	//Auto Aim
	if (mob != NULL&& mob->isDead==false)
	{
	sf::Vector2f pos = getSprite().getPosition();
	pos.x += getSprite().getGlobalBounds().width / 2.f;
	pos.y += getSprite().getGlobalBounds().height / 2.f;
	sf::Vector2f posMob = mob->getSprite().getPosition();
	posMob.x += mob->getSprite().getGlobalBounds().width / 2.f;
	posMob.y += mob->getSprite().getGlobalBounds().height / 2.f;
	sf::Vector2f dir;
	dir.x = posMob.x - pos.x;
	dir.y = posMob.y - pos.y;
	dir = dir / std::max(dir.x, dir.y);
	direction = dir;	
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
	if (isGunShot)
		gunshotDistance += temp.x;
	getSprite().move(temp);
}


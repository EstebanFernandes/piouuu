#include "CBulletAuto.h"

CBulletAuto::CBulletAuto()
{
}

CBulletAuto::CBulletAuto(int damaage, sf::Vector2f pos, CMob* mob_, std::string nameImage, CAssetManager* assetss) :
	CBullet(damaage,pos,sf::Vector2f(1.f,0.f), nameImage,assetss)
{
	mob = mob_;
	setRotation();
}

CBulletAuto::CBulletAuto(int damaage, sf::Vector2f pos, CMob* mob_, float bulletSpeed,std::string nameImage, CAssetManager* assetss) :
	CBullet(damaage, pos, sf::Vector2f(1.f, 0.f),bulletSpeed,nameImage, assetss)
{
	mob = mob_;
	setRotation();
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
		dir = dir / std::max(dir.x, dir.y);
		direction = dir;
		setDirectionSprite();
	}
	else if (mob != NULL && mob->isDead == true)
		isMobSet = false;

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


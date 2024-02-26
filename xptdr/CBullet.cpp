#include "CBullet.h"




CBullet::CBullet()
{
	damage=0;
}

CBullet::CBullet(int damaage, sf::Vector2f pos, sf::Vector2f dir , int penetration
	,std::string nameImage, CAssetManager* assetss)
{
	this->penetration = penetration;
	setType(FriendlyFire);
	assets = assetss;
	setSprite(nameImage);
	direction = dir;
	if (!isABombe) {
		setDirectionSprite();
	}
	damage = damaage;
	getSprite().setPosition(pos);
}

CBullet::CBullet(int damaage, sf::Vector2f pos, sf::Vector2f dir, float bulletSpeed_, int penetration, std::string nameImage, CAssetManager* assetss, sf::Vector2f bulletScale)
{
	this->penetration = penetration;
	bulletSpeed = bulletSpeed_;
	setType(FriendlyFire);
	assets = assetss;
	setSprite(nameImage);
	getSprite().setScale(bulletScale);
	direction = dir;
	if (!isABombe) {
		setDirectionSprite();
	}
	damage = damaage;
	getSprite().setPosition(pos);
}



void CBullet::setSprite(std::string nameImage)
{
	if (nameImage == "")
		nameImage = "bulletImage";
	setTexture(nameImage);
}

void CBullet::updateEntity(float dt)
{
	sf::Vector2f temp = direction;
	if (!isABombe) {
		temp.x = bulletSpeed * dt * 60.f;
	}
	else {
		temp.y = bulletSpeed * dt * 60.f;
	}
	getSprite().move(temp);
}


void CBullet::renderEntity(sf::RenderTarget& target)
{
	target.draw(getSprite());
}

void CBullet::setDirectionSprite()
{
	setRotation(utilities::getAngleFromDirection(direction));
}





bool CBullet::checkCollisions(CMob& b)
{
	auto ret = std::find(entityHitting.begin(), entityHitting.end(), &b);
	if (CEntity::checkCollisions(b)&&!b.isDead)
	{//les deux entit�s sont en contact
	//L'�lement n'est pas dans la liste, donc la balle n'est pas entrain de taper cette entit�
		if (ret == entityHitting.end() && penetration >= 0)
		{
			if (penetration == 0)
				needDelete = true;
			penetration--;
			entityHitting.push_back(&b);
			onHit(b);
			return true;
		}

	}
	else {//Les deux entit�s ne sont plus en contact
		if (ret != entityHitting.end())
		{
			entityHitting.erase(ret);
		}

	}
	return false;
}

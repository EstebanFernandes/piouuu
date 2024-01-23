#include "CBullet.h"


CBullet::CBullet()
{

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

void CBullet::updateCollision(CEntity& b)
{
	
}

void CBullet::renderEntity(sf::RenderTarget& target)
{
	target.draw(getSprite());
}

void CBullet::setDirectionSprite()
{
	float firstPart = atan2(direction.y, direction.x);
	float angle = (180.f / 3.1415926535897932384626f) * firstPart;
	//ce premier cas de figure induit que le sprite va de droite à gauche, dans ce cas si son angle
	// est supérieur à 90 degré il faut le flip pour qu'il soit dans le bon sens
	while (angle < 0.f)
	{
		angle += 360.f;
	}
	setRotation(angle);
}

void CBullet::CONTACT()
{
	if (penetration == 0)
		needDelete = true;
	else
		penetration--;
	isHitting = true;
}

bool CBullet::checkCollisions(CEntity& b)
{
	auto ret = std::find(entityHitting.begin(), entityHitting.end(), &b);
	if (CEntity::checkCollisions(b))
	{//les deux entités sont en contact
	//L'élement n'est pas dans la liste, donc la balle n'est pas entrain de taper cette entité
		if (ret == entityHitting.end()&&penetration>=0)
		{
			if (penetration == 0)
				needDelete = true;
				penetration--;
			entityHitting.push_back(&b);
			return true;
		}

	}
	else {//Les deux entités ne sont en contact
		if (ret != entityHitting.end())
		{
			entityHitting.erase(ret);
		}
		
	}
	return false;
}

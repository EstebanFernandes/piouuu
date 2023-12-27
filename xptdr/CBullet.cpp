#include "CBullet.h"


CBullet::CBullet()
{

}

CBullet::CBullet(int damaage, sf::Vector2f pos, sf::Vector2f dir, std::string nameImage, CAssetManager* assetss)
{
	setType(FriendlyFire);
	assets = assetss;
	setSprite(nameImage);
	direction = dir;
	setDirectionSprite();
	damage = damaage;
	getSprite().setPosition(pos);
}

CBullet::CBullet(int damaage, sf::Vector2f pos, sf::Vector2f dir, float bulletSpeed_, std::string nameImage, CAssetManager* assetss) 
{
	bulletSpeed = bulletSpeed_;
	setType(FriendlyFire);
	assets = assetss;
	setSprite(nameImage);
	direction = dir;
	setDirectionSprite();
	damage = damaage;
	getSprite().setPosition(pos);
}


void CBullet::setSprite(std::string nameImage)
{
	if (nameImage == "")
		nameImage = "bulletImage";
	getSprite().setTexture(assets->GetTexture(nameImage));
}

void CBullet::updateEntity(float dt)
{
	sf::Vector2f temp = direction;
	temp.x = temp.x * bulletSpeed * dt * 60.f;
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
	float firstPart = atan2(direction.y, direction.y);
	float angle = (180.f / 3.1415926535897932384626f) * firstPart;
	//ce premier cas de figure induit que le sprite va de droite à gauche, dans ce cas si son angle
	// est supérieur à 90 degré il faut le flip pour qu'il soit dans le bon sens
	if (angle < 0.f)
	{
		angle += 90;
		angle += 360;
	}
	else
		std::cout<<"";
	setRotation(angle);
}

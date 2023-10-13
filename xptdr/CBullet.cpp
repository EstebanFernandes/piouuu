#include "CBullet.h"


CBullet::CBullet(int damaage, sf::Vector2f pos, sf::Vector2f dir, CAssetManager* assetss)
{
	setType(FriendlyFire);
	assets = assetss;
	setSprite();
	direction = dir;
	damage = damaage;
	getSprite().setPosition(pos);
}

void CBullet::setSprite()
{
	setTexture("bulletImage", "res\\img\\bulletImage.png");
	assets->GetTexture("bulletImage").setSmooth(true);
		getSprite().setColor(sf::Color::Yellow);
}

void CBullet::updateEntity(float dt)
{
	sf::Vector2f temp = direction;
	temp.x = temp.x * bulletSpeed * dt * 60.f;
	getSprite().move(temp);
}

void CBullet::updateCollision(CEntity& b)
{
	switch (b.getType())
	{
	case Enemy:
		if (checkCollisions(b))
		{
			if(b.isDead==false)
			{
				needDelete = true;
				b.damagetaken -= damage;
			}
		}
		break;
	default:
		break;

	}
}

void CBullet::renderEntity(sf::RenderTarget& target)
{
	target.draw(getSprite());
}

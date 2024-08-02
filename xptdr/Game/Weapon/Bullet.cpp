#include "Bullet.h"


Bullet::~Bullet()
{

}

Bullet::Bullet()
{
	damage=0;
}

Bullet::Bullet(const Bullet& bullet)
{
	this->operator=(bullet);
}

Bullet& Bullet::operator=(const Bullet& bullet)
{
	if (this == &bullet) return *this;
	assets = bullet.assets;
	imageName = bullet.imageName;
	direction = bullet.direction;
	bulletScale = bullet.bulletScale;
	bulletSpeed = bullet.bulletSpeed;
	damage = bullet.damage;
	penetration = bullet.penetration;
	distance = bullet.distance;
	entityHitting = bullet.entityHitting;
	buffs = bullet.copyBuff();
	setSprite(imageName);
	getSprite().setScale(bulletScale);
	return *this;
}


Bullet::Bullet(int damaage, sf::Vector2f pos, sf::Vector2f dir , int penetration
	,std::string nameImage, AssetManager* assetss)
{
	this->penetration = penetration;
	setType(FriendlyFire);
	assets = assetss;
	setSprite(nameImage);
	direction = dir;
	/*if (!isABombe) {
		setDirectionSprite();
	}*/
	damage = damaage;
	getSprite().setPosition(pos);
}

Bullet::Bullet(int damaage, sf::Vector2f pos, sf::Vector2f dir, float bulletSpeed_, int penetration, std::string nameImage, AssetManager* assetss, sf::Vector2f bulletScale)
{
	this->penetration = penetration;
	bulletSpeed = bulletSpeed_;
	setType(FriendlyFire);
	assets = assetss;
	setSprite(nameImage);
	getSprite().setScale(bulletScale);
	direction = dir;
	/*if (!isABombe) {
		setDirectionSprite();
	}*/
	damage = damaage;
	getSprite().setPosition(pos);
}

Bullet::Bullet(WeaponStat stat, AssetManager* a)
{
	assets = a;
	setStat(stat);
	setSprite(stat.nameImage);
	getSprite().setScale(stat.bulletScale);
}



void Bullet::setSprite(std::string nameImage)
{
	if (nameImage == "")
		nameImage = "bulletImage";
	setTexture(nameImage);
}

void Bullet::updateEntity(float dt)
{
	sf::Vector2f temp = direction;
	temp = temp*bulletSpeed * dt * 60.f;
	//temp.y = bulletSpeed * dt * 60.f;
	distance += utilities::renvoieNormeVecteur(temp);
	getSprite().move(temp);
	if (checkGlobalCollisions())
		needDelete = true;
}


void Bullet::renderEntity(sf::RenderTarget& target)
{
	target.draw(getSprite());
}

void Bullet::setSprite()
{
}

void Bullet::setDirectionSprite()
{
	setRotation(utilities::getAngleFromDirection(direction));
}



bool Bullet::checkCollisions(Mob& b)
{
	auto ret = std::find(entityHitting.begin(), entityHitting.end(), &b);
	if (Entity::checkCollisions(b)&&!b.isDead)
	{//les deux entités sont en contact
	//L'élement n'est pas dans la liste, donc la balle n'est pas entrain de taper cette entité
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
	else {//Les deux entités ne sont plus en contact
		if (ret != entityHitting.end())
		{
			entityHitting.erase(ret);
		}

	}
	return false;
}

void Bullet::setStat(WeaponStat& stat)
{
	penetration = stat.penetration;
	damage = (int)stat.bulletDamage;
	bulletSpeed = stat.bulletSpeed;
	direction = stat.dir;
	imageName = stat.nameImage;
	bulletScale = stat.bulletScale;
}

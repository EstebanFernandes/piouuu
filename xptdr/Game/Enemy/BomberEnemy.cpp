#include "BomberEnemy.h"

BomberEnemy::BomberEnemy(AssetManager* assets) 
{
	initEnnemy(assets,info, "bomber");
	initPosition();
	initDirection();
	BAW.assets = assets;
	setSprite();
	setMoveSpeed(0.5f);
	setBulletSpeed(1.2f);
	setAttackSpeed(1.f);
	rotate(180.f);
	sf::Vector2f bulletScale = sf::Vector2f(0.5f, 0.5f);
	BAW.setWeaponStats(WeaponStat((float)damagePerBullet, bulletSpeed, sf::Vector2f(0.f, 1.f), 0, "bombe", bulletScale, attackSpeed));
	BAW.setWeaponPos(sf::Vector2f(0.f, getSprite().getGlobalBounds().height / 2.f));
	BAW.addShootType(typeAim::bombe);
	assets->addSFX("bulletSound", &BAW.bulletSound);
	isAnimated = false;
}

BomberEnemy::BomberEnemy(AssetManager* assets, enemyInfo info_) :
	BomberEnemy(assets)
{
	setInfo(info_);
	initDirection();
	setSprite();
}

BomberEnemy::BomberEnemy(AssetManager* assets, Character stat, WeaponStat WStat, enemyInfo info_)
	: BomberEnemy(assets)
{
	info = info_;
	setCharacterStats(stat);
	BAW.setWeaponStats(WStat);
	BAW.setWeaponPos(sf::Vector2f(0.f, getSprite().getGlobalBounds().height / 2.f));
	sf::Vector2f tempDirection(0.f, 1.f);
	BAW.getWeaponStats().changeDir(tempDirection);
	BAW.addShootType(typeAim::bombe);
}

void BomberEnemy::enemyShoot()
{
	if (bulletClock.getElapsedTime().asSeconds() >= 1.f / BAW.getWeaponStats().attackSpeed) {
		BAW.iNeedMoreBullets(getSprite().getPosition()+BAW.getWeaponPos());
		// vient juste le restart le timer à la fin 
		bulletClock.restart();
	}
}

void BomberEnemy::renderEntity(sf::RenderTarget& target)
{
	RoamingEnemy::renderEntity(target);
	BAW.renderWeapon(target);
}

void BomberEnemy::updateEntity(float delta)
{
	RoamingEnemy::updateEntity(delta);
	BAW.updateWeapon(delta);
	if(!isDead)
		enemyShoot();
}

void BomberEnemy::updatewPlayer(float delta, Player& player)
{
	RoamingEnemy::updatewPlayer(delta, player);
	updateShootWithPlayer(player);
	if (needDelete)
		transferBullet(BAW);
}

void BomberEnemy::initDirection()
{
	if (info.spawnSide == "droite")
	{
		dir = sf::Vector2f(-1.f, 0.f);
	}
	else
	{
		dir = sf::Vector2f(1.f, 0.f);
	}
}

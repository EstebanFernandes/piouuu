#include "BomberEnemy.h"

BomberEnemy::BomberEnemy(CAssetManager* assets) 
{
	setType(Enemy);
	this->assets = assets;
	enemyName = "bomber";
	setTexture(enemyName);
	initAnimation();
	level = 0;
	damage = 3;
	maxHealthPoint = 20.f + 15.f * level;
	healthPoint = maxHealthPoint;
	setSprite();
	BAW.assets = assets;
	initPositionX = assets->sCREEN_WIDTH+ getSprite().getGlobalBounds().width;
	initPositionY = (int) (assets->sCREEN_HEIGHT*0.1f);
	setSprite();
	setMoveSpeed(15.0f);
	setBulletSpeed(1.2f);
	setAttackSpeed(1.f);
	setRotation(180.f);
	BAW.addShootType(BAW.bombe);
	sf::Vector2f bulletScale = sf::Vector2f(0.2f, 0.2f);
	BAW.referenceStat = CWeaponStat((float)damagePerBullet, bulletSpeed, sf::Vector2f(0.f, 1.f),0, "bombe", bulletScale);
}

BomberEnemy::BomberEnemy(CAssetManager* assets, bool isFacingLeft_) :
	BomberEnemy(assets)
{
	changeInitialSide(isFacingLeft_);
	setSprite();
	setTexture("bomber");
}

void BomberEnemy::changeInitalSide()
{
	if (isFacingLeft) {

		initPositionX = getSprite().getGlobalBounds().width;
		setDirectionX(1);
		isFacingLeft = false;
	}
	else {
		initPositionX = (float)assets->sCREEN_HEIGHT;
		setDirectionX(-1);
		isFacingLeft = true;
	}
}

void BomberEnemy::changeInitialSide(bool RTL)
{
	if (RTL==false) {
		initPositionX = getSprite().getGlobalBounds().width/2.f;
		setDirectionX(1);
		isFacingLeft = false;
		setSprite();
	}
}

void BomberEnemy::enemyShoot()
{
	if (bulletClock.getElapsedTime().asSeconds() >= 1.f / attackSpeed) {
		sf::Vector2f r(
			getSprite().getPosition().x - getGlobalBounds().width / 2.f,
			getSprite().getPosition().y);
		sf::Vector2f bulletScale = sf::Vector2f(0.2f, 0.2f);
		BAW.iNeedMoreBullets(r);
		// vient juste le restart le timer à la fin 
		bulletClock.restart();
	}
}

void BomberEnemy::renderEntity(sf::RenderTarget& target)
{
	RoamingEnemy::renderEntity(target);
	BAW.renderEntity(target);
}

void BomberEnemy::updateEntity(float delta)
{
	RoamingEnemy::updateEntity(delta);
	BAW.updateEntity(delta);
	if(!isDead)
		enemyShoot();
}

void BomberEnemy::updatewPlayer(float delta, CPlayer& player)
{
	RoamingEnemy::updatewPlayer(delta, player);
	updateShootWithPlayer(player);
	if (needDelete)
		transferBullet(BAW);
}

#include "BomberEnemy.h"

BomberEnemy::BomberEnemy(CAssetManager* assets) : RoamingEnemy(assets)
{
	BAW.assets = assets;
	initPositionY = assets->sCREEN_HEIGHT * 0.1f;
	setDirectionX(-1);
	setDirectionY(0);

	setMoveSpeed(15.0f);
	setAttackSpeed(1.f);

	setSprite();
}

void BomberEnemy::changeInitalSide()
{
	//rotate(180);
	if (isFacingLeft) {
		initPositionX = 0 + getSprite().getGlobalBounds().width;
		setDirectionX(1);
		isFacingLeft = false;
		setSprite();
	}
	else {
		initPositionX = assets->sCREEN_HEIGHT;
		setDirectionX(-1);
		isFacingLeft = true;
		setSprite();
	}
}

void BomberEnemy::enemyShoot()
{
	if (bulletClock.getElapsedTime().asSeconds() >= 1.f / attackSpeed) {
		sf::Vector2f r(
			getSprite().getPosition().x - getGlobalBounds().width / 2.f,
			getSprite().getPosition().y);
		BAW.iNeedMoreBullets(r, damagePerBullet, bulletSpeed, sf::Vector2f(0, 1));
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
	enemyShoot();
}

void BomberEnemy::updatewPlayer(float delta, CPlayer& player)
{
	RoamingEnemy::updatewPlayer(delta, player);
	std::vector<CBulletAuto>* bullets = BAW.getVector();
	size_t temp = bullets->size();
	for (int i = 0; i < temp; i++) {
		if (player.checkCollisions((*bullets)[i])) {
			player.reduceHP((*bullets)[i].getDamage());
			bullets->erase(bullets->begin() + i);
			if (i != 0)
				i--;
			temp--;
		}
	}
}

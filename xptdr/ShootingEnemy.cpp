#include "ShootingEnemy.h"

ShootingEnemy::ShootingEnemy(CAssetManager* assetParam) {
	BAW.assets = assetParam;
	initPositionX = assetParam->sCREEN_WIDTH * 2.f;
	initEnnemy(assetParam);
	moveSpeed = 5.f;
	attackSpeed = 1.f;
	isAShooter = true;
}

void ShootingEnemy::updateMovement(float delta)
{
	if (checkGlobalCollisions())
		needDelete = true;
	updateLifeBar();
	if (onAvance == true && !isPositionated)
		moveEntity(sf::Vector2f(moveSpeed * -delta, 0));
	if (!isPositionated && getSprite().getPosition().x <= assets->sCREEN_WIDTH * 0.9) {
		isPositionated = true;
		bulletClock.restart();
	}
}

void ShootingEnemy::enemyShoot()
{
	if (bulletClock.getElapsedTime().asSeconds() >= 1.f / attackSpeed) {
		sf::Vector2f r(getSprite().getPosition().x + getSprite().getGlobalBounds().width, getSprite().getPosition().y + (getSprite().getGlobalBounds().height / 2));
		BAW.iNeedMoreBullets(r, damagePerBullet, bulletSpeed, sf::Vector2f(-1,0));
		// vient juste le restart le timer à la fin 
		bulletClock.restart();
	}
}

void ShootingEnemy::renderEntity(sf::RenderTarget& target)
{
	CEnemy::renderEntity(target);
	BAW.renderEntity(target);
}

void ShootingEnemy::updateEntity(float delta)
{
	CEnemy::updateEntity(delta);
	BAW.updateEntity(delta);
	enemyShoot();
}

void ShootingEnemy::updatewPlayer(float delta, CPlayer& player)
{
	CEnemy::updatewPlayer(delta, player);
	std::vector<CBullet>* bullets = BAW.getVector();
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

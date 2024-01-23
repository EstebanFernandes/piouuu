#include "ShootingEnemy.h"

ShootingEnemy::ShootingEnemy(CAssetManager* assetParam) {
	BAW.assets = assetParam;
	initEnnemy(assetParam);
	initPositionX = assetParam->sCREEN_WIDTH * 1.05f;
	setSprite();
	moveSpeed = 5.f;
	attackSpeed = 1.f;
}

void ShootingEnemy::updateMovement(float delta)
{
	if (checkGlobalCollisions() && isPositionated)
		needDelete = true;
	updateLifeBar();
	if (onAvance == true && !isPositionated)
		moveEntity(sf::Vector2f(moveSpeed * -delta, 0));
	if (!isPositionated && getSprite().getPosition().x <= assets->sCREEN_WIDTH - getSprite().getGlobalBounds().width / 2.f) {
		isPositionated = true;
		bulletClock.restart();
	}
}

void ShootingEnemy::enemyShoot()
{
	if (bulletClock.getElapsedTime().asSeconds() >= 1.f / attackSpeed && isPositionated) {
		sf::Vector2f r(
			getSprite().getPosition().x - getGlobalBounds().width/2.f,
			getSprite().getPosition().y );
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

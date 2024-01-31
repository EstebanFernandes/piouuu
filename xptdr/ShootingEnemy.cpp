#include "ShootingEnemy.h"

ShootingEnemy::ShootingEnemy(CAssetManager* assetParam) {
	BAW.assets = assetParam;
	BAW.assets->addSFX("bulletSound", &BAW.bulletSound);
	initEnnemy(assetParam);
	initPositionX = assetParam->sCREEN_WIDTH * 1.05f;
	setSprite();
	moveSpeed = 5.f;
	attackSpeed = 1.f;
	bulletSpeed = 0.2f;
	BAW.getWeaponStats() = CWeaponStat((float)damagePerBullet, bulletSpeed, sf::Vector2f(-1.f, 0.f), 0, "", BAW.bulletScale, attackSpeed);
	BAW.setWeaponPos(sf::Vector2f(getGlobalBounds().width / 2.f, 0.f));
}

ShootingEnemy::ShootingEnemy(CAssetManager* asset, CMob* target_)
	:ShootingEnemy(asset)
{
	target = target_;
	hasTarget = true;
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
		if (hasTarget)
		{
			sf::Vector2f posPlayer = target->getSprite().getPosition();
			BAW.shootTowardDirection(getSprite().getPosition(), posPlayer);
		}
		// vient juste le restart le timer à la fin 
		bulletClock.restart();
	}
}

void ShootingEnemy::renderEntity(sf::RenderTarget& target)
{
	CEnemy::renderEntity(target);
	BAW.renderWeapon(target);
}

void ShootingEnemy::updateEntity(float delta)
{
	CEnemy::updateEntity(delta);
	BAW.updateWeapon(delta);
	if (!isDead)
		enemyShoot();
}

void ShootingEnemy::updatewPlayer(float delta, CPlayer& player)
{
	CEnemy::updatewPlayer(delta, player);
	updateShootWithPlayer(player);
	if (needDelete)
		transferBullet(BAW);
}

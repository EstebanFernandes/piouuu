#include "ShootingEnemy.h"

ShootingEnemy::ShootingEnemy(AssetManager* assetParam) {
	BAW.assets = assetParam;
	BAW.assets->addSFX("bulletSound", &BAW.bulletSound);
	initEnnemy(assetParam, info, "shooter");
	info.pos.x = Engine::SCREEN_WIDTH *0.95f;
	moveSpeed = 2.f;
	attackSpeed = 1.5f;
	bulletSpeed = 1.f;
	BAW.setWeaponStats(WeaponStat((float)damagePerBullet, bulletSpeed, sf::Vector2f(-1.f, 0.f), 0, "", BAW.bulletScale, attackSpeed));
	initDirection();
	BAW.setBulletAsset("bulletTear");
	explosionSprite.setColor(sf::Color::Red);
	initAnimation();
	getSprite().setScale(1.5f, 1.5f);
	setSprite();
}


ShootingEnemy::ShootingEnemy(AssetManager* asset, enemyInfo ee)
	:ShootingEnemy(asset)
{
	setInfo(ee);
	setPos();
	//initDirection();
	BAW.getWeaponStats().dir = info.direction;
	setSprite();
}

ShootingEnemy::ShootingEnemy(AssetManager* asset, Character& stat, WeaponStat WeaponStat ,enemyInfo info_)
	: ShootingEnemy(asset,info_)
{
	setCharacterStats(stat);
	BAW.setWeaponStats(WeaponStat);
	if (BAW.getWeaponStats().dir.x == 0.f&& BAW.getWeaponStats().dir.y == 0.f)
	{
		BAW.getWeaponStats().dir  =info.direction;
	}
	BAW.setBulletAsset("bulletTear");
	damage = stat.getDamagePerBullet();
	initAnimation();
}

void ShootingEnemy::setPos()
{
	if (info.spawnSide == "gauche")
	{
		//info.pos.x = Engine::SCREEN_WIDTH * 0.05f;
		spawnPos.x = Engine::SCREEN_WIDTH * 0.05f;
	}
	else if(info.spawnSide == "droite")
	{
		//info.pos.x=Engine::SCREEN_WIDTH * 0.95f;
		spawnPos.x = Engine::SCREEN_WIDTH * 0.95f;
		flipSprite();
	}
	else if (info.spawnSide == "haut")
		//info.pos.y=Engine::SCREEN_HEIGHT * 0.05f;
		spawnPos.y = Engine::SCREEN_HEIGHT * 0.05f;
	else if (info.spawnSide == "bas")
		//info.pos.y=Engine::SCREEN_HEIGHT * 0.95f;
		spawnPos.y = Engine::SCREEN_HEIGHT * 0.95f;
}
void ShootingEnemy::updateMovement(float delta)
{
	if (isPositionated)
	{
		int prevCF = anim.getCurrentFrameNumber().x;
		anim.updateAnimation();
		if (prevCF == 4 && anim.getCurrentFrameNumber().x == 0)
			isReadyToShoot = true;
		if ( info.isAim&&target!=NULL)
		{		
			setRotation(utilities::getAngleFromDirection(utilities::dirAtoB(getSprite().getPosition(), target->getSprite().getPosition())));
			
		}
	}
	if (checkGlobalCollisions() && isPositionated)
		needDelete = true;
	if (onAvance == true && !isPositionated)
		moveEntity(info.direction*moveSpeed * delta); 
	if (!isPositionated && 
		onestPose()) {
		isPositionated = true;
		setRotation(utilities::getAngleFromDirection(BAW.getWeaponStats().dir));
		if (info.isAim)
		{
			seekForTarget = true;
		}
	}
}

void ShootingEnemy::enemyShoot()
{
	if (isReadyToShoot) {
		if (info.isAim && target != NULL)
		{
			float temp = 0.f;
			sf::Vector2f posPlayer = target->getSprite().getPosition();
			BAW.shootTowardDirection(
				utilities::shootPos((getSprite().getPosition()),
					getGlobalBounds().width / 2.f, getSprite().getRotation() + 180.f), posPlayer);
		}
		else
		{
			BAW.iNeedMoreBullets(
				utilities::shootPos((getSprite().getPosition()),
					getGlobalBounds().width / 2.f, utilities::getAngleFromDirection(BAW.getWeaponStats().dir)));
		}
		isReadyToShoot = false;
		// vient juste le restart le timer à la fin 
	}

}

void ShootingEnemy::renderEntity(sf::RenderTarget& target)
{
	Enemy::renderEntity(target);
	BAW.renderWeapon(target);
}


void ShootingEnemy::updateEntity(float delta)
{
	Enemy::updateEntity(delta);
	BAW.updateWeapon(delta);
	if (!isDead)
	{
		enemyShoot();
	}
}

void ShootingEnemy::updatewPlayer(float delta, Player& player)
{
	Enemy::updatewPlayer(delta, player);
	updateShootWithPlayer(player);
	if (needDelete)
		transferBullet(BAW);
}


#include "ShootingEnemy.h"

ShootingEnemy::ShootingEnemy(CAssetManager* assetParam) {
	BAW.assets = assetParam;
	BAW.assets->addSFX("bulletSound", &BAW.bulletSound);
	initEnnemy(assetParam, info, "shooter");
	initDirection();
	info.pos.x = assets->sCREEN_WIDTH *0.95f;
	moveSpeed = 2.f;
	attackSpeed = 1.5f;
	bulletSpeed = 1.f;
	BAW.setWeaponStats(CWeaponStat((float)damagePerBullet, bulletSpeed, sf::Vector2f(-1.f, 0.f), 0, "", BAW.bulletScale, attackSpeed));
	BAW.setBulletAsset("bulletTear");
	explosionSprite.setColor(sf::Color::Red);
	initAnimation();
	getSprite().setScale(2.f, 2.f);
	setSprite();
}

ShootingEnemy::ShootingEnemy(CAssetManager* asset, CMob* target_)
	:ShootingEnemy(asset)
{
	setTarget(target_);
}

ShootingEnemy::ShootingEnemy(CAssetManager* asset, enemyInfo ee)
	:ShootingEnemy(asset)
{
	setInfo(ee);
	setPos();
	initDirection();
	setRotation(utilities::getAngleFromDirection(info.direction)+180.f);
	BAW.getWeaponStats().changeDir(info.direction);
	setSprite();
}

ShootingEnemy::ShootingEnemy(CAssetManager* asset, CMob* target_, CCharacter& stat, CWeaponStat WeaponStat ,enemyInfo info_)
	: ShootingEnemy(asset,info_)
{
	setTarget(target_);
	setCharacterStats(stat);
	BAW.setWeaponStats(WeaponStat);
	if (BAW.getWeaponStats().dir.x == 0.f&& BAW.getWeaponStats().dir.y == 0.f)
	{
		BAW.getWeaponStats().changeDir(info.direction);
	}
	damage = stat.getDamagePerBullet();
	initAnimation();
}

void ShootingEnemy::setPos()
{
	if (info.spawnSide == "gauche")
		info.pos.x = assets->sCREEN_WIDTH * 0.05f;
	else if(info.spawnSide == "droite")
		info.pos.x=assets->sCREEN_WIDTH * 0.95f;
	else if (info.spawnSide == "haut")
		info.pos.y=assets->sCREEN_HEIGHT * 0.05f;
	else if (info.spawnSide == "bas")
		info.pos.y=assets->sCREEN_HEIGHT * 0.95f;
}
void ShootingEnemy::updateMovement(float delta)
{
	if (isPositionated)
	{
		anim.updateAnimation();
		if ( hasTarget)
		{		
			
			setRotation(utilities::getAngleFromDirection(utilities::dirAtoB(getSprite().getPosition(), target->getSprite().getPosition()))+180.f);
			
		}
	}
	if (checkGlobalCollisions() && isPositionated)
		needDelete = true;
	updateLifeBar();
	if (onAvance == true && !isPositionated)
		moveEntity(info.direction*moveSpeed * delta); 
	if (!isPositionated && 
		onestPose()) {
		isPositionated = true;
		setRotation(180.f+utilities::getAngleFromDirection( BAW.getWeaponStats().dir));
	}
}

void ShootingEnemy::enemyShoot()
{
	if (anim.getCurrentFrameNumber()== 5&& isPositionated) {
		if (hasTarget)
		{
			float temp = 0.f;
			if (isSpriteFlip())
				temp = 180.f;
			sf::Vector2f posPlayer = target->getSprite().getPosition();
			BAW.shootTowardDirection(
				utilities::shootPos((getSprite().getPosition()),
				getGlobalBounds().width/2.f,getSprite().getRotation()+180.f), posPlayer);
		}
		else
		{
			BAW.iNeedMoreBullets(
			utilities::shootPos((getSprite().getPosition()),
				getGlobalBounds().width / 2.f,utilities::getAngleFromDirection(BAW.getWeaponStats().dir)));
			std::cout << "je tire !" << std::endl;
		}
		// vient juste le restart le timer à la fin 
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
	{
		enemyShoot();
	}
}

void ShootingEnemy::updatewPlayer(float delta, CPlayer& player)
{
	CEnemy::updatewPlayer(delta, player);
	updateShootWithPlayer(player);
	if (needDelete)
		transferBullet(BAW);
}


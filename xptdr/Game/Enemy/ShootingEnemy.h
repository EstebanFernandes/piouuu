#pragma once
#include "Enemy.h"
#include"InterfaceShootingEnemy.h"
class ShootingEnemy : public Enemy, public InterfaceShootingEnemy
{
private:
	bool isReadyToShoot = false;
	bool isPositionated = false;
	Mob* target;
	Animation anim;
public:
	ShootingEnemy(AssetManager* asset);
	ShootingEnemy(AssetManager* asset, enemyInfo ee);
	ShootingEnemy(AssetManager* asset,Character& stat,WeaponStat WeaponStat,enemyInfo info);
	void updateMovement(float delta);
	void enemyShoot();
	~ShootingEnemy() {
		assets->deleteSound(BAW.bulletSound);
	}
	//redéfinition de Enemy
	void renderEntity(sf::RenderTarget& target);
	//redéfinition de Enemy
	void updateEntity(float delta);
	/**
	* redéfinition de HittingEntity
	* Permet de faire des dégats aux joueurs avec les tirs des ennemis
	*/
	void updatewPlayer(float delta, Player& player);
	Enemy* clone() override {
		ShootingEnemy* temp = new ShootingEnemy(*this);
		temp->initPosition();
		std::cout << temp->getPosition().x << " et pos en y : " << temp->getPosition().y << std::endl;
		temp->initAnimation();
		temp->initDirection();
		temp->setSprite();
		assets->addSFX("bulletSound", &temp->BAW.bulletSound);
		return temp;
	}
	void setSprite()
	{
		setLifeBar();
		setPositionEntity(spawnPos);
	}
	void setPos();
	void setTarget(Mob* target_) {
		target = target_;
	}
	void initAnimation() {
		float timeBetweenBullets = 1.f / BAW.getWeaponStats().attackSpeed;
		float tbf = timeBetweenBullets / 5;
		anim = Animation(getPointerSprite(), sf::Vector2i( 82, 86),5,tbf,2 );
	}
	void initDirection() {
			Enemy::initDirection();
		BAW.getWeaponStats().dir = info.direction;
		BAW.getWeaponStats().changeDir(info.direction);
		setRotation(utilities::getAngleFromDirection(info.direction));
	}

};


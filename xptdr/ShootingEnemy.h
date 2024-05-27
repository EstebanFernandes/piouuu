#pragma once
#include "CEnemy.h"
#include"InterfaceShootingEnemy.h"
class ShootingEnemy : public CEnemy, public InterfaceShootingEnemy
{
private:
	bool isReadyToShoot = false;
	bool isPositionated = false;
	CMob* target;
	CAnimation anim;
public:
	ShootingEnemy(CAssetManager* asset);
	ShootingEnemy(CAssetManager* asset, enemyInfo ee);
	ShootingEnemy(CAssetManager* asset,CCharacter& stat,CWeaponStat WeaponStat,enemyInfo info);
	void updateMovement(float delta);
	void enemyShoot();
	~ShootingEnemy() {
		assets->deleteSound(BAW.bulletSound);
	}
	//redéfinition de CEnemy
	void renderEntity(sf::RenderTarget& target);
	//redéfinition de CEnemy
	void updateEntity(float delta);
	/**
	* redéfinition de CHittingEntity
	* Permet de faire des dégats aux joueurs avec les tirs des ennemis
	*/
	void updatewPlayer(float delta, CPlayer& player);
	CEnemy* clone() override {
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
	void setTarget(CMob* target_) {
		target = target_;
	}
	void initAnimation() {
		float timeBetweenBullets = 1.f / BAW.getWeaponStats().attackSpeed;
		float tbf = timeBetweenBullets / 5;
		anim = CAnimation(getPointerSprite(), sf::Vector2i( 82, 86),5,tbf,2 );
	}
	void initDirection() {
			CEnemy::initDirection();
		BAW.getWeaponStats().dir = info.direction;
		BAW.getWeaponStats().changeDir(info.direction);
		setRotation(utilities::getAngleFromDirection(info.direction));
	}

};


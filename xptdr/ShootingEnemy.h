#pragma once
#include "CEnemy.h"
#include"InterfaceShootingEnemy.h"
class ShootingEnemy : public CEnemy, public InterfaceShootingEnemy
{
private:
	bool isPositionated = false;
	CMob* target;
	bool hasTarget = false;
	CAnimation anim;
public:
	ShootingEnemy(CAssetManager* asset);
	ShootingEnemy(CAssetManager* asset, CMob* target);
	ShootingEnemy(CAssetManager* asset, enemyInfo ee);
	ShootingEnemy(CAssetManager* asset, CMob* target_,CCharacter& stat,CWeaponStat WeaponStat,enemyInfo info);
	void updateMovement(float delta);
	void enemyShoot();
	~ShootingEnemy() {
	}
	//red�finition de CEnemy
	void renderEntity(sf::RenderTarget& target);
	//red�finition de CEnemy
	void updateEntity(float delta);
	/**
	* red�finition de CHittingEntity
	* Permet de faire des d�gats aux joueurs avec les tirs des ennemis
	*/
	void updatewPlayer(float delta, CPlayer& player);
	CEnemy* clone() override {
		initPosition();
		setSprite();
		return new ShootingEnemy(*this);
	}
	void setSprite()
	{
		setLifeBar();
		setPositionEntity(spawnPos);
	}
	void setPos();
	void setTarget(CMob* target_) {
		if (target_ == NULL)
			hasTarget = false;
		else
		{
			target = target_;
			hasTarget = true;
		}
	}
};


#pragma once
#include "CEnemy.h"
#include"InterfaceShootingEnemy.h"
class ShootingEnemy : public CEnemy, public InterfaceShootingEnemy
{
private:
	bool isPositionated = false;
	CMob* target;
	bool hasTarget = false;
public:
	ShootingEnemy(CAssetManager* asset);
	ShootingEnemy(CAssetManager* asset, CMob* target);
	ShootingEnemy(CAssetManager* asset, CMob* target_,CCharacter& stat,CWeaponStat WeaponStat,sf::Vector2f pos);
	void updateMovement(float delta);
	void enemyShoot();
	~ShootingEnemy() {
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
		initPosition(initPos);
		setSprite();
		return new ShootingEnemy(*this);
	}
	void setSprite()
	{
		setLifeBar();
		setPositionEntity((float)assets->sCREEN_WIDTH, (float)initPositionY);
	}
};


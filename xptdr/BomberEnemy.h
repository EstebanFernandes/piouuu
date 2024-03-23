#pragma once

#include "RoamingEnemy.h"
#include"InterfaceShootingEnemy.h"
class BomberEnemy : public RoamingEnemy,public InterfaceShootingEnemy
{
private:
	bool isFacingLeft = true;
public:
	BomberEnemy(CAssetManager* assets);
	BomberEnemy(CAssetManager* assets, enemyInfo info_);
	/// <summary>
	/// Constructeur utilisée par les levels
	/// </summary>
	/// <param name="assets"></param>
	/// <param name="stat"></param>
	/// <param name="WStat"></param>
	/// <param name="info_"></param>
	BomberEnemy(CAssetManager* assets, CCharacter stat, CWeaponStat WStat , enemyInfo info_);
	void enemyShoot();
	//redéfinition de CEnemy
	void renderEntity(sf::RenderTarget& target);
	//redéfinition de CEnemy
	void updateEntity(float delta);
	/**
	* redéfinition de CHittingEntity
	* Permet de faire des dégats aux joueurs avec les tirs des ennemis
	*/
	void updatewPlayer(float delta, CPlayer& player);
	void initDirection();
	CEnemy* clone() override{
		BomberEnemy* temp = new BomberEnemy(*this);
		temp->initPosition();
		temp->initDirection();
		temp->setSprite();
		return temp;
	}
};


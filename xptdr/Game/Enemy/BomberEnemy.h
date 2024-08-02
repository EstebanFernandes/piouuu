#pragma once

#include "RoamingEnemy.h"
#include"InterfaceShootingEnemy.h"
class BomberEnemy : public RoamingEnemy,public InterfaceShootingEnemy
{
private:
	bool isFacingLeft = true;
public:
	BomberEnemy(AssetManager* assets);
	BomberEnemy(AssetManager* assets, enemyInfo info_);
	/// <summary>
	/// Constructeur utilisée par les levels
	/// </summary>
	/// <param name="assets"></param>
	/// <param name="stat"></param>
	/// <param name="WStat"></param>
	/// <param name="info_"></param>
	BomberEnemy(AssetManager* assets, Character stat, WeaponStat WStat , enemyInfo info_);
	void enemyShoot();
	~BomberEnemy(){}
	//redéfinition de Enemy
	void renderEntity(sf::RenderTarget& target);
	//redéfinition de Enemy
	void updateEntity(float delta);
	/**
	* redéfinition de HittingEntity
	* Permet de faire des dégats aux joueurs avec les tirs des ennemis
	*/
	void updatewPlayer(float delta, Player& player);
	void initDirection();
	Enemy* clone() override{
		BomberEnemy* temp = new BomberEnemy(*this);
		temp->initPosition();
		temp->initDirection();
		temp->setSprite();
		return temp;
	}
};


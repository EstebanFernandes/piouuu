#pragma once

#include "RoamingEnemy.h"
#include"InterfaceShootingEnemy.h"
class BomberEnemy : public RoamingEnemy,public InterfaceShootingEnemy
{
private:
	bool isFacingLeft = true;
public:
	BomberEnemy(CAssetManager* assets);
	BomberEnemy(CAssetManager* assets,bool isFacingLeft_);
	BomberEnemy(CAssetManager* assets, CCharacter stat, CWeaponStat WStat , bool isFacingLeft_);
	void changeInitalSide();
	void changeInitialSide(bool RTL);
	void enemyShoot();
	//red�finition de CEnemy
	void renderEntity(sf::RenderTarget& target);
	//red�finition de CEnemy
	void updateEntity(float delta);
	/**
	* red�finition de CHittingEntity
	* Permet de faire des d�gats aux joueurs avec les tirs des ennemis
	*/
	void updatewPlayer(float delta, CPlayer& player);
};


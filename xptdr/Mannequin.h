#pragma once
#include"CEnemy.h"
class Mannequin : public CEnemy
{
private:
	CAnimation anim;
	int etatmannequin = 0;
	float minHeight;
	float maxHeight;
	bool isGoingUp=true;
	float speed = 0.1f;
	sf::Color color;
	int last = 0;

	//Méthode 
	void updateEtat(int& etat);
public:
	Mannequin(){
		setType(typeInt::Enemy);
		setMaxHealth(40);
		healthPoint = maxHealthPoint;
		isDead = false;
	}
	void setAssets(CAssetManager* asset);
	Mannequin(CAssetManager* asset_);
	CEnemy* clone() {
		return nullptr;
	}
	void updateMovement(float delta);
	void enemyShoot();
	void updateEntity(float delta);
	void renderEntity(sf::RenderTarget& target);
	void updatewPlayer(float delta, CPlayer& player);
};


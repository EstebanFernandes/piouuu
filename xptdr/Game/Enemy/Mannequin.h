#pragma once
#include"Enemy.h"
class Mannequin : public Enemy
{
private:
	Animation anim;
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
		setType(typeInt::EnemyType);
		setMaxHealth(40);
		healthPoint = maxHealthPoint;
		isDead = false;
	}
	void setAssets(AssetManager* asset);
	Mannequin(AssetManager* asset_);
	Enemy* clone() {
		return nullptr;
	}
	void updateMovement(float delta);
	void enemyShoot();
	void updateEntity(float delta);
	void renderEntity(sf::RenderTarget& target);
	void updatewPlayer(float delta, Player& player);
};


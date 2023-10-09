#pragma once
#include "SFML/Graphics.hpp"
#include "DEFINITIONS.h"
#include "CEntity1.h"
class CBullet : public CEntity1
{
private:
	sf::Vector2f direction;
	float bulletSpeed = 2.f;
	int damage;
public :
	CBullet(int damaage, sf::Vector2f pos, sf::Vector2f dir, CAssetManager* assetss);
	void setSprite();
	void updateEntity(float dt);
	void updateCollision(CEntity1& b);
	void renderEntity(sf::RenderTarget& target);
	//Surchagrge pour les collisions entre objet
	int getDamage() { return damage; }
};


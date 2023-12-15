#pragma once
#include "SFML/Graphics.hpp"
#include "DEFINITIONS.h"
#include "CEntity.h"
#include "SFML/Audio.hpp"

class CBullet : public CEntity
{
protected:
	sf::Vector2f direction;
	float bulletSpeed = 2.f;
	int damage;
	sf::Sound bulletSound;
	sf::SoundBuffer bulletSoundBuffer;
public :
	CBullet();
	CBullet(int damaage, sf::Vector2f pos, sf::Vector2f dir, CAssetManager* assetss);
	CBullet(int damaage, sf::Vector2f pos, sf::Vector2f dir, float bulletSpeed, CAssetManager* assetss); 
	void setSprite();
	void updateEntity(float dt);
	void updateCollision(CEntity& b);
	void renderEntity(sf::RenderTarget& target);
	//Surchagrge pour les collisions entre objet
	int getDamage() { return damage; }
};


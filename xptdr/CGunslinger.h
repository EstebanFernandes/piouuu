#pragma once
#include"CEntity.h"
#include"CBullet.h"
class CGunslinger : public CEntity
{
private:
	int type_de_tir;
	std::vector<CBullet> magazine;
public:
	CGunslinger();
	void setSprite(){}
	void updateEntity(float dt);
	void renderEntity(sf::RenderTarget& target);
	void updateCollision(CEntity& b);
	void iNeedMoreBullets(sf::Vector2f pos);
	void iNeedMoreBullets(sf::Vector2f pos, int damage);
	void iNeedMoreBullets(sf::Vector2f pos, int damage, float bulletSpeed_);
	void iNeedMoreBullets(sf::Vector2f pos, int damage,sf::Vector2f direction);
	void iNeedMoreBullets(sf::Vector2f pos, int damage, float bulletSpeed_, sf::Vector2f direction);
	std::vector<CBullet>* getVector() { return &magazine; }
};


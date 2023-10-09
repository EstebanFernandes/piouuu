#pragma once
#include"CEntity1.h"
#include"CBullet.h"
class CGunslinger : public CEntity1
{
private:
	std::vector<CBullet> magazine;
public:
	CGunslinger();
	void setSprite(){}
	void updateEntity(float dt);
	void renderEntity(sf::RenderTarget& target);
	void updateCollision(CEntity1& b);
	void iNeedMoreBullets(sf::Vector2f pos);
	void iNeedMoreBullets(sf::Vector2f pos, int damage);
	std::vector<CBullet>* getVector() { return &magazine; }
};


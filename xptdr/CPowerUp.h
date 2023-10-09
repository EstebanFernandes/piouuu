#pragma once
#include "CHittingEntity.h"
class CPowerUp : public CHittingEntity
{
private:
	int posSprite = 0;
	sf::IntRect currentFrame;
	sf::Clock animationTimer;
public:
	CPowerUp(CAssetManager* a);
	void setSprite();
	void updatewPlayer(float delta, CPlayer& player);
	void updateFX();
	void updateEntity(float dt)
	{
		updateFX();
		moveEntity(-SCROLLING_SPEED * dt * 6.f, 0.f);
	}
	void renderEntity(sf::RenderTarget& target) 
	{
		target.draw(getSprite()); 
	}
	 void updateCollision(CEntity1& b){}
};


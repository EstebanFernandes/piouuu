#pragma once
#include "CHittingEntity.h"
#include"CAnimation.h"
class CPowerUp : public CHittingEntity
{
private:
	CAnimation anim;
	int posSprite = 0;
	sf::IntRect currentFrame;
	sf::Clock animationTimer;
public:
	CPowerUp(CAssetManager* a);
	CPowerUp(sf::Vector2f pos,CAssetManager* a);
	void setSprite()
	{
		currentFrame = sf::IntRect(0, 0, 68, 68);
		anim = CAnimation(getPointerSprite(), currentFrame, 4, 0.1f);
		getSprite().setTexture((*assets).GetTexture("lifePowerUp"));
		getSprite().setTextureRect(currentFrame);
	}
	void updatewPlayer(float delta, CPlayer& player);
	void updateEntity(float dt)
	{
		anim.updateAnimation();
		moveEntity(-SCROLLING_SPEED * dt * 6.f, 0.f);
	}
	void renderEntity(sf::RenderTarget& target) 
	{
		target.draw(getSprite()); 
	}
};


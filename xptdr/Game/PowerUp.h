#pragma once
#include "HittingEntity.h"
#include"../Engine/Animation.h"
class PowerUp : public HittingEntity
{
private:
	Animation anim;
	int posSprite = 0;
	sf::IntRect currentFrame;
	sf::Clock animationTimer;
public:
	PowerUp(AssetManager* a);
	PowerUp(sf::Vector2f pos,AssetManager* a);
	void setSprite()
	{
		currentFrame = sf::IntRect(0, 0, 68, 68);
		anim = Animation(getPointerSprite(), sf::Vector2i(68,68), sf::Vector2i(4, 1), 0.1f);
		getSprite().setTexture((*assets).GetTexture("lifePowerUp"));
		getSprite().setTextureRect(currentFrame);
	}
	void updatewPlayer(float delta, Player& player);
	void updateEntity(float dt)
	{
		anim.updateAnimation();
		moveEntity(-SCROLLING_SPEED * dt * 6.f, 0.f);
	}
	void renderEntity(sf::RenderTarget& target) 
	{
		target.draw(getSprite()); 
	}
	void renderUI(sf::RenderTarget& target){}
};


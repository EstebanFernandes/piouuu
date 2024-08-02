#pragma once
#include"dot.h"
#include"../Engine/AssetManager.h"
#include"SFML/Graphics/Sprite.hpp"
#include "../Engine//Animation.h"
class fire : public dot
{
private:
	AssetManager* assets;
	//Chance de propagé le feu à l'unité si jointe
	float probaPropag = 1.f;
	sf::Sprite fireSprite;
	Animation fireAnimation;
	int ab = 0;
	void initSprite();
public:
	void changeTarget(Mob* newTarget) { 
		target = newTarget;
		if (target != NULL)
			initSprite();
	}
	fire(Mob* targetparam, float damage, float timer, float duration,AssetManager* assets_);
	void globalMethod(std::vector<Mob*>& entityList);
	void update(float delta);
	void action();
	void renderBuff(sf::RenderTarget& target);
	effetspecial* clone() const override {
		fire* temp = new fire(*this);
		temp->fireAnimation = Animation(&temp->fireSprite, sf::Vector2i(80, 80), 16, 0.16f);
		return temp; 
	}
};
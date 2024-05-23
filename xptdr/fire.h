#pragma once
#include"dot.h"
#include"CAssetManager.h"
#include"SFML/Graphics/Sprite.hpp"
#include "CAnimation.h"
class fire : public dot
{
private:
	CAssetManager* assets;
	//Chance de propagé le feu à l'unité si jointe
	float probaPropag = 1.f;
	sf::Sprite fireSprite;
	CAnimation fireAnimation;
	int ab = 0;
	void initSprite();
public:
	void changeTarget(CMob* newTarget) { 
		target = newTarget;
		if (target != NULL)
			initSprite();
	}
	fire(CMob* targetparam, float damage, float timer, float duration,CAssetManager* assets_);
	void globalMethod(std::vector<CMob*>& entityList);
	void update(float delta);
	void action();
	void renderBuff(sf::RenderTarget& target);
	effetspecial* clone() const override {
		fire* temp = new fire(*this);
		temp->fireAnimation = CAnimation(&temp->fireSprite, sf::Vector2i(80, 80), 16, 0.16f);
		return temp; 
	}
};
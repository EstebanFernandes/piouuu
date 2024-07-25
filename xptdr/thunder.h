#pragma once
#include"effetspecial.h"
class thunder : public effetspecial
{
private:
	CAssetManager* asset;
	float damage;
	float range;
	int cbdefoisDraw = 0;
	//Liste des sprites qui doivent être dessinés
	std::vector<sf::RectangleShape> hitSprite;
	void setSprite(CMob* otherTarget, float distance);
	CMob* prevTarget = NULL;
	void setPrevTarget(CMob* targz) { prevTarget = targz; }
	static image thunderImage;
	sf::Sprite randomizeThunder();
public:
	thunder(CMob* targetparam,CMob* thereFore, float damage_, float range_ ,CAssetManager* assets_);
	void globalMethod(std::vector<CMob*>& entityList);
	void update(float delta);
	void action();
	void renderBuff(sf::RenderTarget& target) { 
		for (int i = 0; i < hitSprite.size(); i++) 
		{
			target.draw(hitSprite[i]);
		}
		cbdefoisDraw++;
		if (cbdefoisDraw == 1)
		{
			this->target->reduceHP(damage);
			needDelete = true;
		}
	}
	effetspecial* clone() const override {
		thunder* temp = new thunder(*this);
		temp->hasGlobal = true;
		return temp;
	}
	static void initializeThunder(CAssetManager* am);
};


#pragma once
#include"effetspecial.h"
class thunder : public effetspecial
{
private:
	AssetManager* asset;
	float damage;
	float range;
	int cbdefoisDraw = 0;
	//Liste des sprites qui doivent être dessinés
	std::vector<sf::RectangleShape> hitSprite;
	void setSprite(Mob* otherTarget, float distance);
	Mob* prevTarget = NULL;
	void setPrevTarget(Mob* targz) { prevTarget = targz; }
	static image thunderImage;
	sf::Sprite randomizeThunder();
public:
	thunder(Mob* targetparam,Mob* thereFore, float damage_, float range_ ,AssetManager* assets_);
	void globalMethod(std::vector<Mob*>& entityList);
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
	static void initializeThunder(AssetManager* am);
};


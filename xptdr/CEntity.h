#pragma once
#include "DEFINITIONS.h"
#include <SFML/Graphics.hpp>
#include<iostream>
#include <string>
//#include"DEF"
#include"CAssetManager.h"
class CEntity
{
private :
	sf::Sprite ENTsprite;
	int type = undefined;
public:
	bool isHitting = false;
	bool isDead = false;
	bool needDelete = false;
	typedef enum
	{
		undefined = -1,
		Player,
		Enemy,
		FriendlyFire,
		EnemyFire,
		PowerUp,
		Gunslinger
	} typeInt;
	CAssetManager* assets = NULL;
	virtual void setSprite() = 0;
	virtual void updateEntity(float dt) = 0;
	virtual void renderEntity(sf::RenderTarget& target) = 0;
	virtual void updateCollision(CEntity& b) = 0;
	void setTexture(std::string name, std::string filename) {
		CAssetManager& a = *assets;
		a.LoadTexture(name, filename);
		ENTsprite.setTexture(a.GetTexture(name));
	}
	sf::Sprite& getSprite() { return ENTsprite; }
	sf::Sprite* getPointerSprite() { return &ENTsprite; }
	sf::FloatRect getGlobalBounds() {
		return ENTsprite.getGlobalBounds();
	}
	void setPositionEntity(const float x, const float y) {
		ENTsprite.setPosition(x, y);
	}
	void setPositionEntity(sf::Vector2f i) {
		ENTsprite.setPosition(i);
	}
	int getType() { return type; }
	void setType(int Type) { type = Type; }
	bool checkCollisions(CEntity& b)
	{
		if (b.ENTsprite.getGlobalBounds().intersects(ENTsprite.getGlobalBounds()))
			return true;
		return false;
	}
	bool checkGlobalCollisions() {
		if(type!=Gunslinger)
		{ 
			if (ENTsprite.getGlobalBounds().left + ENTsprite.getGlobalBounds().width<0 || ENTsprite.getGlobalBounds().left>assets->sCREEN_WIDTH)
				return true;
			return false;
		}
		return false;
	}
};


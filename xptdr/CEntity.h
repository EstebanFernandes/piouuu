#pragma once
#include "DEFINITIONS.h"
#include <SFML/Graphics.hpp>
#include<iostream>
#include <string>
#include"CAssetManager.h"
#include"utilities.h"
//Abstract class to handle entity, it has the least attribut that an entity should have
class CEntity
{
private :
	//Sprite of the entity
	sf::Sprite ENTsprite;
	//Type of the entity, deprecated but we didnt delete it 
	int type = undefined;
	
public:
	//Boolean that say if the entity is hitting (often the player)
	bool isHitting = false;
	//Bool that said if the entity is dead, in case you have animation of explosion or stuff like that
	bool isDead = false;
	//Bool that is true if the entity has to be delete
	bool needDelete = false;
	//Enum for the type of the entity
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
	//Needed to get assets as sound/texture
	CAssetManager* assets = NULL;
	//virtual method that define how you set the sprite of the entity
	virtual void setSprite() = 0;
	//method use to update the entity, its called each frame and the only parameters is
	//the delta time between frames
	virtual void updateEntity(float dt) = 0;
	//Method use to draw the entity, the target is in pretty much every case the window
	virtual void renderEntity(sf::RenderTarget& target) = 0;
	//Method that load the texture in the asset manager and set the texture on the sprite
	//	||BE CAREFUL|| this function the origin of the sprite in the middle of it.
	/*void setTexture(std::string name, std::string filename) {
		CAssetManager& a = *assets;
		a.LoadTexture(name, filename);
		setTexture(name);
	}*/
	//overload that get the texture from the asset manager, the texture must have been 
	//already loaded in the asset manager
	//	||BE CAREFUL|| this function set the origin of the sprite in the middle of it.
	void setTexture(std::string name) {
		CAssetManager& a = *assets;
		ENTsprite.setTexture(a.GetTexture(name));
		ENTsprite.setOrigin(sf::Vector2f(
			ENTsprite.getLocalBounds().width / 2.f,
			ENTsprite.getLocalBounds().height / 2.f));
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
	const int getType() { return type; }
	void setType(int Type) { type = Type; }
	bool checkCollisions(CEntity& b)
	{
		if (b.ENTsprite.getGlobalBounds().intersects(ENTsprite.getGlobalBounds()))
			return true;
		return false;
	}
	//Method that check collision between the entity and the screen, can be overload if you want other behavior
	bool checkGlobalCollisions() {
		if(type!=Gunslinger)
		{ 
			sf::FloatRect currentBounds = ENTsprite.getGlobalBounds();
			if (currentBounds.left + currentBounds.width<0 ||
				currentBounds.left>assets->sCREEN_WIDTH ||
				currentBounds.top+ currentBounds.height < 0
				|| currentBounds.top>assets->sCREEN_HEIGHT)
				return true;
			return false;
		}
		return false;
	}
	//Rotate the object.
	//This function adds to the current rotation of the object, 
	// unlike setRotation which overwrites it.
	void rotate(float angle)
	{
		ENTsprite.rotate(angle);
	}
	//set the orientation of the object
	//This function completely overwrites the previous rotation.
	// See the rotate function to add an angle based on the previous rotation instead.
	// The default rotation of a transformable object is 0.
	void setRotation(float angle)
	{
		ENTsprite.setRotation(angle);
	}

	void setSprite(const CEntity& r)
	{
		ENTsprite = r.ENTsprite;
	}
};


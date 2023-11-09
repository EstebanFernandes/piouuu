#pragma once
#include <sstream>
#include <string>
#include "CAssetManager.h"
#include "DEFINITIONS.h"
#include "CAnimation.h"

class CCard : public sf::Drawable
{
private :
	int MDRRcafonctionne = 0;
	CAssetManager* asset;
	sf::Text cardTitle;
	sf::Text cardDescription;
	std::string imagePath;
	sf::Sprite cardImage;
	sf::RectangleShape cardBack;
	sf::Vector2f pos;
	CAnimation anim;

	float xSize;
	float ySize;

public:
	CCard();
	CCard(float x, float y, std::string title, std::string description, std::string imageName, CAssetManager* assetParam);
	CCard(std::string title, std::string description, std::string imageName, CAssetManager* assetParam);
	void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(float deltaTime);
	sf::FloatRect getGlobalBounds()
	{
		return cardBack.getGlobalBounds();
	}
	void setPosition(sf::Vector2f r)
	{
		pos = r;
		cardBack.setPosition(pos);
		cardTitle.setPosition(pos.x + (xSize - cardTitle.getGlobalBounds().width) / 2, pos.y);
		cardImage.setPosition(pos.x + ((xSize - cardImage.getGlobalBounds().height) / 2.0f), pos.y + ySize / 2);
		cardDescription.setPosition(pos.x + (xSize - cardDescription.getGlobalBounds().width) / 2, pos.y + ySize * 0.6f);
	}
};


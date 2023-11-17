#pragma once
#include <sstream>
#include <string>
#include "CAssetManager.h"
#include "DEFINITIONS.h"
#include "CAnimation.h"
#include "CCharacter.h"

class CCard : public sf::Drawable
{
protected :
	int MDRRcafonctionne = 0;
	CAssetManager* asset;

	sf::RectangleShape cardBack;
	sf::Vector2f pos;

	sf::Text cardTitle;
	sf::Text cardDescription;

	std::string imagePath;
	sf::Sprite cardImage;
	CAnimation anim;
	

	bool animatedImage;
	bool needImage;

	float xSize;
	float ySize;

public:
	CCard();
	CCard(const CCard& Param) {
		this->operator=(Param);
	}
	CCard(float x, float y, std::string title, std::string description, std::string imageName, CAssetManager* assetParam, bool animated);
	CCard(std::string title, std::string description, std::string imageName, CAssetManager* assetParam, bool animated);
	void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(float deltaTime);
	sf::FloatRect getGlobalBounds()
	{
		return cardBack.getGlobalBounds();
	}
	void setAnimated(bool animated) { animatedImage = animated; }
	void setPosition(sf::Vector2f r)
	{
		pos = r;
		cardBack.setPosition(pos);
		cardTitle.setPosition(pos.x + (xSize - cardTitle.getGlobalBounds().width) / 2, pos.y);
		cardImage.setPosition(pos.x + ((xSize - cardImage.getGlobalBounds().height) / 2.0f), pos.y + ySize / 2);
		cardDescription.setPosition(pos.x + (xSize - cardDescription.getGlobalBounds().width) / 2, pos.y + ySize * 0.6f);
	}
	void setScale(sf::Vector2f scale)
	{
		cardBack.setScale(scale);
		xSize = cardBack.getGlobalBounds().width;
		ySize = cardBack.getGlobalBounds().height;
		cardTitle.setScale(scale);
		cardImage.setScale(scale);
		cardDescription.setScale(scale);
		setPosition(pos);
	}
	void setScale(float x,float y)
	{
		setScale(sf::Vector2f(x, y));
	}

	CCard& operator=(const CCard& Param) {
		MDRRcafonctionne = Param.MDRRcafonctionne;
		asset = Param.asset;
		cardBack = Param.cardBack;
		pos = Param.pos;
		cardTitle = Param.cardTitle;
		cardDescription = Param.cardDescription;
		imagePath = Param.imagePath;
		cardImage = Param.cardImage;
		anim = Param.anim;
		needImage = Param.needImage;
		animatedImage = Param.animatedImage;
		xSize = Param.xSize;
		ySize = Param.ySize;
		return *this;
	}

	void setOutlineThickNess(float r) { cardBack.setOutlineThickness(r); }
	sf::Vector2f getPosition() { return cardBack.getPosition(); }
	sf::Vector2f getSize() { return cardBack.getSize(); }
};


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
	CCard(float x, float y, std::string title, std::string description, std::string imagePath, CAssetManager* assetParam);
	void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(float deltaTime);
};


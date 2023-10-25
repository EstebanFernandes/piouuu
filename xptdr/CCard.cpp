#include "CCard.h"

CCard::CCard()
{
}

CCard::CCard(float x, float y, std::string title, std::string description, std::string imageName, CAssetManager* assetParam)
{
	asset = assetParam;

	pos.x = x;
	pos.y = y;

	cardBack.setPosition(pos);
	cardBack.setFillColor(sf::Color::Black);
	cardBack.setSize(sf::Vector2f(xSize, ySize));


	cardTitle.setString(title);
	cardTitle.setFillColor(sf::Color::White);
	cardTitle.setFont(asset->GetFont("Lato"));
	cardTitle.setCharacterSize(75);
	cardTitle.setPosition(pos.x + (xSize - cardTitle.getGlobalBounds().width)/2, pos.y);

	//asset->LoadTexture("test", imagePath);
	cardImage.setTexture(assetParam->GetTexture(imageName));
	cardImage.setPosition(pos.x, pos.y);
	trucdesteban = CAnimation(&cardImage, sf::IntRect(0, 0, 153, 66), 4, 0.16f);

	cardDescription.setString(description);
	cardDescription.setFillColor(sf::Color::White);
	cardDescription.setFont(asset->GetFont("Lato"));
	cardDescription.setCharacterSize(35);
	cardDescription.setPosition(pos.x + (xSize - cardDescription.getGlobalBounds().width) / 2, pos.y + ySize*0.6f);
}

void CCard::update(float deltaTime)
{
	trucdesteban.updateAnimation();
}

void CCard::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(cardBack);
	target.draw(cardTitle);
	target.draw(cardImage);
	target.draw(cardDescription);
	
}
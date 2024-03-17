#include "CCard.h"

CCard::CCard()
{
	asset = NULL;
}
//pas utilisé
CCard::CCard(float x, float y, std::string title, std::string description, std::string imageName, CAssetManager* assetParam, bool animated)
	:CCard(title, description, imageName,assetParam,animated)
{
	setPosition(sf::Vector2f(x, y));
}

CCard::CCard(std::string title, std::string description, std::string imageName, CAssetManager* assetParam, bool animated)
{
	asset = assetParam;
	int screenheight = asset->sCREEN_HEIGHT;
	int screenwidth = asset->sCREEN_WIDTH;
	xSize = (float)screenwidth/ 3.f;
	ySize = (float)screenheight * 0.85f;

	cardBack.setFillColor(sf::Color::Black);
	cardBack.setSize(sf::Vector2f(xSize, ySize));
	pos.x = (screenwidth / 2) - (getGlobalBounds().width / 2);
	pos.y = (screenheight / 2) - (getGlobalBounds().height / 2);

	cardBack.setPosition(pos);

	animatedImage = animated;

	cardTitle.setString(title);
	cardTitle.setFillColor(sf::Color::White);
	cardTitle.setFont(asset->GetFont("Nouvelle"));
	cardTitle.setCharacterSize(75);
	cardTitle.setPosition(pos.x + (xSize - cardTitle.getGlobalBounds().width) / 2.f, pos.y);


	cardImage.setTexture(asset->GetTexture(imageName));
	//bizarre, à revoir
	cardImage.setPosition(pos.x + xSize/2.f - cardImage.getGlobalBounds().width / 2.f, pos.y + (ySize +cardImage.getGlobalBounds().height) / 2.f);
	
	if (animatedImage) {
		sf::IntRect temp = sf::IntRect(0, 0, 153, 66);
		anim.setParameters(&cardImage, temp, 4, 0.16f);
		cardImage.setTextureRect(temp);
	}

	cardDescription.setString(description);
	cardDescription.setFillColor(sf::Color::White);
	cardDescription.setFont(asset->GetFont("Nouvelle"));
	cardDescription.setCharacterSize(35);
	cardDescription.setPosition(pos.x + (xSize - cardDescription.getGlobalBounds().width) / 2, pos.y + ySize * 0.6f);
}

void CCard::update(float deltaTime)
{
	if (animatedImage) {
		if (MDRRcafonctionne++ == 1)
			anim.setSprite(&cardImage);
		anim.updateAnimation();
	}
}

void CCard::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(cardBack);
	target.draw(cardTitle);
	target.draw(cardImage);
	target.draw(cardDescription);
}
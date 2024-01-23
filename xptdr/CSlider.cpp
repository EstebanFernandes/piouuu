#include "CSlider.h"

CSlider::CSlider()
{
}

CSlider::CSlider(float width, float length)
{
}

CSlider::CSlider(CAssetManager* a,sf::Vector2f pos, sf::Vector2f size, std::string nameOfSlider)
{
	value = 0;
	hasTitle = true;
	style = Horizontal;
	asset = a;
	textPercentage.setFont(asset->GetFont("Lato"));
	textPercentage.setString("0%");
	textPercentage.setCharacterSize(20);
	NameOfSlider.setFont(asset->GetFont("Lato"));
	NameOfSlider.setString(nameOfSlider);
	NameOfSlider.setCharacterSize(20);
	back.setFillColor(sf::Color::Black);
	setSize(size);
	setPosition(pos);
	cursor.setRadius(5.f);
	cursor.setOrigin(cursor.getRadius(), cursor.getRadius());
	setCursor();
}

CSlider::CSlider(CAssetManager* a, sf::Vector2f size, std::string nameOfSlider)
{
	value = 0;
	hasTitle = true;
	style = Horizontal;
	asset = a;
	textPercentage.setFont(asset->GetFont("Lato"));
	textPercentage.setString("0%");
	textPercentage.setCharacterSize(20);
	NameOfSlider.setFont(asset->GetFont("Lato"));
	NameOfSlider.setString(nameOfSlider);
	NameOfSlider.setCharacterSize(20);
	back.setFillColor(sf::Color::Black);
	setSize(size);
	cursor.setRadius(5.f);
	cursor.setOrigin(cursor.getRadius(), cursor.getRadius());
	setCursor();
}

void CSlider::setPosition(float x, float y)
{
	back.setPosition(x, y);
	sf::Vector2f interiorPos;
	interiorPos.x = x + back.getGlobalBounds().width * padding.x;
	interiorPos.y = y + back.getGlobalBounds().height * padding.y;
	interiorBack.top = interiorPos.y;
	interiorBack.left = interiorPos.x;
	if (hasTitle)//Le slider n'a pas la même tête s'il n'a pas de titre
	{
		sf::Vector2f namePos = sf::Vector2f(interiorBack.left + interiorBack.width / 2.f - NameOfSlider.getGlobalBounds().width / 2.f,
			interiorBack.top);
		NameOfSlider.setPosition(namePos);
		namePos.x -= NameOfSlider.getGlobalBounds().left - namePos.x;
		namePos.y -= NameOfSlider.getGlobalBounds().top - namePos.y;
		NameOfSlider.setPosition(namePos);
		line.setPosition(interiorBack.left,
			interiorPos.y + (interiorBack.height - line.getGlobalBounds().height) / 2.f);
		sf::Vector2f textPerPos(
			interiorBack.left + (interiorBack.width - textPercentage.getGlobalBounds().width) / 2.f,
			interiorBack.top + interiorBack.height - textPercentage.getGlobalBounds().height);
		textPercentage.setPosition(textPerPos);
		textPerPos.x -= textPercentage.getGlobalBounds().left - textPerPos.x;
		textPerPos.y -= textPercentage.getGlobalBounds().top - textPerPos.y;
		textPercentage.setPosition(textPerPos);
	}

	minPoint = sf::Vector2f(
		line.getGlobalBounds().left,
		line.getGlobalBounds().top + line.getGlobalBounds().height / 2.f
	);
}

void CSlider::setName(std::string newName)
{
}

void CSlider::setCursor()
{
	float width = line.getGlobalBounds().width;
	cursor.setPosition(
		minPoint.x + (float)value * width/100.f,
		minPoint.y
	);
	textPercentage.setString(std::to_string(value) + "%");
}

void CSlider::setSize(float x, float y,unsigned int charSize =-1)
{
	back.setSize(sf::Vector2f(x,y));
	interiorBack.width = back.getGlobalBounds().width - back.getGlobalBounds().width * (2*padding.x);
	interiorBack.height = back.getGlobalBounds().height - back.getGlobalBounds().height * (2 * padding.y);
	line.setSize(sf::Vector2f(interiorBack.width, interiorBack.height * 0.03f));
	if (hasTitle && charSize != -1)
		NameOfSlider.setCharacterSize(charSize);
	if (charSize != -1)
		textPercentage.setCharacterSize(charSize);
}

void CSlider::setOutlineThickness(float thickness)
{
	back.setOutlineThickness(thickness);
}

void CSlider::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(back);
	target.draw(line);
	target.draw(cursor);
	if(hasTitle)
		target.draw(NameOfSlider);
	target.draw(textPercentage);
}
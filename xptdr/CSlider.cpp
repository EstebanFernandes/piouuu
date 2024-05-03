#include "CSlider.h"

CSlider::CSlider()
{
}

CSlider::CSlider(float width, float length)
{
}

CSlider::CSlider(CAssetManager* a, sf::Vector2f pos, sf::Vector2f size, std::string nameOfSlider)
	:CSlider(a, size, nameOfSlider)
{
	setPosition(pos);
}

CSlider::CSlider(CAssetManager* a, sf::Vector2f size, std::string nameOfSlider)
{
	value = 0;
	hasTitle = true;
	style = Horizontal;
	asset = a;
	textPercentage.setFont(asset->GetFont("Nouvelle"));
	textPercentage.setString("0%");
	textPercentage.setCharacterSize(20);
	NameOfSlider.setFont(asset->GetFont("Nouvelle"));
	NameOfSlider.setString(nameOfSlider);
	NameOfSlider.setCharacterSize(20);
	back.setFillColor(sf::Color::Black);
	setSize(size);
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
		line.setPosition(x + back.getGlobalBounds().width/2.f,
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
		line.getPosition().y
	);
	setCursor();
}

void CSlider::setName(std::string newName)
{
}

void CSlider::setSize(float x, float y, int charSize)
{
	back.setSize(sf::Vector2f(x, y));
	interiorBack.width = back.getGlobalBounds().width - back.getGlobalBounds().width * (2 * padding.x);
	interiorBack.height = back.getGlobalBounds().height - back.getGlobalBounds().height * (2 * padding.y);
	line.setSize(sf::Vector2f(interiorBack.width, interiorBack.height * 0.03f));
	line.setOrigin(line.getLocalBounds().width / 2.f,
		line.getLocalBounds().height / 2.f);
	cursor.setSize(sf::Vector2f(line.getGlobalBounds().height * 2.f, line.getGlobalBounds().height * 2.f));
	cursor.setOrigin(cursor.getLocalBounds().width / 2.f, cursor.getLocalBounds().height / 2.f);
	if (hasTitle && charSize != -1)
		NameOfSlider.setCharacterSize(charSize);
	if (charSize != -1)
		textPercentage.setCharacterSize(charSize);
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
void CSlider::setCharacterSize(unsigned int charSize) {
	if (hasTitle)
	{
		NameOfSlider.setCharacterSize(charSize);
		textPercentage.setCharacterSize(charSize);
	}
	//interiorBack.height = NameOfSlider.getGlobalBounds().height+
}




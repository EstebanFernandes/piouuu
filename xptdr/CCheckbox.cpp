#include "CCheckbox.h"


CCheckbox::CCheckbox(CAssetManager* a, sf::Vector2f pos, std::string titleOftheCheckbox, unsigned int charSize)
{
	isSelected = true;
	asset = a;
	nameOfCheckbox.setFont(a->GetFont("Lato"));
	std::string mdrr(titleOftheCheckbox + "   ");
	nameOfCheckbox.setString(mdrr);
	nameOfCheckbox.setCharacterSize(charSize);
	check.setFont(a->GetFont("Lato"));
	check.setString("X");
	check.setCharacterSize(50);
	check.setOrigin(check.getLocalBounds().width / 2.f,
		check.getLocalBounds().height / 2.f);
	box.setFillColor(sf::Color(255, 255, 255, 0));
	box.setOutlineThickness(3.f);
	check1.setRotation(45);
	check2.setRotation(135);
	initCheckbox();
	setPosition(pos);
}

CCheckbox::CCheckbox(CAssetManager* a, std::string titleOftheCheckbox, unsigned int charSize)
{
	isSelected = true;
	asset = a;
	nameOfCheckbox.setFont(a->GetFont("Lato"));
	std::string mdrr(titleOftheCheckbox + "   ");
	nameOfCheckbox.setString(mdrr);
	nameOfCheckbox.setCharacterSize(charSize);
	check.setFont(a->GetFont("Lato"));
	check.setString("X");
	check.setCharacterSize(50);
	check.setOrigin(check.getLocalBounds().width / 2.f,
		check.getLocalBounds().height / 2.f);
	box.setFillColor(sf::Color(255, 255, 255, 0));
	box.setOutlineThickness(3.f);
	check1.setRotation(45);
	check2.setRotation(135);
	initCheckbox();
}

void CCheckbox::initCheckbox()
{
	interiorBack.height = nameOfCheckbox.getGlobalBounds().height+3.f;
	check1.setSize(sf::Vector2f(interiorBack.height*1.75f, 4.f));
	check1.setOrigin(check1.getLocalBounds().width / 2.f,
		check1.getLocalBounds().height / 2.f);
	check2.setSize(sf::Vector2f(interiorBack.height * 1.75f, 4.f));
	check2.setOrigin(check2.getLocalBounds().width / 2.f,
		check2.getLocalBounds().height / 2.f);
	box.setSize(sf::Vector2f(interiorBack.height-3.f, interiorBack.height - 3.f));
	float width = nameOfCheckbox.getGlobalBounds().width+interiorBack.height;
	interiorBack.width = width;
	sf::Vector2f backSize(width,interiorBack.height);
	sf::Vector2f prc(100.f*(1.f - (padding.x * 2.f)), 100.f * (1.f - (padding.y * 2.f)));
	backSize.x =  100.f*backSize.x / prc.x;
	backSize.y =  100.f*backSize.y / prc.y;
	back.setSize(backSize);
	back.setFillColor(sf::Color::Black);
}
void CCheckbox::setPosition(float x, float y)
{
	back.setPosition(x, y);
	sf::Vector2f interiorPos;
	interiorPos.x = x + back.getGlobalBounds().width * padding.x;
	interiorPos.y = y + back.getGlobalBounds().height * padding.y;
	interiorBack.top = interiorPos.y;
	interiorBack.left = interiorPos.x;
	if (hasTitle)//Le slider n'a pas la même tête s'il n'a pas de titre
	{
		sf::Vector2f namePos = sf::Vector2f(interiorBack.left + interiorBack.width / 2.f - nameOfCheckbox.getGlobalBounds().width / 2.f,
			interiorBack.top);
		nameOfCheckbox.setPosition(namePos);
		namePos.x -= nameOfCheckbox.getGlobalBounds().left - namePos.x;
		namePos.y -= nameOfCheckbox.getGlobalBounds().top - namePos.y;
		nameOfCheckbox.setPosition(namePos);
		box.setPosition(nameOfCheckbox.getGlobalBounds().width + nameOfCheckbox.getGlobalBounds().left,
			interiorBack.top);
			check1.setPosition(box.getPosition().x+box.getSize().x / 2.f,
				box.getPosition().y + box.getSize().y / 2.f);
			check2.setPosition(box.getPosition().x + box.getSize().x / 2.f,
				box.getPosition().y + box.getSize().y / 2.f);
	}

}
void CCheckbox::setSize(float x, float y)
{
}
void CCheckbox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(back);
	target.draw(box);
	if (isSelected)
	{
		target.draw(check1);
		target.draw(check2);
	}
	if (hasTitle)
		target.draw(nameOfCheckbox);
}
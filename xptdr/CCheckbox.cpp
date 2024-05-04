#include "CCheckbox.h"


CCheckbox::CCheckbox(CAssetManager* a, sf::Vector2f pos, std::string titleOftheCheckbox, unsigned int charSize)
	:CCheckbox(a,titleOftheCheckbox,charSize)
{
	setPosition(pos);
}

CCheckbox::CCheckbox(CAssetManager* a, std::string titleOftheCheckbox, unsigned int charSize)
{
	isSelected = true;
	asset = a;
	nameOfCheckbox.setFont(a->GetFont("Nouvelle"));
	std::string mdrr(titleOftheCheckbox + "   ");
	nameOfCheckbox.setString(mdrr);
	nameOfCheckbox.setCharacterSize(charSize);
	check.setFont(a->GetFont("Nouvelle"));
	check.setString("X");
	check.setCharacterSize(50);
	check.setOrigin(check.getLocalBounds().width / 2.f,
		check.getLocalBounds().height / 2.f);
	box.setFillColor(sf::Color(255, 255, 255, 0));
	box.setOutlineThickness(3.f);
	initCheckbox();
}

void CCheckbox::initCheckbox()
{
	interiorBack.height = nameOfCheckbox.getGlobalBounds().height+3.f;
	check1.setSize(sf::Vector2f(interiorBack.height*1.75f, 4.f));
	check1.setOrigin(check1.getLocalBounds().width / 2.f,
		check1.getLocalBounds().height / 2.f);
	check2 = check1;
	check1.setRotation(45);
	check2.setRotation(135);
	box.setSize(sf::Vector2f(interiorBack.height-3.f, interiorBack.height - 3.f));
	box.setOrigin(box.getLocalBounds().width / 2.f, box.getLocalBounds().height / 2.f);
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
		float ouais = nameOfCheckbox.getGlobalBounds().width + box.getGlobalBounds().width;
		float inter = (interiorBack.width - ouais) / 2.f;
		sf::Vector2f namePos = sf::Vector2f(interiorPos.x + inter,
			interiorPos.y + (interiorBack.height - nameOfCheckbox.getGlobalBounds().height) / 2.f);
		nameOfCheckbox.setPosition(namePos);
		namePos.y += nameOfCheckbox.getGlobalBounds().height ;
		box.setPosition(
			interiorPos.x + inter + nameOfCheckbox.getGlobalBounds().width,
			namePos.y);
		check1.setPosition(box.getPosition().x-box.getOutlineThickness(),
			box.getPosition().y - check1.getGlobalBounds().height / 2.f + box.getLocalBounds().height / 2.f);
		check2.setPosition(box.getPosition().x - check2.getGlobalBounds().width / 2.f + box.getLocalBounds().width / 2.f,
			box.getPosition().y - box.getOutlineThickness());
	}

}
void CCheckbox::setSize(float x, float y)
{
	back.setSize(sf::Vector2f(x, y));
	interiorBack.height = y-padding.y * y;
	interiorBack.width = x-padding.x * x;
	setPosition(interiorBack.getPosition());
}
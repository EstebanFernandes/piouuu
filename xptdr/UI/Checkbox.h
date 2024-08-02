#pragma once
#include"UI.h"
/// <summary>
/// Classe qui repr�sente une checkbox
/// </summary>
class Checkbox : public UI
{
private:
	/// <summary>
	/// Box de la checkbox, donc le carr� 
	/// </summary>
	sf::RectangleShape box;
	/// <summary>
	/// Croix (un X) qui nous dit si oui ou non on a s�lectionn� notre objet
	/// </summary>
	sf::Text check;
	sf::RectangleShape check1;
	sf::RectangleShape check2;
	sf::Text nameOfCheckbox;
	bool hasTitle;
	bool isSelected;
	/// <summary>
	/// 
	/// </summary>
	void initCheckbox();
public:
	Checkbox(){}
	Checkbox(AssetManager* a, sf::Vector2f pos, std::string titleOftheCheckbox, unsigned int charSize = 30);
	Checkbox(AssetManager* a, std::string titleOftheCheckbox, unsigned int charSize = 30);
	bool getValue() { return isSelected; }
	void setValue(bool val) {
		isSelected = val;
	}
	void setValue(int val) {
		if (val == 0 || val == 1)
			isSelected = val;
	}

	void setPosition(float x, float y);
	void setPosition(sf::Vector2f r) {
		setPosition(r.x, r.y);
	}
	void setSize(float x, float y);
	void setSize(sf::Vector2f r) {
		setSize(r.x, r.y);
	}
	void changeValue()
	{
		if (isSelected)
			isSelected = false;
		else
			isSelected = true;
	}
	void setScale(sf::Vector2f scale) {}
	void setFontColor(sf::Color colorParam) {}

	void setCharacterSize(unsigned int charSize) {
		nameOfCheckbox.setCharacterSize(charSize);
		box.setSize(sf::Vector2f(nameOfCheckbox.getGlobalBounds().height, nameOfCheckbox.getGlobalBounds().height));
		box.setOrigin(box.getLocalBounds().width / 2.f, box.getLocalBounds().height / 2.f);
		box.setOutlineThickness(box.getGlobalBounds().width * 0.1f);
		check1.setRotation(0);
		check2.setRotation(0);
		check1.setSize(sf::Vector2f(box.getGlobalBounds().height * 1.5f,4.f));
		check1.setOrigin(check1.getLocalBounds().width / 2.f,
			check1.getLocalBounds().height / 2.f);
		check2 = check1;
		check1.setRotation(45);
		check2.setRotation(135);
		setPosition(back.getPosition());
	}
	unsigned int getCharacterSize() { return nameOfCheckbox.getCharacterSize(); }
	void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const {
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
};


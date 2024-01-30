#pragma once
#include"CUI.h"
/// <summary>
/// Classe qui représente une checkbox
/// </summary>
class CCheckbox : public CUI
{
private:
	/// <summary>
	/// Box de la checkbox, donc le carré 
	/// </summary>
	sf::RectangleShape box;
	/// <summary>
	/// Croix (un X) qui nous dit si oui ou non on a sélectionné notre objet
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
	CCheckbox(){}
	CCheckbox(CAssetManager* a, sf::Vector2f pos, std::string titleOftheCheckbox, unsigned int charSize = 30);
	CCheckbox(CAssetManager* a, std::string titleOftheCheckbox, unsigned int charSize = 30);
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
		box.setOutlineThickness(box.getGlobalBounds().width * 0.1f);
		check1.setSize(sf::Vector2f(box.getGlobalBounds().height * 1.75f,box.getOutlineThickness()));
		check2.setSize(check1.getSize());
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


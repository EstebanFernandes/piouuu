#pragma once
#include"SFML/Graphics.hpp"
#include"CAssetManager.h"
/// <summary>
/// Classe qui représente une checkbox
/// </summary>
class CCheckbox : public sf::Drawable
{
private:
	CAssetManager* asset;
	/// <summary>
	/// back panel de la checkbox, peut ne pas être dessiné
	/// </summary>
	sf::RectangleShape back;
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
	bool hasBack;
	bool isSelected;
	sf::Vector2f padding = sf::Vector2f(0.05f, 0.05f);

	/// <summary>
	/// Rectangle intérieur dans lequel on met les élements, on tient ici compte du padding
	/// </summary>
	sf::FloatRect interiorBack;
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
	void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setOutlineThickness(float thickness) {
		back.setOutlineThickness(thickness);
	}
	void setSize(float x, float y);
	void setSize(sf::Vector2f r) {
		setSize(r.x, r.y);
	}
	sf::Vector2f getSize() { return back.getSize(); }
	void changeValue()
	{
		if (isSelected)
			isSelected = false;
		else
			isSelected = true;
	}
};


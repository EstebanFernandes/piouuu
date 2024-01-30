#pragma once
#include"SFML/Graphics.hpp"
#include"CAssetManager.h"
/// <summary>
/// Classe de base pour gérer des UI, cela contient des élements commun à tous les élements d'UI (slider, checkbox et texte)
/// </summary>
class CUI : public sf::Drawable
{
protected:
	CAssetManager* asset;
	/// <summary>
	/// back panel 
	/// </summary>
	sf::RectangleShape back;
	bool isBackVisible;
	/// <summary>
	/// Le padding est l'écartement entre le back et la ligne du slider (le padding est le même à droite et à gauche)
	/// </summary>
	sf::Vector2f padding = sf::Vector2f(0.05f, 0.05f);
	/// <summary>
	/// Rectangle intérieur dans lequel on met les élements, on tient ici compte du padding
	/// </summary>
	sf::FloatRect interiorBack;
public:
	sf::FloatRect getGlobalBounds() {
		return back.getGlobalBounds();
	}
	void changeBackVisibilty(bool f) {
		isBackVisible = f;
		if (isBackVisible)
			back.setFillColor(sf::Color::Black);
		else
			back.setFillColor(sf::Color(255, 255, 255, 0));
	}
	void setColor(sf::Color colorParam) {
		back.setFillColor(colorParam);
	}
	void setOutlineThickness(float thickness) { back.setOutlineThickness(thickness); }
	sf::Vector2f getSize() { return back.getSize(); }
	virtual void setSize(sf::Vector2f f) { setSize(f.x, f.y); }
	virtual void setSize(float xSizeParam, float ySizeParam) = 0;
	virtual void setCharacterSize(unsigned int charSize) = 0;
	virtual unsigned int getCharacterSize()=0;
	virtual void setFontColor(sf::Color colorParam) = 0;
	void setThicknessColor(sf::Color colorParam) { back.setOutlineColor(colorParam); }
	virtual void setScale(sf::Vector2f scale)=0;
	void setPosition(sf::Vector2f pos) { setPosition(pos.x, pos.y); }
	virtual void setPosition(float x, float y) = 0;
};


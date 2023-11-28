#pragma once
#include <SFML/Graphics.hpp>
#include "CJeu.h"

class CButton : public sf::Drawable
{
private:
	GameDataRef data;
	sf::Text text;
	sf::RectangleShape back;
	float xSize;
	float ySize;

	void resizeText(sf::Text& textToResize);
public:
	CButton();
	CButton(GameDataRef dataParam);
	CButton(GameDataRef dataParam, float xSize, float ySize);
	void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setSize(float xSizeParam, float ySizeParam);
	void setPos(float xParam, float yParam);
	void setColor(sf::Color colorParam);
	void setFontColor(sf::Color colorParam);
	void setOutlineThickness(float fParam);
	void setThicknessColor(sf::Color colorParam);
	void setString(std::string strParam);

};


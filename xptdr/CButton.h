#pragma once
#include <SFML/Graphics.hpp>
#include "CJeu.h"
//This class represent a button, You can define the text inside, the font and the size of it
class CButton : public sf::Drawable
{
private:
	GameDataRef data;
	sf::Text text;
	sf::RectangleShape back;
	//width of the button
	float xSize;
	//Height of the button
	float ySize;
	//method that resize taking in consideration the back of the button
	void resizeText(sf::Text& textToResize);
public:
	CButton() {
		xSize = 0;
		ySize = 0;
	}
	CButton(GameDataRef dataParam);
	CButton(GameDataRef dataParam, float xSize, float ySize);
	void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//method that set the size of the back of the button and resize the text to fit in
	void setSize(float xSizeParam, float ySizeParam);
	//set the position of the Button
	void setPos(float xParam, float yParam);
	void setPos(sf::Vector2f pos) {
		setPos(pos.x, pos.y);
	}
	void setColor(sf::Color colorParam);
	void setFontColor(sf::Color colorParam);
	void setOutlineThickness(float fParam);
	void setThicknessColor(sf::Color colorParam);
	void setString(std::string strParam);
	void setScale(sf::Vector2f scale);
	sf::FloatRect getGlobalBounds() {
		return back.getGlobalBounds();
	}
	void displayButtonInfo() {
		std::cout << "Back info : x : " << back.getPosition().x
			<< " y : " << back.getPosition().y<<std::endl;
		std::cout <<"Text info : Name : " << text.getString().toAnsiString() << " x : " << text.getPosition().x
			<< " y : " << text.getPosition().y << std::endl;
		std::cout << "Text global bounds : top : " << text.getGlobalBounds().top <<
			" left : " << text.getGlobalBounds().left << " height : " << text.getGlobalBounds().height <<
			" width : " << text.getGlobalBounds().width ;
	}

	sf::Vector2f getTextPosition() {
		return text.getPosition();
	}
	void setTextPosition(sf::Vector2f pos)
	{
		text.setPosition(pos);
	}
	//set the size of the text of the button and center the text
	void setCharacterSize(unsigned int charSize);
	void centerText();
	unsigned int getCharacterSize() {
		return text.getCharacterSize();
	}
};


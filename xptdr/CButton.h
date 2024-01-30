#pragma once
#include"CUI.h"
#include<iostream>
//This class represent a button, You can define the text inside, the font and the size of it
class CButton : public CUI
{
private:
	sf::Text text;
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
	CButton(CAssetManager* a);
	CButton(CAssetManager* a, std::string title, float xSize, float ySize);
	CButton(CAssetManager* a, float xSize, float ySize);
	//method that set the size of the back of the button and resize the text to fit in
	void setSize(sf::Vector2f f) { setSize(f.x, f.y); }
	void setSize(float xSizeParam, float ySizeParam);
	//set the position of the Button
	void setPosition(float xParam, float yParam);
	void setFontColor(sf::Color colorParam);
	void setOutlineThickness(float fParam);
	void setThicknessColor(sf::Color colorParam);
	void setScale(sf::Vector2f scale);
	void setString(std::string strParam);
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
	void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(back);
		target.draw(text);
	}
};


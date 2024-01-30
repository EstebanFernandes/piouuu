#pragma once
#define Horizontal true
#define Vertical false
#include"CUI.h"
//Class that represent a slider 
class CSlider :public CUI
{
private:
	//represent the line of the slider
	sf::RectangleShape line;
	sf::CircleShape cursor;
	sf::Text textPercentage;
	//Coordinate of the minimum point ie 0%
	sf::Vector2f minPoint;
	//Optional
	
	/// <summary>
	/// Titre du slider, est affiché au dessus 
	/// </summary>
	sf::Text NameOfSlider;
	int value;
	//only two style, horizontal or vertical
	bool style;
	bool hasTitle;
	/// <summary>
	/// method that set the cursor within the value, minimum point and width of the slider
	/// </summary>
	void setCursor();
public:
	CSlider();
	CSlider(float width, float length);
	/// <summary>
///  confort constructor
/// </summary>
/// <param name="assetmanager"></param>
/// <param name="position"></param>
/// <param name="size of the Slider"></param>
/// <param name="Title of the slider"></param>
/// <returns> None</returns>
	CSlider(CAssetManager* a, sf::Vector2f pos, sf::Vector2f size, std::string nameOfSlider);

	CSlider(CAssetManager* a, sf::Vector2f size, std::string nameOfSlider);

	int getValue() {
		return value;
	}
	/// <summary>
///  set the position of the slider from top left corner of the back
/// </summary>
/// <param name="x position"></param>
/// <param name="y position"></param>
	void setPosition(float x, float y);
	/// <summary>
	///  set the name of the slider
	/// </summary>
	/// <param name="newName"></param>
	/// <returns> None</returns>
	void setName(std::string newName);
	//value--;
	void slideLeft()
	{
		if (value != 0)
		{
			value--;
			setCursor();
		}
	}

	void slideLeft(int n)
	{
		for (int i = 0; i < n; i++)
			slideLeft();
	}
	void slideRight()
	{
		if (value != 100)
		{
			value++;
			setCursor();

		}
	}

	void slideRight(int n)
	{
		for (int i = 0; i < n; i++)
			slideRight();
	}

	void setSize(float x, float y,  int charSize=-1);
	void setSize(sf::Vector2f size, int charSize = -1) {
		setSize(size.x, size.y, charSize);
	}
	void setPosition(sf::Vector2f pos)
	{
		setPosition(pos.x, pos.y);
	}
	void setValue(int valuee)
	{
		if (valuee >= 0 && valuee <= 100)
			value = valuee;
		setCursor();
	}
	void setScale(sf::Vector2f scale){}
	void setFontColor(sf::Color colorParam){}
	void setSize(float x, float y)
	{
		setSize(x, y, -1);
	}
	void setCharacterSize(unsigned int charSize);
	unsigned int getCharacterSize() { return NameOfSlider.getCharacterSize(); }
	void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(back);
		target.draw(line);
		target.draw(cursor);
		if (hasTitle)
			target.draw(NameOfSlider);
		target.draw(textPercentage);
	}
};


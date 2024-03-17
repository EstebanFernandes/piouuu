#pragma once
#include <sstream>
#include <string>
#include "CAssetManager.h"
#include "DEFINITIONS.h"
#include "CAnimation.h"
#include "CCharacter.h"
#include"utilities.h"
class CCard : public sf::Drawable
{
protected :
	int MDRRcafonctionne = 0;
	CAssetManager* asset;

	sf::RectangleShape cardBack;
	sf::Vector2f pos;

	sf::Text cardTitle;
	sf::Text cardDescription;

	std::string imagePath;
	sf::Sprite cardImage;
	CAnimation anim;
	

	bool animatedImage;
	bool needImage;

	float xSize;
	float ySize;
	sf::Vector2f padding;

public:
	CCard();
	CCard(const CCard& Param) {
		this->operator=(Param);
	}
	CCard(float x, float y, std::string title, std::string description, std::string imageName, CAssetManager* assetParam, bool animated);
	CCard(std::string title, std::string description, std::string imageName, CAssetManager* assetParam, bool animated);
	void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(float deltaTime);
	sf::FloatRect getGlobalBounds()
	{
		return cardBack.getGlobalBounds();
	}
	void setAnimated(bool animated) { animatedImage = animated; }
	void setPosition(sf::Vector2f r)
	{
		pos = r;
		cardBack.setPosition(pos);
		float xoff = cardTitle.getGlobalBounds().width;
		sf::Vector2f offset( (xSize - xoff)/2.f, ySize * 0.02f);
		utilities::readaptText(cardTitle, pos+offset);
		cardImage.setPosition(pos.x + xSize / 2.f - cardImage.getGlobalBounds().width / 2.f, pos.y + ySize/2.f - cardImage.getGlobalBounds().height/ 2.f);
		cardDescription.setPosition(pos.x + (xSize - cardDescription.getGlobalBounds().width) / 2, pos.y + ySize * 0.6f);
	}
	void setScale(sf::Vector2f scale)
	{
		cardBack.setScale(scale);
		xSize = cardBack.getGlobalBounds().width-2*cardBack.getOutlineThickness();
		ySize = cardBack.getGlobalBounds().height -2* cardBack.getOutlineThickness();
		cardTitle.setScale(scale);
		cardImage.setScale(scale);
		cardDescription.setScale(scale);
		setPosition(pos);
	}
	void setScale(float x,float y)
	{
		setScale(sf::Vector2f(x, y));
	}

	CCard& operator=(const CCard& Param) {
		MDRRcafonctionne = Param.MDRRcafonctionne;
		asset = Param.asset;
		cardBack = Param.cardBack;
		pos = Param.pos;
		cardTitle = Param.cardTitle;
		cardDescription = Param.cardDescription;
		imagePath = Param.imagePath;
		cardImage = Param.cardImage;
		anim = Param.anim;
		needImage = Param.needImage;
		animatedImage = Param.animatedImage;
		xSize = Param.xSize;
		ySize = Param.ySize;
		return *this;
	}

	void setOutlineThickNess(float r) { cardBack.setOutlineThickness(r); }
	sf::Vector2f getPosition() { return cardBack.getPosition(); }
	sf::Vector2f getSize() { return cardBack.getSize(); }
	void setSize(sf::Vector2f newSize) {
		sf::Vector2f scale(newSize.x/ xSize, newSize.y/ ySize );
		xSize = newSize.x;
		ySize = newSize.y;
		
		cardBack.setSize(sf::Vector2f(xSize, ySize));
		cardTitle.setCharacterSize((unsigned int)((float)cardTitle.getCharacterSize() * scale.x));
		resizeText(cardTitle);
		cardTitle.setPosition(pos.x + (xSize - cardTitle.getGlobalBounds().width) / 2, pos.y);
		
		cardImage.setPosition(pos.x + ((xSize - cardImage.getGlobalBounds().height) / 2.0f), pos.y + ySize / 2);
		
		cardDescription.setCharacterSize((unsigned int)((float)cardDescription.getCharacterSize() * scale.x));
		resizeText(cardDescription);
		cardDescription.setPosition(pos.x + (xSize - cardDescription.getGlobalBounds().width) / 2, pos.y + ySize * 0.6f);
	}
	/// <summary>
	/// Cette fonction réduit la taille du texte afin de le faire fit (si on a qu'un argument, 
	/// si on passe false au deuxième argument il va juste diviser le texte
	/// </summary>
	/// <param name="textToResize"></param>
	/// <param name="minCharsSize"></param>
	void resizeText(sf::Text& textToResize,bool minCharsSize=true)
	{
		if (minCharsSize == true)
		{
			while (
				textToResize.getGlobalBounds().width >= xSize * 0.95f &&
				textToResize.getCharacterSize() >= 15)
			{
				textToResize.setCharacterSize(textToResize.getCharacterSize() - 1);
			}
		}
		int dividedIn = 1;
		std::string basicString = textToResize.getString();
		while (textToResize.getGlobalBounds().width >= xSize * 0.95f)
		{
			dividedIn++;
			std::string temp = basicString;
			for (int i = 1; i < dividedIn; i++)
			{
				int R = (int)(temp.size() / (float)(dividedIn)) * i;
				for (int j = R; j < temp.size(); j++)
				{
					if (temp[j] == ' ')
					{
						temp.insert(j, "\n");
						textToResize.setString(temp);
						break;
					}
				}
			}
		}
	}
	void resizeText(sf::Text& textToResize,unsigned int charSize, bool divided = true)
	{	
		while (
			textToResize.getGlobalBounds().width >= xSize * 0.95f &&
			textToResize.getCharacterSize() >= charSize)
		{
			textToResize.setCharacterSize(textToResize.getCharacterSize() - 1);
		}
		if (divided)
		{
			int dividedIn = 1;
			std::string basicString = textToResize.getString();
			while (textToResize.getGlobalBounds().width >= xSize * 0.95f)
			{
				dividedIn++;
				std::string temp = basicString;
				for (int i = 1; i < dividedIn; i++)
				{
					int R = (int)(temp.size() / (float)(dividedIn)) * i;
					for (int j = R; j < temp.size(); j++)
					{
						if (temp[j] == ' ')
						{
							temp.insert(j, "\n");
							textToResize.setString(temp);
							break;
						}
					}
				}
			}
		}
	}
	
	
	sf::Vector2f getScale() {
		return cardBack.getScale();
	}
	void setTitleCharSize(unsigned int size)
	{
		cardTitle.setCharacterSize(size);
	}
	unsigned int getTitleCharSize()
	{
		return cardTitle.getCharacterSize();
	}
	void setDescriptionCharSize(unsigned int size)
	{
		cardDescription.setCharacterSize(size);
	}
	unsigned int getDescriptionCharSize()
	{
		return cardDescription.getCharacterSize();
	}
};


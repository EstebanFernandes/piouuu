#include "CButton.h"

CButton::CButton(CAssetManager* a)
{
	asset = a;
	text.setFont(asset->GetFont("Nouvelle"));
	text.setString("Button");
	setColor(sf::Color::Black);
	setFontColor(sf::Color::White);

	//temp la taille
	setSize(300, 150);
	setPosition(0, 0);
	text.setLineSpacing(0.f);
}

CButton::CButton(CAssetManager* a, std::string title, float xSize, float ySize)
 : CButton(a,xSize,ySize)
{
	setString(title);
}

CButton::CButton(CAssetManager* a, float xSizeParam, float ySizeParam)
	:CButton(a)
{
	setPosition(0, 0);
	setSize(xSizeParam, ySizeParam);
}

void CButton::setSize(float xSizeParam, float ySizeParam)
{
	xSize = xSizeParam;
	ySize = ySizeParam;
	back.setSize(sf::Vector2f(xSize, ySize));
	resizeText(text);

}

void CButton::setPosition(float xParam, float yParam)
{
	back.setPosition(sf::Vector2f(xParam, yParam));
	sf::FloatRect backBounds = back.getGlobalBounds();
	sf::FloatRect textBounds = text.getGlobalBounds();
	float xPositionText = xParam + backBounds.width / 2.f - textBounds.width / 2.f;
	float yPositionText = yParam + backBounds.height / 2.f - textBounds.height / 2.f;
	text.setPosition(xPositionText, yPositionText);
	xPositionText -= text.getGlobalBounds().left - xPositionText;
	yPositionText -= text.getGlobalBounds().top - yPositionText;
	text.setPosition(xPositionText,yPositionText);
}


void CButton::setFontColor(sf::Color colorParam)
{
	text.setFillColor(colorParam);
}

void CButton::setOutlineThickness(float fParam)
{
	back.setOutlineThickness(fParam);
}

void CButton::setThicknessColor(sf::Color colorParam)
{
	back.setOutlineColor(colorParam);
}

void CButton::setString(std::string strParam)
{
	text.setString(strParam);
	resizeText(text);
	//setPos(back.getPosition().x, back.getPosition().y);
}

void CButton::setScale(sf::Vector2f scale)
{
	back.setScale(scale);
	xSize = back.getGlobalBounds().width;
	ySize = back.getGlobalBounds().height;
	text.setScale(scale);
	CUI::setPosition(back.getPosition());
}

void CButton::setCharacterSize(unsigned int charSize)
{
	text.setCharacterSize(charSize);
	centerText();
}

void CButton::centerText()
{
	sf::FloatRect backBounds = back.getGlobalBounds();
	sf::FloatRect textBounds = text.getGlobalBounds();
	float xPositionText = backBounds.width / 2.f - textBounds.width / 2.f;
	float yPositionText = backBounds.height / 2.f - textBounds.height / 2.f;
	text.setPosition(xPositionText, yPositionText);
	xPositionText -= text.getGlobalBounds().left - xPositionText;
	yPositionText -= text.getGlobalBounds().top - yPositionText;
	text.setPosition(
		backBounds.left + backBounds.width / 2.f - textBounds.width / 2.f,
		backBounds.top + backBounds.height / 2.f - textBounds.height / 2.f);
}

void CButton::resizeText(sf::Text& textToResize)
{
	if (textToResize.getGlobalBounds().width >= back.getGlobalBounds().width)
	{
		while (textToResize.getGlobalBounds().width >=
			back.getGlobalBounds().width - back.getGlobalBounds().width * 0.05f &&
			textToResize.getCharacterSize() >= 10)
		{
			textToResize.setCharacterSize(textToResize.getCharacterSize() - 1);
		}
		int dividedIn = 1;
		std::string basicString = textToResize.getString();
		while (textToResize.getGlobalBounds().width >= back.getGlobalBounds().width - back.getGlobalBounds().width * 0.05f)
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
	else
	{
		/*while (textToResize.getGlobalBounds().width <=
			back.getGlobalBounds().width* 0.90f &&
			textToResize.getGlobalBounds().height <=
			back.getGlobalBounds().height * 0.90f)
		{
			textToResize.setCharacterSize(textToResize.getCharacterSize() + 1);
		}*/
	}
	sf::FloatRect backBounds = back.getGlobalBounds();
	sf::FloatRect textBounds = text.getGlobalBounds();
	float xPositionText = backBounds.width / 2.f - textBounds.width / 2.f;
	float yPositionText = backBounds.height / 2.f - textBounds.height / 2.f;
	text.setPosition(xPositionText, yPositionText);
	xPositionText -= text.getGlobalBounds().left - xPositionText;
	yPositionText -= text.getGlobalBounds().top - yPositionText;
	text.setPosition(
		backBounds.left + backBounds.width/2.f - textBounds.width/ 2.f,
		backBounds.top + backBounds.height/2.f - textBounds.height/ 2.f);
}


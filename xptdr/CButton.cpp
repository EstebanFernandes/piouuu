#include "CButton.h"

CButton::CButton(GameDataRef dataParam)
{
	data = dataParam;
	text.setFont(data->assets.GetFont("Lato"));
	text.setString("Button");
	setColor(sf::Color::Black);
	setFontColor(sf::Color::White);

	//temp la taille
	setSize(300, 150);
	setPos(0, 0);
}

CButton::CButton(GameDataRef dataParam, float xSizeParam, float ySizeParam)
{
	data = dataParam;
	text.setFont(data->assets.GetFont("Lato"));
	text.setString("Button");
	setColor(sf::Color::Black);
	setFontColor(sf::Color::White);

	setPos(0, 0);
	setSize(xSizeParam, ySizeParam);
}

void CButton::setSize(float xSizeParam, float ySizeParam)
{
	xSize = xSizeParam;
	ySize = ySizeParam;
	back.setSize(sf::Vector2f(xSize, ySize));
	resizeText(text);

}

void CButton::setPos(float xParam, float yParam)
{
	back.setPosition(sf::Vector2f(xParam, yParam));
	text.setPosition(xParam + (back.getGlobalBounds().width - text.getLocalBounds().getSize().x) / 2.f, yParam + (back.getGlobalBounds().height - text.getLocalBounds().getSize().y) / 2.f);
}

void CButton::setColor(sf::Color colorParam)
{
	back.setFillColor(colorParam);
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
}

void CButton::setScale(sf::Vector2f scale)
{
	back.setScale(scale);
	xSize = back.getGlobalBounds().width;
	ySize = back.getGlobalBounds().height;
	text.setScale(scale);
	setPos(back.getPosition());
}

//void CButton::setCharacterSize(unsigned int charSize)
//{
//	unsigned int prevCharSize = text.getCharacterSize();
//	int sum = 0;
//	text.setCharacterSize(charSize);
//	if (prevCharSize > charSize)
//		sum++;
//	else if (prevCharSize < charSize)
//		sum--;
//		while (text.getGlobalBounds().width * 0.95f >= back.getGlobalBounds().width)
//		{
//			back.setSize(sf::Vector2f(back.getSize().x + 1, back.getSize().y));
//		}
//		while (text.getGlobalBounds().width * 0.95f >= back.getGlobalBounds().width)
//		{
//			back.setSize(sf::Vector2f(back.getSize().x + 1, back.getSize().y));
//		}
//}

void CButton::resizeText(sf::Text& textToResize)
{
	while (textToResize.getGlobalBounds().width >=
		back.getGlobalBounds().width - back.getGlobalBounds().width * 0.05f &&
		textToResize.getCharacterSize() >= 20)
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
	text.setPosition(back.getPosition().x + (back.getGlobalBounds().width - text.getGlobalBounds().width) / 2.f, back.getPosition().y + (back.getGlobalBounds().height - text.getGlobalBounds().height) / 2.f);

}

void CButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(back);
	target.draw(text);
}
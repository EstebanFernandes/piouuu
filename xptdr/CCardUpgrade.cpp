#include "CCardUpgrade.h"

CCardUpgrade::CCardUpgrade(float x, float y, std::string title, std::string description, std::vector<std::string> Upgrade, std::vector<std::string> type, CAssetManager* assetParam)
{
	asset = assetParam;
	xSize = (float)asset->sCREEN_WIDTH / 3.f;
	ySize = (float)asset->sCREEN_HEIGHT * 0.85f;
	pos.x = x;
	pos.y = y;

	cardBack.setPosition(pos);
	cardBack.setFillColor(sf::Color::Black);
	cardBack.setSize(sf::Vector2f(xSize, ySize));


	cardTitle.setString(title);
	cardTitle.setFillColor(sf::Color::White);
	cardTitle.setFont(asset->GetFont("Lato"));
	cardTitle.setCharacterSize(75);
	cardTitle.setPosition(pos.x + (xSize - cardTitle.getGlobalBounds().width) / 2, pos.y);

	for (int i = 0; i < type.size(); i++)
	{
		sf::Text temp;
		std::string tempString = type[i] + Upgrade[i];
		temp.setString(tempString);
		temp.setFillColor(sf::Color::White);
		temp.setFont(asset->GetFont("Lato"));
		temp.setCharacterSize(35);
		int posY = pos.y + ySize * 0.3f+(temp.getLineSpacing()*(i+1));
		temp.setPosition(pos.x + (xSize - temp.getGlobalBounds().width) / 2, pos.y + ySize * 0.4f);
	}

	cardDescription.setString(description);
	cardDescription.setFillColor(sf::Color::White);
	cardDescription.setFont(asset->GetFont("Lato"));
	cardDescription.setCharacterSize(35);
	cardDescription.setPosition(pos.x + (xSize - cardDescription.getGlobalBounds().width) / 2, pos.y + ySize * 0.8f);
}

CCardUpgrade::CCardUpgrade( std::vector<std::string> Upgrade, std::vector<std::string> type_, CAssetManager* assetParam)
{
	asset = assetParam;
	xSize = (float)asset->sCREEN_WIDTH / 3.f;
	ySize = (float)asset->sCREEN_HEIGHT * 0.85f;
	pos.x = 0.f;
	pos.y = 0.f;

	type = type_;

	cardBack.setPosition(pos);
	cardBack.setFillColor(sf::Color::Black);
	cardBack.setSize(sf::Vector2f(xSize, ySize));
	int index;
	auto it = std::find(type.begin(), type.end(), "name");
	// If element was found 
	if (it != type.end())
	{
		// calculating the index 
		// of K 
		index = it - type.begin();
	}
	else
		throw(2);
	std::string title = Upgrade[index];
	Upgrade.erase(Upgrade.begin() + index);
	type.erase(type.begin() + index);
	cardTitle.setString(title);
	cardTitle.setFillColor(sf::Color::White);
	cardTitle.setFont(asset->GetFont("Lato"));
	cardTitle.setCharacterSize(75);
	cardTitle.setPosition(pos.x + (xSize - cardTitle.getGlobalBounds().width) / 2, pos.y);
	resizeText(cardTitle);
	auto iit = std::find(type.begin(), type.end(), "description");
	// If element was found 
	if (iit != type.end())
	{
		// calculating the index 
		// of K 
		index = iit - type.begin();
	}
	else
		throw(2);
	std::string description = Upgrade[index];
	Upgrade.erase(Upgrade.begin() + index);
	type.erase(type.begin() + index);
	cardDescription.setString(description);
	cardDescription.setFillColor(sf::Color::White);
	cardDescription.setFont(asset->GetFont("Lato"));
	cardDescription.setCharacterSize(35);
	cardDescription.setPosition(pos.x + (xSize - cardDescription.getGlobalBounds().width) / 2, pos.y + ySize * 0.8f);
	resizeText(cardDescription);
	for (int i = 0; i < type.size(); i++)
	{
		sf::Text temp;
		std::string tempString = type[i] + Upgrade[i];
		temp.setString(tempString);
		temp.setFillColor(sf::Color::White);
		temp.setFont(asset->GetFont("Lato"));
		temp.setCharacterSize(35);
		int posY = pos.y + ySize * 0.3f + (temp.getGlobalBounds().height*1.5 * (i + 1));
		temp.setPosition(pos.x + (xSize - temp.getGlobalBounds().width) / 2, pos.y + ySize * 0.4f);
		Stats.push_back(temp);
	}
}

void CCardUpgrade::setPosition(sf::Vector2f r)
{
	pos = r;
	cardBack.setPosition(pos);
	cardTitle.setPosition(pos.x + (xSize - cardTitle.getGlobalBounds().width) / 2, pos.y);
	for (int i = 0; i < Stats.size(); i++)
	{
		int posY = pos.y + ySize * 0.3f + ((Stats[i].getGlobalBounds().height * 1.5) * (i + 1));
		Stats[i].setPosition(pos.x + (xSize - Stats[i].getGlobalBounds().width) / 2, posY);
	}
	cardDescription.setPosition(pos.x + (xSize - cardDescription.getGlobalBounds().width) / 2, pos.y + ySize * 0.8f);
}

void CCardUpgrade::resizeText(sf::Text& textToResize)
{
	while(textToResize.getGlobalBounds().width >=
cardBack.getGlobalBounds().width - cardBack.getGlobalBounds().width * 0.05f &&
		  textToResize.getCharacterSize()>=20)
	{
		textToResize.setCharacterSize(textToResize.getCharacterSize() - 1);
	}
	int dividedIn =1;
	std::string basicString = textToResize.getString();
	while (textToResize.getGlobalBounds().width >= cardBack.getGlobalBounds().width - cardBack.getGlobalBounds().width * 0.05f)
	{
		dividedIn++;
		std::string temp = basicString;
		for (int i = 1; i < dividedIn; i++)
		{
			int R = (temp.size() / (float)(dividedIn))*i;
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

void CCardUpgrade::update(float deltaTime)
{
}

void CCardUpgrade::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(cardBack);
	target.draw(cardTitle);
	for (int i = 0; i < Stats.size(); i++)
	{
		target.draw(Stats[i]);
	}
	target.draw(cardDescription);
}
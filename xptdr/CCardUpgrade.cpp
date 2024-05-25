#include "CCardUpgrade.h"


CCardUpgrade::CCardUpgrade(int levelofEntity)
{
}

CCardUpgrade::CCardUpgrade( std::vector<std::string> Upgrade_, std::vector<std::string> type_, CAssetManager* assetParam)
{
	asset = assetParam;
	xSize = (float)asset->sCREEN_WIDTH / 3.f;
	ySize = (float)asset->sCREEN_HEIGHT * 0.85f;
	pos.x = 0.f;
	pos.y = 0.f;

	type = type_;
	Upgrade = Upgrade_;
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
		index = (int)(it - type.begin());
	}
	else
		throw(2);
	std::string title = Upgrade[index];
	Upgrade.erase(Upgrade.begin() + index);
	type.erase(type.begin() + index);
	cardTitle.setString(title);
	cardTitle.setFillColor(sf::Color::White);
	cardTitle.setFont(asset->GetFont("Nouvelle"));
	cardTitle.setCharacterSize(75);
	cardTitle.setPosition(pos.x + (xSize - cardTitle.getGlobalBounds().width) / 2, pos.y);
	resizeText(cardTitle);
	auto iit = std::find(type.begin(), type.end(), "description");
	// If element was found 
	if (iit != type.end())
	{
		// calculating the index 
		// of K 
		index = (int)(iit - type.begin());
	}
	else
		throw(2);
	std::string description = Upgrade[index];
	Upgrade.erase(Upgrade.begin() + index);
	type.erase(type.begin() + index);
	cardDescription.setString(description);
	cardDescription.setFillColor(sf::Color::White);
	cardDescription.setFont(asset->GetFont("Nouvelle"));
	cardDescription.setCharacterSize(35);
	cardDescription.setPosition(pos.x + (xSize - cardDescription.getGlobalBounds().width) / 2, pos.y + ySize * 0.8f);
	resizeText(cardDescription);
	int YSizepris = (int)(pos.y + ySize * 0.3f);
	int padding = 5;
	for (int i = 0; i < type.size(); i++)
	{
		if(Upgrade[i]!="")
		{
			sf::Text temp;
			std::string tempString = CCharacter::returnTypeStylish(type[i], Upgrade[i]) ;
			temp.setString(tempString);
			temp.setFillColor(sf::Color::White);
			temp.setFont(asset->GetFont("Nouvelle"));
			temp.setCharacterSize(35);
			int posY = (int)YSizepris+ padding+ (int)temp.getGlobalBounds().height*i ;
			temp.setPosition(pos.x + (xSize - temp.getGlobalBounds().width) / 2, (float)posY);
			Stats.push_back(temp);
		}
	}
}

CCardUpgrade::CCardUpgrade(std::string Upgrade_, std::string type_, CAssetManager* assetParam)
{
	asset = assetParam;
	xSize = (float)asset->sCREEN_WIDTH / 3.f;
	ySize = (float)asset->sCREEN_HEIGHT * 0.85f;
	pos.x = 0.f;
	pos.y = 0.f;

	cardBack.setPosition(pos);
	cardBack.setFillColor(sf::Color::Black);
	cardBack.setSize(sf::Vector2f(xSize, ySize));

	type.push_back(type_);
	Upgrade.push_back(Upgrade_);
	std::string title = type_;
	cardTitle.setString(title);
	cardTitle.setFillColor(sf::Color::White);
	cardTitle.setFont(asset->GetFont("Nouvelle"));
	cardTitle.setCharacterSize(75);
	cardTitle.setPosition(pos.x + (xSize - cardTitle.getGlobalBounds().width) / 2, pos.y);
	resizeText(cardTitle);
	cardDescription.setString(CCharacter::returnTypeStylish(type_, Upgrade_));
	cardDescription.setFillColor(sf::Color::White);
	cardDescription.setFont(asset->GetFont("Nouvelle"));
	cardDescription.setCharacterSize(35);
	cardDescription.setPosition(pos.x + (xSize - cardDescription.getGlobalBounds().width) / 2,
		pos.y + (ySize - cardDescription.getGlobalBounds().height) / 2);
}

void CCardUpgrade::setPosition(sf::Vector2f r)
{
	pos = r;
	cardBack.setPosition(pos);
	cardTitle.setPosition(pos.x + (xSize - cardTitle.getGlobalBounds().width) / 2, pos.y);
	/*int YSizepris = (int)(ySize * 0.2f);
	int padding = 5;
	for (int i = 0; i < Stats.size(); i++)
	{
		int posY = (int)pos.y + YSizepris;
		Stats[i].setPosition(pos.x + (xSize - Stats[i].getGlobalBounds().width) / 2.f, (float)posY);
		YSizepris += padding + (int)(Stats[i].getGlobalBounds().height);
	}
	*/
	fillSpace(Stats, sf::FloatRect(pos.x + xSize * 0.05f , pos.y + ySize * 0.2f, xSize * 0.95f, ySize * 0.6f));
	cardDescription.setPosition(pos.x + (xSize - cardDescription.getGlobalBounds().width) / 2, pos.y + ySize * 0.8f);
}


void CCardUpgrade::update(float deltaTime)
{
}

void CCardUpgrade::reduceScale()
{
	sf::Vector2f scale = cardBack.getScale();
	scale.x -= 0.1f; scale.y -= 0.1f;
	cardBack.setScale(scale);
	xSize = cardBack.getGlobalBounds().width+2*cardBack.getOutlineThickness();
	ySize = cardBack.getGlobalBounds().height + 2 * cardBack.getOutlineThickness();
	resizeTexts();
}

void CCardUpgrade::resizeTexts()
{//Pour replacer les textes, on va les placer selon la méthode fillSpace
	sf::Vector2f paddings(xSize * 0.02f, ySize * 0.02f);
	sf::FloatRect bord(pos.x, pos.y, xSize, ySize * 0.2f);
	//PLacer titre
	fillSpace(cardTitle, bord);
	cardTitle.setPosition(pos.x + (xSize - cardTitle.getGlobalBounds().width) / 2.f, pos.y);
	bord.top += ySize * 0.2f;
	bord.height = ySize * 0.4f;
	bord.left += paddings.x;
	bord.width = xSize - paddings.x;
	fillSpace(Stats, bord);
	//Placer description
	bord.top = ySize * 0.6f;
	fillSpace(cardDescription, bord);
}

void CCardUpgrade::fillSpace(std::vector<sf::Text>& texts, sf::FloatRect border)
{
	int nbText = (int)texts.size();
	if (nbText != 0)
	{
		for (int i = 0; i < nbText; i++)
			resizeText(texts[i],5,false);
		//Espace (en hauteur) pas pris par 
		float t = border.height - (texts[0].getGlobalBounds().height * nbText);
		while (t < 0.f)
		{
			for (int i = 0; i < nbText; i++)
				texts[i].setCharacterSize(texts[i].getCharacterSize() - 1);
		}
		if (t > 0.f)//C'est qu'on a la place de mettre les textes
		{
			for (int i = 0; i < nbText; i++)
			{
				sf::Vector2f posTemp;
				float spaceBetweenCard = t / (float)(nbText + 1);
				posTemp.x = border.left;
				posTemp.y = border.top+spaceBetweenCard + (spaceBetweenCard + texts[i].getGlobalBounds().height) * i;
				utilities::readaptText(texts[i], posTemp);
			}
		}
	}
}
/// <summary>
/// Cette méthode remplit le plus d'espace possible 
/// </summary>
/// <param name="text"></param>
/// <param name="border"></param>
void CCardUpgrade::fillSpace(sf::Text& text, sf::FloatRect border)
{
	while (text.getGlobalBounds().width > border.width)
	{
		resizeText(text,5,true);
	}
}

void CCardUpgrade::setSize(sf::Vector2f size)
{
	cardBack.setSize(size);
	xSize = size.x;
	ySize = size.y;
	resizeTexts();
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
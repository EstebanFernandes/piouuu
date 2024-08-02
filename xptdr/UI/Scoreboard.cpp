#include "Scoreboard.h"
#include <numeric>
void Scoreboard::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(scoreboardBack);
	for (int i = 0; i < textToDisplay.size(); i++) {
		for(int j =0;j<textToDisplay[i].size();j++){
			target.draw(textToDisplay[i][j]);
		}
	}
	std::cout << "draw le scoreboard\n";
}

Scoreboard::Scoreboard()
{
	boldRank = -1;
	asset = NULL;
	xSize = 0;
	ySize = 0;
}

Scoreboard::Scoreboard(AssetManager* assetParam, int boldRankParam)
	: Scoreboard()
{
	asset = assetParam;
	boldRank = boldRankParam;
	initText();
	setPos(0, 0);
	for (int i = 0; i < 4; i++)
		xSize += widthPerCol[i]+padding.x;
	ySize = (height + padding.y) * textToDisplay[0].size() + padding.y/2.f;
	scoreboardBack = sf::RectangleShape(sf::Vector2f(xSize, ySize));
	scoreboardBack.setPosition(0, 0);
	scoreboardBack.setFillColor(sf::Color(0, 0, 0, 100));
	scoreboardBack.setOutlineThickness(7);
	scoreboardBack.setOutlineColor(sf::Color::Black);	
}
//Deprecated
Scoreboard::Scoreboard(AssetManager* assetParam, float x, float y, int boldRankParam)
{
	boldRank = boldRankParam;
	asset = assetParam;
	initText();


	xSize = Engine::SCREEN_WIDTH * 0.7f;
	ySize = Engine::SCREEN_HEIGHT / 2.0f;

	scoreboardBack = sf::RectangleShape(sf::Vector2f(xSize,ySize));
	scoreboardBack.setPosition(x, y);
	scoreboardBack.setFillColor(sf::Color(174, 137, 100));
	scoreboardBack.setOutlineThickness(7);
	scoreboardBack.setOutlineColor(sf::Color(0,0,0,100));
}

void Scoreboard::setSize(float xSizeParam, float ySizeParam)
{
	xSize = xSizeParam;
	ySize = ySizeParam;
}

void Scoreboard::setPos(sf::Vector2f pos_)
{
	pos = pos_;
	scoreboardBack.setPosition(pos);
	
	sf::Vector2f posText;
	for (int i = 0; i < textToDisplay.size(); i++)
	{
		float plusWidth = 0;
		for (int a = 0; a < i; a++)
			plusWidth += widthPerCol[a]+padding.x;
		for (int j = 0; j < textToDisplay[i].size(); j++)
		{
			posText.x = pos.x + plusWidth+padding.x/2.f;
			posText.y = pos.y + (height+padding.y) * j+ padding.y / 2.f;
			utilities::readaptText(textToDisplay[i][j], posText);
		}
	}
}

void Scoreboard::setPosAuto()
{
	setPos((Engine::SCREEN_WIDTH - xSize) / 2.f,
		(Engine::SCREEN_HEIGHT*0.8f - ySize) / 2.f);
}

void Scoreboard::initText()
{
	std::vector<std::vector<std::string>> elements = IO::retrieveCSVFile("res/data/Scoreboard.csv");
	sf::Text texte;
	texte.setFillColor(sf::Color::White);
	texte.setFont(asset->GetFont("Nouvelle"));
	for (int i = 0; i < 4; i++)
		textToDisplay.push_back(std::vector<sf::Text>());
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < (int)elements.size() && j<10; j++) {
			switch (i)
			{
			case col::rank:
				texte.setString(std::to_string(j + 1));
				break;
			case col::aircraft :
				texte.setString(elements[j][1]);
				break;
			case col::name :
				texte.setString(elements[j][0]);
				break;
			case col::score :
				texte.setString(elements[j][2]);
					break;

			}
			textToDisplay[i].push_back(texte);
		}
	}
	if (boldRank > 10 && boldRank <= 100) {
		for (int j = 0; j < 4; j++)
		{
			switch (j)
			{
			case col::rank:
				texte.setString("..");
				break;
			case col::aircraft:
				texte.setString(".....");
				break;
			case col::name:
				texte.setString(".....");
				break;
			case col::score:
				texte.setString("....");
				break;

			}
			textToDisplay[j].push_back(texte);
		}
		for (int j = 0; j < 4; j++)
		{
			switch (j)
			{
			case col::rank:
				texte.setString(std::to_string(boldRank));
				break;
			case col::aircraft:
				texte.setString(elements[boldRank - 1][1]);
				break;
			case col::name:
				if(elements[boldRank - 1][1].find('&')==-1)//Si il y a un & c'est qu'on a deux joueurs
					texte.setString("Toi");
				else
					texte.setString("Vous");
				break;
			case col::score:
				texte.setString(elements[boldRank - 1][2]);
				break;

			}
			textToDisplay[j].push_back(texte);
		}
	}
	for (int i = 0; i < textToDisplay.size(); i++) {
		//Si i=11, alors il y a un score en plus des 10 premiers : on le mets en gras
			for(int j=0;j<textToDisplay[i].size();j++)
			{
					if (j == 11 || j == boldRank - 1) 
					{
						textToDisplay[i][j].setStyle(sf::Text::Italic);
						textToDisplay[i][j].setFillColor(sf::Color::Red);
					}
			}
			widthPerCol[i] = utilities::getMaxWidth(textToDisplay[i]);
			float tempHeight = utilities::getMaxHeight(textToDisplay[i]);
			if (tempHeight > height)
				height = tempHeight;
	}
}

float Scoreboard::getWidth()
{
	return scoreboardBack.getGlobalBounds().width;
}

float Scoreboard::getHeight()
{
	return scoreboardBack.getGlobalBounds().height;
}

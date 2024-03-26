#include "CScoreboard.h"
#include <numeric>
void CScoreboard::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(scoreboardBack);
	for (int i = 0; i < textToDisplay.size(); i++) {
		for(int j =0;j<textToDisplay[i].size();j++){
			target.draw(textToDisplay[i][j]);
		}
	}
}

CScoreboard::CScoreboard()
{
	boldRank = -1;
	asset = NULL;
	xSize = 0;
	ySize = 0;
}

CScoreboard::CScoreboard(CAssetManager* assetParam, int boldRankParam)
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
	scoreboardBack.setFillColor(sf::Color(174,137,100,190));
	scoreboardBack.setOutlineThickness(7);
	scoreboardBack.setOutlineColor(sf::Color::Black);	
}
//Deprecated
CScoreboard::CScoreboard(CAssetManager* assetParam, float x, float y, int boldRankParam)
{
	boldRank = boldRankParam;
	asset = assetParam;
	initText();


	xSize = asset->sCREEN_WIDTH * 0.7f;
	ySize = asset->sCREEN_HEIGHT / 2.0f;

	scoreboardBack = sf::RectangleShape(sf::Vector2f(xSize,ySize));
	scoreboardBack.setPosition(x, y);
	scoreboardBack.setFillColor(sf::Color(174, 137, 100));
	scoreboardBack.setOutlineThickness(7);
	scoreboardBack.setOutlineColor(sf::Color::Black);
}

void CScoreboard::setSize(float xSizeParam, float ySizeParam)
{
	xSize = xSizeParam;
	ySize = ySizeParam;
}

void CScoreboard::setPos(sf::Vector2f pos_)
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

void CScoreboard::setPosAuto()
{
	setPos((asset->sCREEN_WIDTH - xSize) / 2.f,
		(asset->sCREEN_HEIGHT*0.8f - ySize) / 2.f);
}

void CScoreboard::initText()
{
	CParserCSV parser = CParserCSV("res/data/Scoreboard.csv");
	std::vector<std::vector<std::string>> elements = parser.getElements();
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
		sf::Text texte;
			texte.setString(" ");
		for (int j = 0; j < 4; j++)
		{
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
				texte.setString(elements[boldRank - 1][0]);
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
				textToDisplay[i][j].setStyle(sf::Text::Bold);
			}
			widthPerCol[i] = utilities::getMaxWidth(textToDisplay[i]);
			float tempHeight = utilities::getMaxHeight(textToDisplay[i]);
			if (tempHeight > height)
				height = tempHeight;
	}
}

float CScoreboard::getWidth()
{
	return scoreboardBack.getGlobalBounds().width;
}

float CScoreboard::getHeight()
{
	return scoreboardBack.getGlobalBounds().height;
}

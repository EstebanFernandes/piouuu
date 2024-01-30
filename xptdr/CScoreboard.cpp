#include "CScoreboard.h"

void CScoreboard::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(scoreboardBack);
	for (int i = 0; i < textToDisplay.size(); i++) {
		target.draw(textToDisplay[i]);
	}
}

CScoreboard::CScoreboard()
{
	asset = NULL;
	xSize = 0;
	ySize = 0;
}

CScoreboard::CScoreboard(CAssetManager* assetParam, int boldRankParam)
{
	boldRank = boldRankParam;
	initText();

	asset = assetParam;


	xSize = asset->sCREEN_WIDTH *0.7f;
	ySize = asset->sCREEN_HEIGHT / 2.0f;

	scoreboardBack = sf::RectangleShape(sf::Vector2f(xSize, ySize));
	scoreboardBack.setPosition(0, 0);
	scoreboardBack.setFillColor(sf::Color(174,137,100));
	scoreboardBack.setOutlineThickness(7);
	scoreboardBack.setOutlineColor(sf::Color::Black);

	for (int i = 0; i < textToDisplay.size(); i++) {
		//Si i=11, alors il y a un score en plus des 10 premiers : on le mets en gras
		if (i == 11 || i == boldRank - 1) {
			textToDisplay[i].setStyle(sf::Text::Bold);
		}

		textToDisplay[i].setFillColor(sf::Color::White);
		textToDisplay[i].setFont(asset->GetFont("Lato"));
		//taille
		textToDisplay[i].setPosition(scoreboardBack.getPosition().x, scoreboardBack.getPosition().y * 0.9f + i * scoreboardBack.getGlobalBounds().height / (textToDisplay.size()+1));
	}
}

CScoreboard::CScoreboard(CAssetManager* assetParam, float x, float y, int boldRankParam)
{
	boldRank = boldRankParam;
	initText();
	asset = assetParam;


	xSize = asset->sCREEN_WIDTH * 0.7f;
	ySize = asset->sCREEN_HEIGHT / 2.0f;

	scoreboardBack = sf::RectangleShape(sf::Vector2f(xSize,ySize));
	scoreboardBack.setPosition(x, y);
	scoreboardBack.setFillColor(sf::Color(174, 137, 100));
	scoreboardBack.setOutlineThickness(7);
	scoreboardBack.setOutlineColor(sf::Color::Black);

	for (int i = 0; i < textToDisplay.size(); i++) {
		//Si i=11, alors il y a un score en plus des 10 premiers : on le mets en gras
		if (i == 11 || i == boldRank-1) {
			textToDisplay[i].setStyle(sf::Text::Bold);
		}

		textToDisplay[i].setFillColor(sf::Color::White);
		textToDisplay[i].setFont(asset->GetFont("Lato"));
		//taille
		textToDisplay[i].setPosition(scoreboardBack.getPosition().x, scoreboardBack.getPosition().y*0.9f + i * scoreboardBack.getGlobalBounds().height / (textToDisplay.size() + 1));
	}
	
}

void CScoreboard::setSize(float xSizeParam, float ySizeParam)
{
	xSize = xSizeParam;
	ySize = ySizeParam;
}

void CScoreboard::setPosAuto()
{
	pos = sf::Vector2f((asset->sCREEN_WIDTH - xSize) / 2, asset->sCREEN_HEIGHT * 0.1f);
	scoreboardBack.setPosition(pos);

	for (int i = 0; i < textToDisplay.size(); i++) {
		//taille
		textToDisplay[i].setPosition(scoreboardBack.getPosition().x, scoreboardBack.getPosition().y * 0.9f + i * scoreboardBack.getGlobalBounds().height / textToDisplay.size());
	}
}

void CScoreboard::initText()
{
	CParserCSV parser = CParserCSV("res/data/Scoreboard.csv");
	std::vector<std::vector<std::string>> elements = parser.getElements();

	sf::Text scorer = sf::Text();
	for (int i = 0; i < (int)elements.size() && i<10; i++) {
		scorer.setString(std::to_string(i + 1) + ". " + elements[i][0] +
			" : " + elements[i][2] + " points avec le " + elements[i][1] + "\n");
		textToDisplay.push_back(scorer);
	}
	if (boldRank > 10 && boldRank <= 100) {
		scorer.setString("...");
		textToDisplay.push_back(scorer);

		scorer.setString(std::to_string(boldRank) + ". " + "toi" +
			" : " + elements[boldRank-1][2] + " points avec le " + elements[boldRank-1][1] + "\n");
		textToDisplay.push_back(scorer);
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

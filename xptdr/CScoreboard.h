#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>
#include "CAssetManager.h"
#include "CParserCSV.h"
#include "utilities.h"
class CScoreboard : public sf::Drawable
{
private:

	enum col
	{
		rank,
		score,
		name,
		aircraft
	};
	CAssetManager* asset;
	int boldRank;
	float height = 0;
	float widthPerCol[4];
	sf::Vector2f padding = sf::Vector2f(40.f,10.f);
	sf::RectangleShape scoreboardBack;
	std::vector<sf::RectangleShape> ligne;
	sf::Vector2f pos;
	std::vector<std::vector<sf::Text>> textToDisplay;

	float xSize;
	float ySize;
public:
	CScoreboard();
	CScoreboard(CAssetManager* assetParam, int boldRank);
	CScoreboard(CAssetManager* assetParam, float x, float y, int boldRank);
	void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setSize(float xSizeParam, float ySizeParam);
	void setPos(float x, float y) {
		setPos(sf::Vector2f(x, y));
	}
	void setPos(sf::Vector2f pos);
	void setPosAuto();
	void initText();
	float getWidth();
	float getHeight();
};


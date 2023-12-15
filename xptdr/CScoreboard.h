#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>
#include "CAssetManager.h"
#include "CParserCSV.h"

class CScoreboard : public sf::Drawable
{
private:
	CAssetManager* asset;
	int boldRank;

	sf::RectangleShape scoreboardBack;
	sf::Vector2f pos;

	std::vector<sf::Text> textToDisplay;

	float xSize;
	float ySize;
public:
	CScoreboard();
	CScoreboard(CAssetManager* assetParam, int boldRank);
	CScoreboard(CAssetManager* assetParam, float x, float y, int boldRank);
	void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setSize(float xSizeParam, float ySizeParam);
	void setPosAuto();
	void initText();
	float getWidth();
	float getHeight();
};


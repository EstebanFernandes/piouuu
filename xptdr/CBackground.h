#pragma once
#include"CAssetManager.h"
#include<SFML/Graphics.hpp>

struct BGContainer {
	std::string name;
	sf::Sprite sprite;
	float speed;
	int type;
};
//Classe qui gère les fond de chaque map, il faut rentrer les couches de la dernière à la 1ere
class CBackground
{
private:
	CAssetManager* assets;
	sf::Vector2u windowSize;
	std::vector<BGContainer> allLayer;
	std::vector<BGContainer> layerCopies;
public:
	enum type{
		background,
		bot,
		top
	};
	CBackground(CAssetManager* a,sf::RenderWindow* w);
	CBackground();
	void addAndScaleLayer(std::string fileName, std::string name, float speed);
	void addLayer(std::string fileName,std::string name, float speed, int type);
	void addLayer(sf::Sprite sprite, std::string name, float speed, int type);
	bool deleteLayer(std::string name);
	void updateCBackground(float delta);
	void renderBackground(sf::RenderTarget& target);
	void setAssets(CAssetManager* a) { assets = a; }
	void setWindowSize(sf::Vector2u a) { windowSize = a; }
};


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
	std::vector<sf::Shader*> shaders;
	bool typeBG;//Si true c'est un background ingame, sinon c'est un bg de menu
	float* time;//Represente le temps
	sf::RectangleShape fond;
public:
	enum type{
		background,
		bot,
		top,
		basicBG //Spécial pour les menus de pause sélection de perso etc, contient deux shaders
	};
	CBackground(CAssetManager* a);
	CBackground();
	~CBackground();

	void addAndScaleLayer(std::string fileName, std::string name, float speed);
	void addLayer(std::string fileName,std::string name, float speed, int type);
	void addLayer(sf::Sprite sprite, std::string name, float speed, int type);
	bool deleteLayer(std::string name);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="TYPE">true = background ingame,
	/// false = background de menu</param>
	void initBackground(bool TYPE);
	void initBackground(CAssetManager* a,bool TYPE);
	void updateCBackground(float delta);
	void renderBackground(sf::RenderTarget& target);
	void setAssets(CAssetManager* a) {
		assets = a;
		windowSize = sf::Vector2u(assets->sCREEN_WIDTH, assets->sCREEN_HEIGHT);
	}
	void setWindowSize(sf::Vector2u a) 
	{ 
		windowSize = a;
		if (typeBG == false)//on est avec les shaders quoi
		{
			shaders[0]->setUniform("u_resolution", sf::Glsl::Vec2(windowSize));
			shaders[1]->setUniform("texture", sf::Shader::CurrentTexture);
			shaders[1]->setUniform("u_resolution", sf::Glsl::Vec2(windowSize));
			fond.setSize(sf::Vector2f(windowSize));
		}
	}
	void setTimePointer(float* time_) { time = time_; }
};


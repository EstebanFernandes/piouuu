#pragma once
#include"AssetManager.h"
#include<SFML/Graphics.hpp>
#include"Animation.h"
#include"../utilities.h"
namespace Engine {

struct BGContainer {
	std::string name;
	sf::Sprite sprite;
	sf::Vector2f direction;
	int type;
};
//Classe qui gère les fond de chaque map, il faut rentrer les couches de la dernière à la 1ere
class Background
{
private:
	AssetManager* assets;
	sf::Vector2u windowSize;
	std::vector<BGContainer> allLayer;
	std::vector<BGContainer> cloudLayers; //POur gérer les nuages
	std::vector<BGContainer> cloudLayersCopies; //POur gérer les nuages
	std::vector<BGContainer> layerCopies;
	std::vector<sf::Shader*> shaders;
	bool typeBG;//Si true c'est un background ingame, sinon c'est un bg de menu
	float* time;//Represente le temps
	sf::RectangleShape fond;
	bool hasCloud = false;
	sf::Clock cloudClocks;
	int cloudLayer = -1; //Indique la couche où l'on doit rendre les nuages
	float cloudTimer =0.5f;
public:
	enum type{
		backgroundtype,
		bot,
		top,
		clouds,
		sun,
		basicBG //Spécial pour les menus de pause sélection de perso etc, contient deux shaders
	};
	Background(AssetManager* a);
	Background();
	~Background();

	void addAndScaleLayer(std::string fileName, std::string name, float speed);
	void addLayer(std::string fileName,std::string name, float speed, int type);
	void addLayer(sf::Sprite sprite, std::string name, float speed, int type);
	void addClouds(std::string textureName, std::string name, float speed,Animation& anim);
	void initClouds();
	bool deleteLayer(std::string name);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="TYPE">true = background ingame,
	/// false = background de menu</param>
	void initBackground(bool TYPE);
	void initBackground(AssetManager* a,bool TYPE);
	void updateBackground(float delta);
	void renderBackground(sf::RenderTarget& target);
	void setAssets(AssetManager* a) {
		assets = a;
		windowSize = sf::Vector2u(Engine::SCREEN_WIDTH,Engine::SCREEN_HEIGHT);
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

	BGContainer& getLayer(std::string name)
	{
		for (int i = 0; i < allLayer.size(); i++)
		{
			if (allLayer[i].name == name)
				return allLayer[i];
		}
		BGContainer temp;
		temp.type = -1;
		return temp;
	}
	void drawEverythingButFirstLayer(sf::RenderTarget& target, float inter);
	void drawFirstLayer(sf::RenderTarget& target, float inter);
};

}
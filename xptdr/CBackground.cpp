#include "CBackground.h"
#include<iostream>
#include"utilities.h"
CBackground::CBackground(CAssetManager* a)
	:CBackground()
{
	assets = a;
	windowSize = sf::Vector2u(assets->sCREEN_WIDTH, assets->sCREEN_HEIGHT);
}



CBackground::CBackground()
{
	assets = NULL;
	time = NULL;
	typeBG = true;
}

CBackground::~CBackground()
{
	for (int i = 0; i < shaders.size(); i++)
	{
		delete shaders[i];
	}
	shaders.clear();
}



void CBackground::initBackground(bool TYPE)
{
	typeBG = TYPE;
	if (typeBG == false)
	{
		sf::Shader* first = new sf::Shader(); //Draw the zigzag
		sf::Shader* second = new sf::Shader();//Apply the blur
		if (!first->loadFromFile("shaders/vertexbandw.vert", "shaders/test.frag"))
			std::cout << "non non";
		first->setUniform("u_resolution", sf::Glsl::Vec2(windowSize));
		first->setUniform("angle",utilities::RandomFloat(0.f,360.f));
		if (!second->loadFromFile("shaders/vertexbandw.vert", "shaders/blurFrag.frag"))
			std::cout << "bof";
		second->setUniform("texture", sf::Shader::CurrentTexture);
		second->setUniform("u_resolution", sf::Glsl::Vec2(windowSize));
		shaders.push_back(first);
		shaders.push_back(second);
		fond.setSize(sf::Vector2f(windowSize));
		BGContainer render;
		allLayer.push_back(render);
	}

}
void CBackground::initBackground(CAssetManager* a, bool TYPE)
{
	setAssets(a);
	initBackground(TYPE);
}
void CBackground::addAndScaleLayer(std::string fileName, std::string name, float speed)
{
	sf::Vector2u TextureSize;  //Added to store texture size.
	sf::Vector2u WindowSize;   //Added to store window size.
	sf::Sprite t1;
	assets->LoadTexture(name,fileName);
	TextureSize = assets->GetTexture(name).getSize(); //Get size of texture.
	float ScaleX = (float)(windowSize.x * 1.1f) / TextureSize.x;
	float ScaleY = (float)windowSize.y / TextureSize.y;     //Calculate scale.
	t1.setTexture(assets->GetTexture(name));
	t1.setScale(ScaleX, ScaleY);      //Set scale. 
	addLayer(t1, name, speed, CBackground::background);
}

void CBackground::addLayer(std::string fileName, std::string name, float speed,int type)
{
	assets->LoadTexture(name, fileName);
	BGContainer temp;
	temp.sprite.setTexture(assets->GetTexture(name));
	temp.name = name;
	temp.speed = speed;
	temp.type = type;
	allLayer.push_back(temp);
	sf::Vector2f f = temp.sprite.getPosition();
	f.x += temp.sprite.getGlobalBounds().width;
	temp.sprite.setPosition(f);
	layerCopies.push_back(temp);
}

void CBackground::addLayer(sf::Sprite sprite, std::string name, float speed, int type)
{
	BGContainer temp;
	temp.sprite = sprite;
	temp.name = name;
	temp.speed = speed;
	allLayer.push_back(temp);
	sf::Vector2f f = temp.sprite.getPosition();
	f.x += temp.sprite.getGlobalBounds().width;
	temp.sprite.setPosition(f);
	layerCopies.push_back(temp);
}

bool CBackground::deleteLayer(std::string name)
{
	for (int i = 0; i < allLayer.size(); i++)
	{
		if(allLayer[i].name.compare(name))
		{
			allLayer.erase(allLayer.begin() + i);
			layerCopies.erase(allLayer.begin() + i);
			return true;
		}
	}
	return false;
}


void CBackground::updateCBackground(float delta)
{
	if (typeBG == false)
	{
		float currentTime = *time;
		shaders[0]->setUniform("u_time", currentTime);
	}
	else {
		for (int i = 0; i < allLayer.size(); i++)
		{
			sf::FloatRect sprite1Pos = allLayer[i].sprite.getGlobalBounds();
			sf::FloatRect sprite2Pos = layerCopies[i].sprite.getGlobalBounds();
			if (sprite1Pos.left + sprite1Pos.width <= 0)
				allLayer[i].sprite.setPosition(sprite2Pos.left + sprite2Pos.width, sprite1Pos.top);
			if (sprite2Pos.left + sprite2Pos.width <= 0)
				layerCopies[i].sprite.setPosition(sprite1Pos.left + sprite1Pos.width, sprite2Pos.top);
			allLayer[i].sprite.move(sf::Vector2f(-allLayer[i].speed, 0));
			layerCopies[i].sprite.move(sf::Vector2f(-layerCopies[i].speed, 0));
		}
	}
}

void CBackground::renderBackground(sf::RenderTarget& target)
{
	if (typeBG == false)
	{
		sf::RenderTexture back;
		back.create(windowSize.x, windowSize.y);
		back.clear();
		back.draw(fond, shaders[0]);
		back.display();
		allLayer[0].sprite = sf::Sprite(back.getTexture());
		target.draw(allLayer[0].sprite, shaders[1]);
	}
	else
	{
		for (int i = 0; i < allLayer.size(); i++)
		{
			target.draw(allLayer[i].sprite);
			target.draw(layerCopies[i].sprite);
		}
	}
}

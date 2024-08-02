#include "Background.h"
#include<iostream>
Engine::Background::Background(AssetManager* a)
	:Background()
{
	assets = a;
	windowSize = sf::Vector2u(Engine::SCREEN_WIDTH,Engine::SCREEN_HEIGHT);
}



Engine::Background::Background()
{
	assets = NULL;
	time = NULL;
	typeBG = true;
}

Engine::Background::~Background()
{
	for (int i = 0; i < shaders.size(); i++)
	{
		delete shaders[i];
	}
	shaders.clear();
}



void Engine::Background::initBackground(bool TYPE)
{
	typeBG = TYPE;
	if (typeBG == false)
	{
		sf::Shader* first = new sf::Shader(); //Draw the zigzag
		sf::Shader* second = new sf::Shader();//Apply the blur
		if (!first->loadFromFile( "shaders/test.frag",  sf::Shader::Fragment))
			std::cout << "non non";
		first->setUniform("u_resolution", sf::Glsl::Vec2(windowSize));
		first->setUniform("angle",utilities::RandomFloat(0.f,360.f));
		if (!second->loadFromFile( "shaders/blurFrag.frag",sf::Shader::Fragment))
			std::cout << "bof";
		second->setUniform("textureSampler", sf::Shader::CurrentTexture);
		second->setUniform("u_resolution", sf::Glsl::Vec2(windowSize));
		shaders.push_back(first);
		shaders.push_back(second);
		fond.setSize(sf::Vector2f(windowSize));
		BGContainer render;
		allLayer.push_back(render);
	}

}
void Engine::Background::initBackground(AssetManager* a, bool TYPE)
{
	setAssets(a);
	initBackground(TYPE);
}
void Engine::Background::addAndScaleLayer(std::string fileName, std::string name, float speed)
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
	addLayer(t1, name, speed, Background::backgroundtype);
}

void Engine::Background::addLayer(std::string fileName, std::string name, float speed,int type)
{
	assets->LoadTexture(name, fileName);
	BGContainer temp;
	temp.sprite.setTexture(assets->GetTexture(name));
	temp.name = name;
	temp.direction = sf::Vector2f(-speed, 0.f);
	temp.type = type;
	allLayer.push_back(temp);
	sf::Vector2f f = temp.sprite.getPosition();
	f.x += temp.sprite.getGlobalBounds().width;
	temp.sprite.setPosition(f);
	layerCopies.push_back(temp);
}

void Engine::Background::addLayer(sf::Sprite sprite, std::string name, float speed, int type)
{
	BGContainer temp;
	temp.sprite = sprite;
	temp.name = name;
	temp.direction = sf::Vector2f(-speed,0.f);
	temp.type = type;
	allLayer.push_back(temp);
		sf::Vector2f f = temp.sprite.getPosition();
		f.x += temp.sprite.getGlobalBounds().width;
		temp.sprite.setPosition(f);
		layerCopies.push_back(temp);
	
}

void Engine::Background::addClouds(std::string textureName, std::string name, float speed, Animation& anim)
{
	sf::Texture& textureCloud = assets->GetTexture(textureName);
	for (int i = 0; i < anim.getMaxFrame().y; i++)
	{
		anim.setDifferentAnimation(i);
		BGContainer temp;
		temp.direction = sf::Vector2f(speed, 0.f);
		temp.sprite.setTexture(textureCloud);
		temp.sprite.setTextureRect((*anim.getCurrentFrame()));
		temp.sprite.setScale(5.f, 5.f);
		temp.type = i;
		temp.name = name;
		cloudLayersCopies.push_back(temp);
	}
	cloudLayer = (int)allLayer.size();
	hasCloud = true;
	initClouds();
	cloudClocks.restart();
}

void Engine::Background::initClouds()
{
	int nbAjouter = 15;
	for (int i = 0; i < nbAjouter; i++)
	{
		BGContainer temp;
		int randomNuage = rand() % cloudLayersCopies.size();
		if (cloudLayers.size() != 0)
		{
			while (randomNuage == cloudLayers.back().type)
				randomNuage = rand() % cloudLayersCopies.size();
		}
		temp = cloudLayersCopies.at(randomNuage);
		if (rand() % 2 + 1 == 1)
			utilities::flipSprite(temp.sprite);

		sf::Vector2f Position = sf::Vector2f(utilities::RandomFloat(0.f, (float)Engine::SCREEN_WIDTH),utilities::RandomFloat(0.f, (float)Engine::SCREEN_HEIGHT * 0.5f));
		temp.sprite.setPosition(Position);
		cloudLayers.push_back(temp);
	}
}

bool Engine::Background::deleteLayer(std::string name)
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


void Engine::Background::updateBackground(float delta)
{
	if (typeBG == false)
	{
		float currentTime = *time;
		shaders[0]->setUniform("u_time", currentTime);
	}
	else {
		if (hasCloud) //UPdate pour les nuages
		{
			for (auto it = cloudLayers.begin();it!=cloudLayers.end();)
			{
				sf::Sprite& currentCloud = it->sprite;
				if (currentCloud.getGlobalBounds().left >= (float)Engine::SCREEN_WIDTH)
					it = cloudLayers.erase(it);
				else
				{
					currentCloud.move(it->direction);
					it++;
				}
			}
			if(cloudLayers.size() <= cloudLayersCopies.size() / 1.25 || cloudClocks.getElapsedTime().asSeconds() >=cloudTimer)
			{
				int nbMax = (int)((float)cloudLayersCopies.size()/1.5),nbAjouter=0;
				if (nbMax > 1)
					nbAjouter = rand() % nbMax + 1;//On ajout un nombre random de nuage
				else
					nbAjouter = nbMax;
				for (int i = 0; i < nbAjouter; i++)
				{
					BGContainer temp;
					int randomNuage = rand() % cloudLayersCopies.size();
					if(cloudLayers.size()!=0)
					{
						while (randomNuage == cloudLayers.back().type)
							randomNuage = rand() % cloudLayersCopies.size();
					}
					temp = cloudLayersCopies.at(randomNuage);
					if (rand() % 2 + 1 == 1)
						utilities::flipSprite(temp.sprite);

					float yPosition = utilities::RandomFloat(0.f, (float)Engine::SCREEN_HEIGHT * 0.5f);
					temp.sprite.setPosition(sf::Vector2f(-temp.sprite.getGlobalBounds().width, yPosition));
					cloudLayers.push_back(temp);
				}
				cloudTimer = utilities::RandomFloat(1.f, 1.5f);
				cloudClocks.restart();
			}
		}
		for (int i = 0; i < allLayer.size(); i++)
		{
			sf::FloatRect sprite1Pos = allLayer[i].sprite.getGlobalBounds();
			sf::FloatRect sprite2Pos = layerCopies[i].sprite.getGlobalBounds();
			if (sprite1Pos.left + sprite1Pos.width <= 0)
				allLayer[i].sprite.setPosition(sprite2Pos.left + sprite2Pos.width, sprite1Pos.top);
			if (sprite2Pos.left + sprite2Pos.width <= 0)
				layerCopies[i].sprite.setPosition(sprite1Pos.left + sprite1Pos.width, sprite2Pos.top);
			allLayer[i].sprite.move(allLayer[i].direction);
			layerCopies[i].sprite.move(layerCopies[i].direction);
		}
	}
}

void Engine::Background::renderBackground(sf::RenderTarget& target)
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
	{//Op�rateur ternaire, on attribue la premi�re valeur si la condition est vraie, la deuxi�me sinon
		int nbLayer = (hasCloud) ? (int)allLayer.size() + 1 : (int)allLayer.size();
		for (int i = 0; i < nbLayer; i++)
		{
			if(hasCloud&&cloudLayer==i)
				for (int j = 0;j<cloudLayers.size();j++)
					target.draw(cloudLayers[j].sprite);
			else if(i>cloudLayer)
			{
				target.draw(allLayer[i-1].sprite);
				if(allLayer[i-1].type!=sun)
				target.draw(layerCopies[i-1].sprite);
			}
			else
			{
				target.draw(allLayer[i ].sprite);
				if (allLayer[i ].type != sun)
				target.draw(layerCopies[i ].sprite);
			}
		}
	}
}

void Engine::Background::drawEverythingButFirstLayer(sf::RenderTarget& target, float inter)
{
	int nbLayer = (hasCloud) ? (int)allLayer.size() + 1 : (int)allLayer.size();
	for (int i = 2; i < nbLayer; i++)
	{
		if (hasCloud && cloudLayer == i)
			for (int j = 0; j < cloudLayers.size(); j++)
				target.draw(cloudLayers[j].sprite);
		else if (i > cloudLayer)
		{
			target.draw(allLayer[i - 1].sprite);
			if (allLayer[i - 1].type != sun)
				target.draw(layerCopies[i - 1].sprite);
		}
		else
		{
			target.draw(allLayer[i].sprite);
			if (allLayer[i].type != sun)
				target.draw(layerCopies[i].sprite);
		}
	}
}

void Engine::Background::drawFirstLayer(sf::RenderTarget& target, float inter)
{
		target.draw(allLayer[0].sprite);
		if (allLayer[0].type != sun)
			target.draw(layerCopies[0].sprite);
		target.draw(allLayer[1].sprite);
		
}
#include "CBackground.h"

CBackground::CBackground(CAssetManager* a, sf::RenderWindow* w)
{
	assets = a;
}

CBackground::CBackground()
{
	assets = NULL;
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

void CBackground::renderBackground(sf::RenderTarget& target)
{
	for (int i = 0; i < allLayer.size(); i++)
	{
		target.draw(allLayer[i].sprite);
		target.draw(layerCopies[i].sprite);
	}
}

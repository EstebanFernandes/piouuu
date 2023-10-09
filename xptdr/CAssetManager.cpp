#include "CAssetManager.h"

void CAssetManager::LoadTexture(std::string name, std::string fileName)
{
	sf::Texture tex;
	if (tex.loadFromFile(fileName)) {
		Textures[name] = tex;
	}
}

void CAssetManager::LoadTexture(std::string name, sf::Texture tex)
{
	Textures[name] = tex;
}

sf::Texture& CAssetManager::GetTexture(std::string name)
{
	return Textures.at(name);
}

void CAssetManager::LoadFont(std::string name, std::string fileName)
{
	sf::Font font;
	if (font.loadFromFile(fileName)) {
		Fonts[name] = font;
	}
}

sf::Font& CAssetManager::GetFont(std::string name)
{
	return Fonts.at(name);
}



#pragma once
#include <map>
#include <SFML/Graphics.hpp>
class CAssetManager
{

private:
	std::map<std::string, sf::Texture> Textures;
	std::map<std::string, sf::Font> Fonts;
public:
	//Constructeurs et destructeurs
	CAssetManager() {};
	~CAssetManager() {};
	//Méthodes :
	void LoadTexture(std::string name, std::string fileName);
	void LoadTexture(std::string name, sf::Texture tex);
	sf::Texture& GetTexture(std::string name);
	void LoadFont(std::string name, std::string fileName);
	sf::Font& GetFont(std::string name);
	void DeleteTexture(std::string name) {
		Textures.erase(name);
	}

};


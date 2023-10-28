#pragma once
#include <map>
#include <SFML/Graphics.hpp>
//La classe assetmanager est partag� par toutes les entit�s qui doivent avoir des sprites, donc c'est �galement ici que l'on met la taille de l'�cran
class CAssetManager
{

private:
	std::map<std::string, sf::Texture> Textures;
	std::map<std::string, sf::Font> Fonts;
public:
	// Oui les deux attributs sont en public, force � nous la moindre erreur dans le code l'�cran ressemble plus � rien
	int sCREEN_WIDTH= 1280;
	int sCREEN_HEIGHT = 720;
	//Constructeurs et destructeurs
	CAssetManager() {};
	~CAssetManager() {};
	//M�thodes :
	void LoadTexture(std::string name, std::string fileName);
	void LoadTexture(std::string name, sf::Texture tex);
	sf::Texture& GetTexture(std::string name);
	void LoadFont(std::string name, std::string fileName);
	sf::Font& GetFont(std::string name);
	void DeleteTexture(std::string name) {
		Textures.erase(name);
	}
	//Cette m�thode permet de changer de fullscren � pas fullscreen, 
	//on passe en param�tre la fen�tre et le bool�en isFullScreen
	void changeScreenType(sf::RenderWindow & R, bool& isFullScreen);
};


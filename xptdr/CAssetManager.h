#pragma once
#include <map>
#include <SFML/Graphics.hpp>
//La classe assetmanager est partagé par toutes les entités qui doivent avoir des sprites, donc c'est également ici que l'on met la taille de l'écran
class CAssetManager
{

private:
	std::map<std::string, sf::Texture> Textures;
	std::map<std::string, sf::Font> Fonts;
public:
	// Oui les deux attributs sont en public, force à nous la moindre erreur dans le code l'écran ressemble plus à rien
	int sCREEN_WIDTH= 1280;
	int sCREEN_HEIGHT = 720;
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
	//Cette méthode permet de changer de fullscren à pas fullscreen, 
	//on passe en paramètre la fenêtre et le booléen isFullScreen
	void changeScreenType(sf::RenderWindow & R, bool& isFullScreen);
};


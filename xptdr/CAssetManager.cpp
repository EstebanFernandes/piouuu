#include "CAssetManager.h"
#include <iostream>


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

void CAssetManager::deleteEverythingBut(std::string name)
{
	auto itt = Textures.find(name);
	if (itt != Textures.end())
	{
		for (auto it = Textures.cbegin(); it != Textures.cend() /* not hoisted */; /* no increment */)
		{
			if (name!=it->first)
			{
				Textures.erase(it++);    // or "it = m.erase(it)" since C++11
			}
			else
			{
				++it;
			}
		}
	}
}

void CAssetManager::deleteEverythingBut(std::vector<std::string>& names)
{

		for (auto it = Textures.cbegin(); it != Textures.cend() /* not hoisted */; /* no increment */)
		{
			bool hasToDelete = true;
			for (int i = 0; i<names.size(); i++)
			{
				if (names[i] == it->first)
				{
					hasToDelete = false;
					break;
				}
			}
			if (hasToDelete)
			{
				Textures.erase(it++);    // or "it = m.erase(it)" since C++11
			}
			else
			{
				++it;
			}
		}
}

void CAssetManager::LoadSFX(std::string name, std::string fileName)
{
	sonManager.stockSound(name, fileName);
}

void CAssetManager::addSFX(std::string name,sf::Sound** son)
{
	return sonManager.addSound(name,son);
}

void CAssetManager::InitialiserMusiques(float volumeMusic,float volumeSon)
{
	musiqueManager.ajouterMusique("MenuPrincipal", "res\\sfx\\ecran_titre.wav");
	sf::Music::TimeSpan ts;
	ts.offset = sf::milliseconds(25600);
	ts.length = sf::milliseconds(505181);
	musiqueManager.getMusique("MenuPrincipal")->setLoopPoints(ts);
	musiqueManager.ajouterMusique("PartieJour", "res\\sfx\\Partie_de_jour.mp3");
	setOverAllvolumeMusique(volumeMusic);
	setOverAllvolumeSon(volumeSon);
}

void CAssetManager::changeScreenType(sf::RenderWindow& window, bool& isFullScreen)
{
	if (!isFullScreen)
	{
		//Borderless Fullscreen
		isFullScreen = true;
		sCREEN_WIDTH = 1920;
		sCREEN_HEIGHT = 1080;
		window.create(sf::VideoMode(sCREEN_WIDTH, sCREEN_HEIGHT), "PIOU PIOU", sf::Style::None);
	}
	else
	{
		//Surtout pour nous
		isFullScreen = false;
		sCREEN_WIDTH = 1280;
		sCREEN_HEIGHT = 720;
		window.create(sf::VideoMode(sCREEN_WIDTH, sCREEN_HEIGHT),"PIOU PIOU", sf::Style::Close | sf::Style::Titlebar);
	}
	window.setFramerateLimit(60);
}

void CAssetManager::checkSound()
{
	//sonManager.checkVect();
}



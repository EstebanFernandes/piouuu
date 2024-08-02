#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include "Musique.h"
#include"Effetsonore.h"
#include"Animation.h"
//Namespace qui contient toutes les classes et m�thodes qui concernent le moteur
namespace Engine {

	extern int SCREEN_HEIGHT;
	extern int SCREEN_WIDTH;

	sf::Vector2i getEcranBound();
#define TRANSI_TIME 1.25f
struct image {//Struct qui encapsule ce qu'on a besoin pour g�rer un sprite 
	sf::Sprite sprite;
	Animation anim;
	bool isAnimated = false;
};
//La classe assetmanager est partag� par toutes les entit�s qui doivent avoir des sprites, donc c'est �galement ici que l'on met la taille de l'�cran

class AssetManager
{

private:
	std::map<std::string, sf::Texture> Textures;
	std::map<std::string, sf::Font> Fonts;
	EffetSonore sonManager;
	Musique musiqueManager;
	float fxVolume = 100.f;
public:
	//Constructeurs et destructeurs
	AssetManager() {};
	~AssetManager() {};
	//M�thodes :

	void LoadTexture(std::string name, std::string fileName);
	void LoadTexture(std::string name, sf::Texture tex);
	sf::Texture& GetTexture(std::string name);
	void LoadFont(std::string name, std::string fileName);
	sf::Font& GetFont(std::string name);
	void DeleteTexture(std::string name) {
		Textures.erase(name);
	}
	/// <summary>
	/// Delete tous les assets de texture qui ne correspondent pas � ce qui est pass� en param�tre
	/// </summary>
	/// <param name="name"></param>
	void deleteEverythingBut(std::string name);
	void deleteEverythingBut(std::vector<std::string>& names);
	/// <summary>
	/// Load va charger dans une map le buffer du son
	/// </summary>
	/// <param name="name"></param>
	/// <param name="fileName"></param>
	void LoadSFX(std::string name, std::string fileName);
	/// <summary>
	
	/// <summary>
	/// Cela va parametrer le sound pass� en param�tre et l'ajouter dans un vector de pointer de son pour qu'on puisse r�gler le volume overall
	/// </summary>
	/// <param name="name"></param>
	/// <param name="son"></param>
	void addSFX(std::string name, sf::Sound** son);
	void DeleteSFX(std::string name) {
		//SoundFX.erase(name);
	}
	//M�thodes pour g�rer la musique
	void InitialiserMusiques(float volumeMusic, float volumeSon);

	void jouerMusique(const std::string& id) {
		musiqueManager.jouerMusique(id);
	}

	void pauseMusique(const std::string& id) {
		musiqueManager.pauseMusique(id);
	}

	void reprendreMusique(const std::string& id) {
		musiqueManager.resumeMusique(id);
	}

	void stopMusique(const std::string& id) {
		musiqueManager.stopMusique(id);
	}

	void volumeSon(sf::Sound* son, float volume) {
		sonManager.setSonVolume(son, volume);
	}

	void volumeMusique(const std::string& id, float volume) {
		musiqueManager.volumeMusique(id, volume);
	}
	void setOverAllvolumeSon(float volume) {
		sonManager.overAllVolume(volume);
	}
	void setOverAllvolumeMusique(float volume) {
		musiqueManager.overAllVolume(volume);
	}
	//Cette m�thode permet de changer de fullscreen � pas fullscreen, 
	//on passe en param�tre la fen�tre et le bool�en isFullScreen
	void changeScreenType(sf::RenderWindow & R, bool& isFullScreen);
	void checkSound();
	void deleteSound(sf::Sound* a) { sonManager.deleteSound(a); }
	void clearSoundBuffer() { sonManager.clearSoundBuffer(); }
};

}
using Engine::AssetManager;
using Engine::image;
using Engine::SCREEN_HEIGHT;
using Engine::SCREEN_WIDTH;
using Engine::getEcranBound;
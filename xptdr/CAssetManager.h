#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include "Cmusique.h"
#include"Ceffetsonore.h"
//La classe assetmanager est partagé par toutes les entités qui doivent avoir des sprites, donc c'est également ici que l'on met la taille de l'écran

class CAssetManager
{

private:
	std::map<std::string, sf::Texture> Textures;
	std::map<std::string, sf::Font> Fonts;
	CeffetSonore sonManager;
	Cmusique musiqueManager;
	float fxVolume = 100.f;
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

	void deleteEverythingBut(std::string name);
	/// <summary>
	/// Load va charger dans une map le buffer du son
	/// </summary>
	/// <param name="name"></param>
	/// <param name="fileName"></param>
	void LoadSFX(std::string name, std::string fileName);
	/// <summary>
	
	/// <summary>
	/// Cela va parametrer le sound passé en paramètre et l'ajouter dans un vector de pointer de son pour qu'on puisse régler le volume overall
	/// </summary>
	/// <param name="name"></param>
	/// <param name="son"></param>
	void addSFX(std::string name, sf::Sound* son);
	void DeleteSFX(std::string name) {
		//SoundFX.erase(name);
	}
	//Méthodes pour gérer la musique
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

	void volumeMusique(const std::string& id, float volume) {
		musiqueManager.volumeMusique(id, volume);
	}
	void setOverAllvolumeSon(float volume) {
		sonManager.overAllVolume(volume);
	}
	void setOverAllvolumeMusique(float volume) {
		musiqueManager.overAllVolume(volume);
	}
	//Cette méthode permet de changer de fullscren à pas fullscreen, 
	//on passe en paramètre la fenêtre et le booléen isFullScreen
	void changeScreenType(sf::RenderWindow & R, bool& isFullScreen);
	void checkSound();
	void deleteSound(sf::Sound* a) { sonManager.deleteSound(a); }
	void clearSoundBuffer() { sonManager.clearSoundBuffer(); }
};


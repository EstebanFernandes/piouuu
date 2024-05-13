#pragma once
#include <vector>
#include <string>
#include "CTransition.h"
#include"CBackground.h"
#include"inputPlayer.h"
//Classe virtuelle qu'on doit hériter pour construire une scène, on redéfinit les méthodes init (appelés en premier),
//update( appelé pour update la scène (faire bouger les personnages par exemple))
//HandleInput où on peut gérer les inputs et ce que l'on fait avec
//Et draw qui sert à afficher sur l'écran (on doit toujours commencer par window.clear et finir par window.display)
class CState
{
protected:
	
	//Liste qui contient les texture que l'on doit charger 
	std::vector<std::pair<std::string, std::string>> assetToload;
	/// <summary>
	/// Méthode qui regarde l'extension du nom du fichier ->pair.second
	/// </summary>
	/// <param name="paire"></param>
	inline void load(CAssetManager* asset, std::pair<std::string, std::string> paire) {
		std::string extensionfile = paire.second.substr(paire.second.find_last_of('.'));
		if (extensionfile == ".wav")
			asset->LoadSFX(paire.first, paire.second);
		else
			asset->LoadTexture(paire.first, paire.second);
	}
	/// <summary>
	/// ajoute un asset au vecteur des assets à load
	/// </summary>
	/// <param name="name"></param>
	/// <param name="filepath"></param>
	inline void addAsset(std::string name, std::string filepath) {
		assetToload.push_back(std::pair<std::string, std::string>(name, filepath));
	}

	sf::Clock clock;//Clock on the currentstate
	static float time; 
	virtual void updateTime();
	static sf::Clock globalClock;
	static CBackground background;

	static inputPlayer inputOfPlayers[2];
public:
	static float angleOffset;
	virtual ~CState();
	//La transition est un objet static commun à tous les états, comme ça on le passe d'état en état (génie de ma part imo)
	static CTransition currentTransi;
	bool hasChanges = false;
	bool needDisplay = true;
	//Méthodes :
	virtual void STEInit() = 0;
	virtual void STEHandleInput() = 0;
	virtual void STEUpdate(float delta) = 0;
	//on doit juste clear et draw dans ces fonctions, le display est réalisé dans la boucle principale
	virtual void STEDraw(float delta) = 0; // différence entre les frames
	virtual void STEPause() {};
	virtual void STEResume() {};
	//Méthode appelé une fois la transac effectué ;)
	virtual void afterTransi() {};
	virtual void drawOnTarget(sf::RenderTarget& target,float interpolation){}
};


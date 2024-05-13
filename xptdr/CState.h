#pragma once
#include <vector>
#include <string>
#include "CTransition.h"
#include"CBackground.h"
#include"inputPlayer.h"
//Classe virtuelle qu'on doit h�riter pour construire une sc�ne, on red�finit les m�thodes init (appel�s en premier),
//update( appel� pour update la sc�ne (faire bouger les personnages par exemple))
//HandleInput o� on peut g�rer les inputs et ce que l'on fait avec
//Et draw qui sert � afficher sur l'�cran (on doit toujours commencer par window.clear et finir par window.display)
class CState
{
protected:
	
	//Liste qui contient les texture que l'on doit charger 
	std::vector<std::pair<std::string, std::string>> assetToload;
	/// <summary>
	/// M�thode qui regarde l'extension du nom du fichier ->pair.second
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
	/// ajoute un asset au vecteur des assets � load
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
	//La transition est un objet static commun � tous les �tats, comme �a on le passe d'�tat en �tat (g�nie de ma part imo)
	static CTransition currentTransi;
	bool hasChanges = false;
	bool needDisplay = true;
	//M�thodes :
	virtual void STEInit() = 0;
	virtual void STEHandleInput() = 0;
	virtual void STEUpdate(float delta) = 0;
	//on doit juste clear et draw dans ces fonctions, le display est r�alis� dans la boucle principale
	virtual void STEDraw(float delta) = 0; // diff�rence entre les frames
	virtual void STEPause() {};
	virtual void STEResume() {};
	//M�thode appel� une fois la transac effectu� ;)
	virtual void afterTransi() {};
	virtual void drawOnTarget(sf::RenderTarget& target,float interpolation){}
};


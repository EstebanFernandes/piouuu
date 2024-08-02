#pragma once
#include <vector>
#include <string>
#include "../Engine/Transition.h"
#include"../Engine/Background.h"
#include"../Engine/InputPlayer.h"
#include "imgui/imgui.h"
#include "imgui-sfml/imgui-SFML.h"

 namespace StateNS {

using Engine::AssetManager;
using Engine::Transition;
using Engine::SENS_TRANSITION;
using Engine::Background;
	//Classe virtuelle qu'on doit hériter pour construire une scène, on redéfinit les méthodes init (appelés en premier),
	//update( appelé pour update la scène (faire bouger les personnages par exemple))
	//HandleInput où on peut gérer les inputs et ce que l'on fait avec
	//Et draw qui sert à afficher sur l'écran 
	class State
	{
	protected:
		//Liste qui contient les texture que l'on doit charger on met d'abord le nom puis le filepath
		std::vector<std::pair<std::string, std::string>> assetToload;
		/// <summary>
		/// Méthode qui regarde l'extension du nom du fichier ->pair.second
		/// </summary>
		/// <param name="paire"></param>
		inline void load(AssetManager* asset, std::pair<std::string, std::string> paire) {
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
		static Background background;

		static InputPlayer inputOfPlayers[2];

		//IMGUI

		bool useIMGUI = false;
		//Fonction a overload pour update la fenêtre IMGUI
		//Pour moi on a besoin que d'une fenetre vu que c'est juste pour afficher des infos/modifier des valeurs
		virtual void debugInfo() {}

	public:
		virtual void updateIMGUI(sf::RenderWindow& window,float dt);
		static float angleOffset;
		virtual ~State();
		//La transition est un objet static commun à tous les états, comme ça on le passe d'état en état (génie de ma part imo)
		static Transition currentTransi;
		bool hasChanges = false;
		bool needDisplay = true;
		//Méthodes :
		virtual void STEInit() = 0;
		virtual void STEHandleInput(sf::Event& event) = 0;
		void HandleInput(sf::RenderWindow& window)
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				STEHandleInput(event);
				if (useIMGUI)
					ImGui::SFML::ProcessEvent(window,event);
			}
		}

		virtual void STEUpdate(float delta) = 0;
		//on doit juste clear et draw dans ces fonctions, le display est réalisé dans la boucle principale
		virtual void STEDraw(float delta) = 0; // différence entre les frames
		virtual void STEPause() {};
		virtual void STEResume() {};
		//Méthode appelé une fois la transac effectué ;)
		virtual void afterTransi() {};
		virtual void drawOnTarget(sf::RenderTarget& target,float interpolation){}
		bool getImguiBoolean() { return useIMGUI; }
	};

}
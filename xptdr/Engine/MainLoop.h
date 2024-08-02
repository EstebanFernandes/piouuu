#pragma once
#include"AssetManager.h"
#include"InputManager.h"
#include "StateMachine.h"
#include <memory>
#include <string>
namespace Engine {
	struct GameData {
		StateMachine machine;
		sf::RenderWindow window;
		AssetManager assets;
		InputManager inputs;
		bool isFullScreen = false;
	};

	typedef std::shared_ptr<GameData> GameDataRef;
	class MainLoop
	{
	private :
		GameDataRef data = std::make_shared<GameData>();
	//Attributs
		unsigned int fps = 60;
		const float dt = 1.0f / fps;
		static int screenWidth;
		static int screenHeight;
		sf::Clock JEUClock;

	public:
	//Constructeur
		MainLoop(int width, int height, std::string title);
	//Méthodes
		void JEURun();
	};

}
//Lorsqu'on include ce fichier voici les deux attributs que l'on récupère, c'est pour ne pas avoir à réécrire partout using Engine::GameDataRef et using Engine::StateRef
//Obliger de le mettre ici sinon le compilateur ne le reconnait pas
using Engine::StateRef;
using Engine::GameDataRef;
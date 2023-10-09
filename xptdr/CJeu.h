#pragma once
#include"CAssetManager.h"
#include"CInputManager.h"
#include "CStateMachine.h"
#include <memory>
#include <string>
struct GameData {
	CStateMachine machine;
	sf::RenderWindow window;
	CAssetManager assets;
	CInputManager inputs;
	bool isFullScreen = false;
};

typedef std::shared_ptr<GameData> GameDataRef;
class CJeu
{
private :
	GameDataRef data = std::make_shared<GameData>();
//Attributs
	unsigned int fps = 60;
	const float dt = 1.0f / fps;
	sf::Clock JEUClock;
public:
//Constructeur
	CJeu(int width, int height, std::string title);
//Méthodes
	void JEURun();
};


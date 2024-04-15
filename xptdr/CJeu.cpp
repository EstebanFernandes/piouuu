#include "CJeu.h"
#include "CSplashState.h"
CJeu::CJeu(int width, int height, std::string title)
{
	CParserCSV parser = CParserCSV("res/data/settings.csv");
	std::vector<std::vector<std::string>> retrieveInfo = parser.getElements();
	float volumeMusic = std::stof(retrieveInfo[0][1]);
	float volumeSound = std::stof(retrieveInfo[1][1]);
	if (std::stoi(retrieveInfo[2][1])) 
		data->assets.changeScreenType(data->window, data->isFullScreen);
	else
		data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
	sf::Texture icon;
	icon.loadFromFile("res/img/logo icon WIP.png");
	data->window.setIcon(16, 16, icon.copyToImage().getPixelsPtr());
	data->machine.AddState(StateRef(new CSplashState(data)));
	data->assets.InitialiserMusiques(volumeMusic,volumeSound); // Initialiser les musiques
	JEURun();
}

void CJeu::JEURun()
{

	data->window.setFramerateLimit(fps);
	float newTime, frameTime, interpolation;
	float currentTime = JEUClock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;
	bool& transiInIt = CState::currentTransi.transiouuuuu;//permet de savoir l'�tat actuel de la transition
	while (data->window.isOpen())
	{
		if (transiInIt == false)
			data->machine.ProcessStateChanges();
		else if (CState::currentTransi.updateTransition(0.f))
		{
			data->machine.GetActiveState()->afterTransi();
		}
		StateRef& currentState = data->machine.GetActiveState();
		newTime = JEUClock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;
		if (frameTime < 0.25f) frameTime = 0.25f;
		currentTime = newTime;
		accumulator += frameTime;
		while (accumulator >= dt)
		{
			if (currentState->hasChanges == true)
				break;
			if(transiInIt==false)
			{
				currentState->STEHandleInput();
				currentState->STEUpdate(dt);
			}
			accumulator -= dt;
		}
		if(!currentState->hasChanges||transiInIt==true)
		{
			interpolation = accumulator / dt;
			data->machine.GetActiveState()->STEDraw(interpolation);
			if (transiInIt == true)
				CState::currentTransi.renderTransition(data->window);
			data->window.display();
		}
	}
}

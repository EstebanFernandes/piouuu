#include "../Engine/MainLoop.h"
#include "../State/SplashState.h"
#include "../IO/ParserCSV.h"
Engine::MainLoop::MainLoop(int width, int height, std::string title)
{
	std::vector<std::vector<std::string>> retrieveInfo = IO::retrieveCSVFile("res/data/settings.csv");
	float volumeMusic = std::stof(retrieveInfo[0][1]);
	float volumeSound = std::stof(retrieveInfo[1][1]);
	if (std::stoi(retrieveInfo[2][1])) 
		data->assets.changeScreenType(data->window, data->isFullScreen);
	else
	{
		sf::ContextSettings settings;
		settings.antialiasingLevel = 8;
		data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar,settings);
	}
	sf::Texture icon;
	icon.loadFromFile("res/img/logo icon WIP.png");
	data->window.setIcon(16, 16, icon.copyToImage().getPixelsPtr());
	data->machine.AddState(StateRef(new StateNS::SplashState(data)));
	data->assets.InitialiserMusiques(volumeMusic,volumeSound); // Initialiser les musiques
	JEURun();
}

void Engine::MainLoop::JEURun()
{
	ImGui::SFML::Init(data->window);
	data->window.setFramerateLimit(fps);
	float newTime, frameTime, interpolation;
	float currentTime = JEUClock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;
	bool& transiInIt = State::currentTransi.transiouuuuu;//permet de savoir l'état actuel de la transition
	while (data->window.isOpen())
	{
		if (transiInIt == false)
			data->machine.ProcessStateChanges();
		else if (State::currentTransi.updateTransition(0.f))
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
				currentState->HandleInput(data->window);
				currentState->STEUpdate(dt);
				
			}
			accumulator -= dt;
		}
		if(!currentState->hasChanges||transiInIt==true)
		{
				if (currentState->getImguiBoolean())
					currentState->updateIMGUI(data->window, dt);
			interpolation = accumulator / dt;
			data->window.clear();
			data->machine.GetActiveState()->STEDraw(interpolation);
			if (currentState->getImguiBoolean())
				ImGui::SFML::Render(data->window);
			if (transiInIt == true)
				State::currentTransi.renderTransition(data->window);
			if(currentState->needDisplay)
			{
				data->window.display();
			}
		}
	}
	ImGui::SFML::Shutdown();
}

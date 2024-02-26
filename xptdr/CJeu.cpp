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
	while (data->window.isOpen())
	{
		data->machine.ProcessStateChanges();

		newTime = JEUClock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;
		if (frameTime < 0.25f) frameTime = 0.25f;
		currentTime = newTime;
		accumulator += frameTime;
		while (accumulator >= dt)
		{
			data->machine.GetActiveState()->STEHandleInput();
 			data->machine.GetActiveState()->STEUpdate(dt);
			accumulator -= dt;
		}

		interpolation = accumulator / dt;
		data->machine.GetActiveState()->STEDraw(interpolation);
		/*std::cout << "dt : " << dt << std::endl
			<< "interpolation : " <<interpolation << std::endl
			<< "frametime : " << frameTime << std::endl;*/
	}
}

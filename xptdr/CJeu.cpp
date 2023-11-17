#include "CJeu.h"
#include "CSplashState.h"
CJeu::CJeu(int width, int height, std::string title)
{
	data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
	data->machine.AddState(StateRef(new CSplashState(data)));
	JEURun();
}

void CJeu::JEURun()
{

	data->window.setFramerateLimit(fps);
	srand(static_cast<unsigned int>(time(nullptr)));
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

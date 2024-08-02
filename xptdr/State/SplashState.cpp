#include "SplashState.h"
StateNS::SplashState::SplashState(GameDataRef _data) : data(_data)
{
}

void StateNS::SplashState::STEInit()
{
	std::cout << data->window.getSettings().majorVersion <<"majeur mineur" << data->window.getSettings().minorVersion;
	globalClock.restart();
	background.initBackground(&(data->assets), false);
	background.setTimePointer(&time);
	data->assets.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
	CSSBackground.setTexture(data->assets.GetTexture("Splash State Background"));
	sf::Vector2f targetSize((float)Engine::SCREEN_WIDTH, (float)Engine::SCREEN_HEIGHT);

	CSSBackground.setScale(
		targetSize.x / CSSBackground.getLocalBounds().width,
		targetSize.y / CSSBackground.getLocalBounds().height);
}

void StateNS::SplashState::STEHandleInput(sf::Event& event)
{
	if (sf::Event::Closed == event.type)	
		data->window.close();
}

void StateNS::SplashState::STEUpdate(float delta)
{
	if ((int)CSSClock.getElapsedTime().asSeconds() >= SPLASH_STATE_SHOW_TIME && !CESTBON) {
		// Switch to the main menu
		data->machine.RemoveState();
		data->machine.AddState(StateRef (new MainMenuState(data)), false);
		CESTBON = true;
	}
}

void StateNS::SplashState::STEDraw(float delta)
{
	data->window.draw(CSSBackground);
}

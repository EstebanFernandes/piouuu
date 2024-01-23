#include "CSplashState.h"
CSplashState::CSplashState(GameDataRef _data) : data(_data)
{
}

void CSplashState::STEInit()
{
	data->assets.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
	CSSBackground.setTexture(data->assets.GetTexture("Splash State Background"));
	sf::Vector2f targetSize(data->assets.sCREEN_WIDTH, data->assets.sCREEN_HEIGHT);

	CSSBackground.setScale(
		targetSize.x / CSSBackground.getLocalBounds().width,
		targetSize.y / CSSBackground.getLocalBounds().height);

}

void CSplashState::STEHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)	data->window.close();
	}
}

void CSplashState::STEUpdate(float delta)
{
	if ((int)CSSClock.getElapsedTime().asSeconds() == SPLASH_STATE_SHOW_TIME && !CESTBON) {
		// Switch to the main menu
		data->machine.RemoveState();
		data->machine.AddState(StateRef (new CMainMenuState(data)), false);
		CESTBON = true;
	}
}

void CSplashState::STEDraw(float delta)
{
	data->window.clear(sf::Color::Red);
	data->window.draw(CSSBackground);
	data->window.display();
}

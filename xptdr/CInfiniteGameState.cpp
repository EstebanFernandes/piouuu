#include "CInfiniteGameState.h"

CInfiniteGameState::CInfiniteGameState(GameDataRef _data) 
{
	data = _data;
}

void CInfiniteGameState::STEHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
			data->window.close();
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
		{
			if (!data->isFullScreen)
			{
				data->isFullScreen = true;
				data->window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "ihih", sf::Style::Fullscreen);
			}
			else
			{
				data->isFullScreen = false;
				data->window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "title", sf::Style::Close | sf::Style::Titlebar);
			}
		}if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::Escape)
			{
				sf::Texture texture;
				texture.create(SCREEN_WIDTH, SCREEN_HEIGHT);
				texture.update(data->window);
				data->assets.LoadTexture("pauseScreen", texture);
				gameTime += gameClock.getElapsedTime();
				data->machine.AddState(StateRef(new CGameMenu(data)), false);
			}
		}
	}
}

void CInfiniteGameState::STEUpdate(float delta)
{
	while(enemyNumber < 2 + (1 * player1.getLevel()))
	{
		addEnemy();
	}
	CGameState::STEUpdate(delta);
	if (player1.needDelete == true)
	{
		GameOver();
	}
}

void CInfiniteGameState::STEDraw(float delta)
{
	CGameState::STEDraw(delta);
}

void CInfiniteGameState::GameOver()
{
	data->machine.AddState(StateRef(new CGameOver<CInfiniteGameState>(data)), true);
}

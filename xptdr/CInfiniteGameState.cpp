#include "CInfiniteGameState.h"

CInfiniteGameState::CInfiniteGameState(GameDataRef _data) 
{
	data = _data;
}

CInfiniteGameState::CInfiniteGameState(GameDataRef _data, CCharacter characterParam)
{
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
			data->assets.changeScreenType(data->window, data->isFullScreen);
		}if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::Escape)
			{
				sf::Texture texture;
				texture.create(data->assets.sCREEN_WIDTH, data->assets.sCREEN_HEIGHT);
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

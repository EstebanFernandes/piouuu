#include "CTestGame.h"

CTestGame::CTestGame(GameDataRef _data)
{
	setData(_data);
}

void CTestGame::STEInit()
{
	CGameState::STEInit();
	data->assets.LoadTexture("lifePowerUp", "C:\\Users\\scizz\\Pictures\\VROUM\\lifepowerup\\lifePowerUp.png");
}

void CTestGame::STEHandleInput()
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
			if (event.key.code == sf::Keyboard::Space)
			{
				player1.reduceHP(player1.getMaxHealth());
				GameOver();
			}
			if (event.key.code == sf::Keyboard::A)
			{
				addEnemy();
			}
			if (event.key.code == sf::Keyboard::T)
			{
				addPowerUp();
			}
		}
	}

}

void CTestGame::STEUpdate(float delta)
{
	CGameState::STEUpdate(delta);
}

void CTestGame::addPowerUp()
{
	entityList.push_back(new CPowerUp(&(data->assets)));
}

void CTestGame::STEDraw(float delta)
{
	CGameState::STEDraw(delta);

}

void CTestGame::GameOver()
{
	data->machine.AddState(StateRef(new CGameOver<CTestGame>(data)), true);
}

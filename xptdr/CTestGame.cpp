#include "CTestGame.h"
#include"CUpgradeState.h"
CTestGame::CTestGame(GameDataRef _data)
{
	setData(_data);
}

CTestGame::CTestGame(GameDataRef _data, CCharacter characterParam)
{
	setData(_data);
	player1.updateStates(characterParam);
}

void CTestGame::STEInit()
{
	CGameState::STEInit();
	data->assets.LoadTexture("lifePowerUp", "res\\img\\lifePowerUp.png");
}

void CTestGame::STEHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{
		player1.PLYupdateMovement(event);
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
			if (event.key.code == sf::Keyboard::Space)
			{
				player1.gainXP(100);
				//GameOver();
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
	if (currentLevelOfplayer < player1.getLevel())
	{
		currentLevelOfplayer = player1.getLevel();
		data->machine.AddState(StateRef(new CUpgradeState(data,&player1,&Upgradegraphs)), false);
	}
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
	data->machine.AddState(StateRef(new CGameOver<CTestGame>(data, player1)), true);
}

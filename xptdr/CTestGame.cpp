#include "CTestGame.h"
#include"CUpgradeState.h"
#include<math.h>
CTestGame::CTestGame(GameDataRef _data)
{
	setData(_data);
}

CTestGame::CTestGame(GameDataRef _data, CCharacter characterParam)
{
	setData(_data);
	player1.updateStates(characterParam);
	player1.updateMisc();
}

void CTestGame::STEInit()
{
	CGameState::STEInit();
	initAssets();
}

void CTestGame::initAssets()
{
	data->assets.LoadTexture("lifePowerUp", "res\\img\\lifePowerUp.png");
	data->assets.LoadTexture("enemyImage", ENEMYPNG_FILEPATH);
	data->assets.LoadTexture("explosion", "res\\img\\explosion_sprite_sheet.png");
	data->assets.LoadTexture("bulletImage", "res\\img\\bulletImage.png");
	data->assets.LoadTexture("bulletImageRancoeur", "res\\img\\bullet_Rancoeur.png");
	data->assets.LoadTexture("bombe", "res\\img\\bombe.png");
	data->assets.LoadTexture("boss", "res\\img\\spacecraft_player_1.png");
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
				data->machine.AddState(StateRef(new CGameMenu(data)), false);
			}
			if (event.key.code == sf::Keyboard::Space)
			{
				player1.gainXP(100);
			}
			if (event.key.code == sf::Keyboard::A)
			{
				addEnemy("roaming");
			}
			if (event.key.code == sf::Keyboard::E)
			{
				addEnemy("shooter");
			}
			if (event.key.code == sf::Keyboard::B)
			{
				addEnemy("boss");
			}
			if (event.key.code == sf::Keyboard::K)
			{
				addEnemy("bomber");
			}
			if (event.key.code == sf::Keyboard::L)
			{
				addEnemy("bomberInverse");
			}
			if (event.key.code == sf::Keyboard::J)
			{
				addEnemy("rusher");
			}
			if (event.key.code == sf::Keyboard::T)
			{
				player1.BAW.setPenetration(2);
			}
			if (event.key.code == sf::Keyboard::R)

			{
				player1.BAW.setPenetration(0);
			}
			//TEMP C POUR MOURIR
			if (event.key.code == sf::Keyboard::M)
			{
				player1.reduceHP(player1.getMaxHealth());
				//GameOver();
			}
		}
	}

}


void CTestGame::STEUpdate(float delta)
{
	updateBackground(delta);
	//Auto aim
	CMob* nearEnemy = NULL;
	sf::Vector2f lessDir(1920.f,1080.f);
	//On check d'abord les collisions entre le joueur et les entités. ensuite on update
	player1.updateEntity(delta);
	size_t temp = entityList.size();
	//Si c'est un AutoAim
	if (player1.BAW.typeBalle != 1)
	{
		for (int i = 0; i < temp; i++)
		{
			entityList[i]->updatewPlayer(delta, player1);
			if (entityList[i]->needDelete == true)
			{
				deleteEntity(i);
				temp--;
			}
			else
			{
				entityList[i]->updateEntity(delta);
				if (entityList[i]->getType() == 1&& entityList[i]->isDead==false)
				{
					sf::Vector2f dirTemp = entityList[i]->getDistance(player1);
					float un = (float)std::sqrt(pow(lessDir.x, 2) + pow(lessDir.y, 2));
					float deux = (float)std::sqrt(pow(dirTemp.x, 2) + pow(dirTemp.y, 2));
					if (un > deux)
					{
						lessDir = dirTemp;
						nearEnemy = entityList[i];
					}
				}
			}
		}
		if (player1.seekForTarget == true && nearEnemy!=NULL)
		{
				player1.BAW.changeTarget(nearEnemy);
			player1.seekForTarget = false;
		}
	}
	else {
		for (int i = 0; i < temp; i++)
		{
			entityList[i]->updatewPlayer(delta, player1);
			if (entityList[i]->needDelete == true)
			{
				deleteEntity(i);
				temp--;
			}
			else
				entityList[i]->updateEntity(delta);
		}
	}
	if (player1.needDelete)
		GameOver();

	//Information / Clock updates
	sf::Vector2f tempw = player1.getSprite().getPosition();
	std::stringstream ss;
	ss << "Player level : " << player1.getLevel() << std::endl <<
		"XP : " << player1.getXp() << std::endl <<
		"Max xp : " << player1.getMaxXp() << "\n" <<
		"Score : " << player1.getScore() << std::endl <<
		"Bullet number : " << player1.BAW.getVector()->size() << "\n";
	uitext.setString(ss.str());
	float clock = (gameTime.asSeconds() + gameClock.getElapsedTime().asSeconds() )* 100.f;
	clock = ceil(clock);
	clock = clock / 100.f;
	std::string i = std::to_string(clock);
	size_t r = i.find('.') + 3;
	i.erase(r, i.size() - r);
	size_t ti = gameClockText.getString().getSize();
	gameClockText.setString(i);
	if (ti != i.size())
		gameClockText.setPosition(sf::Vector2f(data->assets.sCREEN_WIDTH / 2 - gameClockText.getGlobalBounds().width / 2, 20.f));





	//Condition qui assure que le joueur prend bien un niveau par un niveau
 	if(player1.hasLevelUp ==true&& currentLevelOfplayer!=player1.getLevel())
	{
		currentLevelOfplayer++;
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
	if (isThistheEnd == false)
	{
		isThistheEnd = true;
	data->machine.AddState(StateRef(new CGameOver<CTestGame>(data, player1, player1.getScore())), true);
	}
}

void CTestGame::STEResume()
{
	data->assets.DeleteTexture("pauseScreen");
	gameClock.restart();
	CESTBON = false;
	player1.resetMovement();
	player1.updateMisc();
	if (player1.hasLevelUp == true && currentLevelOfplayer == player1.getLevel())
		player1.hasLevelUp = false;
}

void CTestGame::STEPause()
{
	gameTime += gameClock.getElapsedTime();
}

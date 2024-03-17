#include "CTestGame.h"
#include"CUpgradeState.h"
#include<math.h>
#include"dot.h"
CTestGame::CTestGame(GameDataRef _data)
{
	setData(_data);
}

CTestGame::CTestGame(GameDataRef _data, CCharacter characterParam)
{
	setData(_data);
	player1.updateStates(characterParam);
	player2.updateStates(characterParam);
}

void CTestGame::STEInit()
{
	initAssets();
	CGameState::STEInit();
	player2.setAssets(&(data->assets));
	player2.updateMisc();
	player2.upKey = sf::Keyboard::Up;
	player2.downKey = sf::Keyboard::Down;
	player2.leftKey = sf::Keyboard::Left;
	player2.rightKey = sf::Keyboard::Right;
	player2.getMainWeapon()->setTouche(sf::Keyboard::U);
	player2.getSecondaryWeapon()->setTouche(sf::Keyboard::J);
	player2.dashKey = sf::Keyboard::I;
}

void CTestGame::initAssets()
{
	data->assets.deleteEverythingBut(player1.getName());
	data->assets.clearSoundBuffer();
	data->assets.LoadTexture("lifepoint", LIFEPOINTTEXTURE);
	data->assets.LoadTexture("bomber", "res\\img\\lance-bombe.png");
	data->assets.LoadTexture("lifePowerUp", "res\\img\\lifePowerUp.png");
	data->assets.LoadTexture("enemyImage", ENEMYPNG_FILEPATH);
	data->assets.LoadTexture("explosion", "res\\img\\explosion_sprite_sheet.png");
	data->assets.LoadTexture("bulletSecond", "res\\img\\characters\\bullet_Second.png");
	data->assets.LoadTexture("bulletImage", "res\\img\\bulletImage.png");
	data->assets.LoadTexture("bulletImageRancoeur", "res\\img\\characters\\bulletRancoeur.png");
	data->assets.LoadTexture("bombe", "res\\img\\bombe.png");
	data->assets.LoadTexture("boss", "res\\img\\spacecraft_player_1.png");
	data->assets.LoadTexture("beginLaser", "res\\img\\laser\\beginLaser.png");
	data->assets.LoadTexture("fullLaser", "res\\img\\laser\\fullLaser.png");
	data->assets.GetTexture("fullLaser").setRepeated(true);
	data->assets.LoadTexture("R2D2", "res\\img\\characters\\Droide2.png");
	data->assets.LoadTexture("shooter", "res\\img\\ennemies\\shooter.png");
	data->assets.LoadTexture("bulletTear", "res\\img\\ennemies\\bulletTear.png");
	data->assets.LoadSFX("bulletSound", "res\\sfx\\Piou.wav");
	data->assets.LoadSFX("enemyRush", "res\\sfx\\vaisseau_fonce.wav");
	
}

void CTestGame::STEHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{
		player1.PLYupdateMovement(event);
		player2.PLYupdateMovement(event);
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
				player1.gainXP(5);
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
			if (event.key.code == sf::Keyboard::H)
			{
				addEnemy("pantin");
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
				player1.AAA();
			
			}
			if (event.key.code == sf::Keyboard::Tab)
				player1.debugh();
			//TEMP C POUR MOURIR
			if (event.key.code == sf::Keyboard::M)
			{
				player1.reduceHP(player1.getMaxHealth());
				//GameOver();
			}
		}
	}

}



void CTestGame::addPowerUp()
{
	entityList.push_back(new CPowerUp(&(data->assets)));
}


void CTestGame::GameOver()
{
	if (isThistheEnd == false)
	{
		isThistheEnd = true;
	data->machine.AddState(StateRef(new CGameOver<CTestGame>(data, player1, player1.getScore())), true);
	}
}

void CTestGame::STEUpdate(float delta)
{
	updateBackground(delta);
	//Auto aim
	//On check d'abord les collisions entre le joueur et les entités. ensuite on update
	player1.updateEntity(delta);
	player2.updateEntity(delta);
	if (player1.getMainWeapon()->typeTir == typeAim::autoAim && player1.seekForTarget)
	{
		CMob* cible = nearEnemy(&player1);
			player1.getMainWeapon()->changeTarget(cible);
			player1.seekForTarget = false;
	}
	if (player2.getMainWeapon()->typeTir == typeAim::autoAim && player2.seekForTarget)
	{
		CMob* cible = nearEnemy(&player2);
		player2.getMainWeapon()->changeTarget(cible);
		player2.seekForTarget = false;
	}
	size_t temp = entityList.size();
	int previousMax = (int)temp;
	for (int i = 0; i < temp; i++)
	{
		entityList[i]->updatewPlayer(delta, player1);
		entityList[i]->updatewPlayer(delta, player2);
		if (entityList[i]->needDelete == true)
		{
			deleteEntity(i);
			temp--;
		}
		else
			entityList[i]->updateEntity(delta);
	}
	if (player1.needDelete && player2.needDelete)
		GameOver();

	if (previousMax != temp)
	{
		data->assets.checkSound();
	}
	//Clock updates
	clock = (gameTime.asSeconds() + gameClock.getElapsedTime().asSeconds()) * 100.f;
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
	if (player1.hasLevelUp == true && currentLevelOfplayer != player1.getLevel())
	{
		currentLevelOfplayer++;
		data->machine.AddState(StateRef(new CUpgradeState(data, &player1, &Upgradegraphs)), false);
	}
	
	//DEBUG INFO
	std::stringstream ss;
	ss << "Player level : " << player1.getLevel() << std::endl <<
		"mouse x pos : " << sf::Mouse::getPosition(data->window).x << " y position : "<< sf::Mouse::getPosition(data->window).y << std::endl <<
		"Max xp : " << player1.getMaxXp() << "\n" <<
		"Score : " << player1.getScore() << std::endl << "\n";
	//"Bullet number : " << player1.BAW.getVector()->size() << "\n";
	uitext.setString(ss.str());
}

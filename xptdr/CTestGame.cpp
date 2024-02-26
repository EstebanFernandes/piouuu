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
}

void CTestGame::STEInit()
{
	initAssets();
	CGameState::STEInit();
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
	data->assets.LoadTexture("bulletImage", "res\\img\\bulletImage.png");
	data->assets.LoadTexture("bulletImageRancoeur", "res\\img\\bullet_Rancoeur.png");
	data->assets.LoadTexture("bombe", "res\\img\\bombe.png");
	data->assets.LoadTexture("boss", "res\\img\\spacecraft_player_1.png");
	data->assets.LoadSFX("bulletSound", "res\\sfx\\Piou.wav");
	data->assets.LoadSFX("enemyRush", "res\\sfx\\vaisseau_fonce.wav");
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
				player1.gainXP(20);
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
				//player1.addBuff(new dot(&player1,1.f,0.5f,4.f), true);
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
	CGameState::STEUpdate(delta);
	std::stringstream ss;
	ss << "Player level : " << player1.getLevel() << std::endl <<
		"mouse x pos : " << sf::Mouse::getPosition(data->window).x << " y position : "<< sf::Mouse::getPosition(data->window).y << std::endl <<
		"Max xp : " << player1.getMaxXp() << "\n" <<
		"Score : " << player1.getScore() << std::endl << "\n";
	//"Bullet number : " << player1.BAW.getVector()->size() << "\n";
	uitext.setString(ss.str());
}

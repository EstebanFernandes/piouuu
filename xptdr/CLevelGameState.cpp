#include "CLevelGameState.h"


void CLevelGameState::GameOver()
{
	if (isThistheEnd == false)
	{
		isThistheEnd = true;
		data->machine.AddState(StateRef(new CGameOver<CLevelGameState>(data, player1, player1.getScore())), true);
	}
}

void CLevelGameState::STEResume()
{
	data->assets.DeleteTexture("pauseScreen");
	gameClock.restart();
	CESTBON = false;
	player1.resetMovement();
}



void CLevelGameState::deleteEntity(int& i)
{
	if (entityList[i]->getType() == 1)
	{
		level.deleteEnemy(entityList[i]);
	}
	CGameState::deleteEntity(i);
}

CLevelGameState::CLevelGameState(GameDataRef _data)
{
	setData(_data);
}

CLevelGameState::CLevelGameState(GameDataRef _data, CCharacter characterParam, std::string filePath)
: CLevelGameState(_data){
	levelFilePath = filePath;
	player1.updateStates(characterParam);
	player1.updateMisc();
}

void CLevelGameState::STEInit()
{
	initAssets();
	CGameState::STEInit();


	CParserXML xml(levelFilePath, &(data->assets), &player1, &bulletstorage);
	xml.coreFunction();
	level = xml.getLevel();
	level.setEnnemyList(&entityList);
	level.setClock(&clock);
	level.isInfinite = true;
	level.startLevel();
}

void CLevelGameState::STEUpdate(float delta)
{
	if(isThistheEnd == false)
	{
		updateBackground(delta);
		//Auto aim
		CMob* nearEnemy = NULL;
		sf::Vector2f lessDir(1920.f, 1080.f);
		//On check d'abord les collisions entre le joueur et les entités. ensuite on update
		player1.updateEntity(delta);
		size_t temp = entityList.size();
		int previousMax = (int)temp;
		//Si c'est un AutoAim
		if (player1.getMainWeapon()->typeTir == typeAim::autoAim)
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
					if (entityList[i]->getType() == 1 && entityList[i]->isDead == false)
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
			if (player1.seekForTarget == true && nearEnemy != NULL)
			{
				player1.getMainWeapon()->changeTarget(nearEnemy);
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

		if (previousMax != temp)
		{
			data->assets.checkSound();
		}
		//Information / Clock updates
		sf::Vector2f tempw = player1.getSprite().getPosition();
		std::stringstream ss;
		ss << "Player level : " << player1.getLevel() << std::endl <<
			"XP : " << player1.getXp() << std::endl <<
			"Max xp : " << player1.getMaxXp() << "\n" <<
			"Score : " << player1.getScore() << std::endl << "\n";
		//"Bullet number : " << player1.BAW.getVector()->size() << "\n";
		uitext.setString(ss.str());
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
		if (level.updateLevel())
			GameOver();
	}
}

void CLevelGameState::initAssets()
{
	data->assets.deleteEverythingBut(player1.getName());
	data->assets.clearSoundBuffer();
	data->assets.LoadTexture("lifepoint", LIFEPOINTTEXTURE);
	data->assets.LoadTexture("bomber", "res\\img\\lance-bombe.png");
	data->assets.LoadTexture("lifePowerUp", "res\\img\\lifePowerUp.png");
	data->assets.LoadTexture("enemyImage", ENEMYPNG_FILEPATH);
	data->assets.LoadTexture("bulletSecond", "res\\img\\characters\\bullet_Second.png");
	data->assets.LoadTexture("explosion", "res\\img\\explosion_sprite_sheet.png");
	data->assets.LoadTexture("bulletImage", "res\\img\\characters\\bulletImage.png");
	data->assets.LoadTexture("bulletImageRancoeur", "res\\img\\bullet_Rancoeur.png");
	data->assets.LoadTexture("bulletImageGolden", "res\\img\\bullet_Golden.png");
	data->assets.LoadTexture("bombe", "res\\img\\bombe.png");
	data->assets.LoadTexture("boss", "res\\img\\spacecraft_player_1.png");
	data->assets.LoadSFX("bulletSound", "res\\sfx\\Piou.wav");
	data->assets.LoadSFX("enemyRush", "res\\sfx\\vaisseau_fonce.wav");
}
#include "CLevelGameState.h"


void CLevelGameState::GameOver()
{
	if (isThistheEnd == false)
	{
		isThistheEnd = true;
		std::vector<CCharacter> temp;
		for (auto i = players.begin(); i != players.end(); i++)
			temp.push_back(*i);
		data->machine.AddState(StateRef(new CGameOver<CLevelGameState>(data, temp, totalScore)), true);
	}
}

void CLevelGameState::STEResume()
{
	if (level.isLevelSet)
	{
		level.setEnnemyList(&entityList);
		level.setClock(&clock);
		level.startLevel();
		gameTime = sf::Time::Zero;
	}
	CGameState::STEResume();
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

CLevelGameState::CLevelGameState(GameDataRef _data, std::vector<CCharacter>& characters)
	:CLevelGameState(_data)
{
	CPlayer temp;
	for (int i = 0; i < characters.size(); i++)
	{
		temp.updateStates(characters[i]);
		players.push_back(temp);
	}
}

CLevelGameState::CLevelGameState(GameDataRef _data, std::vector<CCharacter>& characters, std::string filePath)
: CLevelGameState(_data,characters){
	levelFilePath = filePath;
}

void CLevelGameState::STEInit()
{
	initAssets();
	CGameState::STEInit();
	//CParserXML xml(levelFilePath, &(data->assets), nullptr, &bulletstorage);
	//xml.coreFunction();
	//level = xml.getLevel();
	//level.setEnnemyList(&entityList);
	//level.setClock(&clock);
	//level.startLevel();
}

void CLevelGameState::STEUpdate(float delta)
{
	if(level.isLevelSet==false && isLevelSet==false)
	{
		infoForloading temp;
		temp.bulletStorage = &bulletstorage;
		temp.fileName = levelFilePath;
		temp.level = &level;
		data->machine.AddState(StateRef(new CLoadingState(data, temp)), false);
		isLevelSet = true;
	}

	if(isThistheEnd == false&&level.isLevelSet)
	{
		updateBackground(delta);
		//Auto aim
		for (auto i = players.begin(); i != players.end(); i++)
		{
			i->updateEntity(delta);
			if (i->getMainWeapon()->typeTir == typeAim::autoAim && i->seekForTarget)
			{
				CMob* cible = nearEnemy(&(*i));
				i->getMainWeapon()->changeTarget(cible);
				i->seekForTarget = false;
			}
		}

		size_t temp = entityList.size();
		int previousMax = (int)temp;
		for (int i = 0; i < temp; i++)
		{
			for (auto player = players.begin(); player != players.end(); player++)
				entityList[i]->updatewPlayer(delta, (*player));
			if (entityList[i]->needDelete == true)
			{
				deleteEntity(i);
				i--;
				temp--;
			}
			else
			{
				entityList[i]->updateEntity(delta);
				if (entityList[i]->seekForTarget)
				{
					entityList[i]->setTarget(nearestPlayer(entityList[i]->getPosition()));
				}
			}
		}
		if (players.begin()->needDelete && players.back().needDelete)
			GameOver();
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
		for (auto player = players.begin(); player != players.end(); player++)
		{
			if (player->hasLevelUp == true )
			{
				//data->machine.AddState(StateRef(new CUpgradeState(data, &(*player), &US )), false);
			}
		}
		if (level.updateLevel())
			GameOver();
	}
}

void CLevelGameState::initAssets()
{
	std::vector<std::string> ouioui;
	for (auto i = players.begin(); i != players.end(); i++)
		ouioui.push_back(i->getName());
	data->assets.deleteEverythingBut(ouioui);
	data->assets.clearSoundBuffer();
	data->assets.LoadTexture("lifepoint", LIFEPOINTTEXTURE);
	data->assets.LoadTexture("bomber", "res\\img\\lance-bombe.png");
	data->assets.LoadTexture("lifePowerUp", "res\\img\\lifePowerUp.png");
	data->assets.LoadTexture("enemyImage", ENEMYPNG_FILEPATH);
	data->assets.LoadTexture("bulletSecond", "res\\img\\characters\\bullet_Second.png");
	data->assets.LoadTexture("explosion", "res\\img\\explosion_sprite_sheet.png");
	data->assets.LoadTexture("bulletImage", "res\\img\\characters\\bulletImage.png");
	data->assets.LoadTexture("bulletImageRancoeur", "res\\img\\characters\\bulletRancoeur.png");
	data->assets.LoadTexture("bulletImageGolden", "res\\img\\bullet_Golden.png");
	data->assets.LoadTexture("bombe", "res\\img\\bombe.png");
	data->assets.LoadTexture("shooter", "res\\img\\ennemies\\shooter.png");
	data->assets.LoadTexture("bulletTear", "res\\img\\ennemies\\bulletTear.png");
	data->assets.LoadTexture("R2D2", "res\\img\\characters\\Droide2.png");
	data->assets.LoadTexture("boss", "res\\img\\spacecraft_player_1.png");
	data->assets.LoadTexture("logonormal", "res\\img\\characters\\logonormal2.png");
	data->assets.LoadSFX("bulletSound", "res\\sfx\\Piou.wav");
	data->assets.LoadSFX("enemyRush", "res\\sfx\\vaisseau_fonce.wav");
	data->assets.LoadTexture("rusher", "res\\img\\ennemies\\rusher.png");
}

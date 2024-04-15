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
		CGameState::STEInit();
		for (auto it = players.begin(); it != players.end(); it++)
		{
			it->curUpgrade.push_back(US.initVert(ARME_PRINCIPALE));
			it->curUpgrade.push_back(US.initVert(ARME_SECONDAIRE));
		}
		level.setEnnemyList(&entityList);
		level.setClock(&clock);
	}
	hasChanges = false;
	currentTransi.initTransition();
	CGameState::STEResume();
}

void CLevelGameState::STEDraw(float delta)
{
	sf::RenderWindow& r = data->window;
	if (currentTransi.transiouuuuu==false)
	{
		CGameState::STEDraw(delta);
	}
	else
	{
		r.clear(sf::Color::Red);
		renderBackground();
		for (int i = 0; i < entityList.size(); i++)
		{
			entityList[i]->renderEntity(r);
		}

		r.setView(data->window.getDefaultView());
		//Permet de remettre la vue par défaut et donc pas de soucis sur la suite
		for (int i = 0; i < entityList.size(); i++)
		{
			entityList[i]->renderUI(r);
		}
		for (auto i = players.begin(); i != players.end(); i++)
		{
			i->renderUI(data->window);
		}
		r.draw(uitext);
		r.draw(gameClockText);
		currentTransi.renderTransition(r);
		for (auto i = players.begin(); i != players.end(); i++)
			i->renderEntity(data->window);
	}
}

void CLevelGameState::afterTransi()
{
	startLevel();
}



void CLevelGameState::deleteEntity(int& i)
{
	if (entityList[i]->getType() == 1)
	{
		level.deleteEnemy(entityList[i]);
	}
	CGameState::deleteEntity(i);
}

void CLevelGameState::startLevel()
{
	level.startLevel();
	gameTime = sf::Time::Zero;
	gameClock.restart();
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
	initPlayer();
	infoForloading temp;
	temp.bulletStorage = &bulletstorage;
	temp.fileName = levelFilePath;
	temp.level = &level;
	temp.US = &US;
	temp.assetToLoadForGame = &assetToload;
	data->machine.AddState(StateRef(new CLoadingState(data, temp, &players)), false);
	hasChanges = true;
	isLevelSet = true;
}

void CLevelGameState::STEUpdate(float delta)
{
	if(level.isLevelSet==false && isLevelSet==false)
	{
		infoForloading temp;
		temp.bulletStorage = &bulletstorage;
		temp.fileName = levelFilePath;
		temp.level = &level;
		temp.US= &US;
		data->machine.AddState(StateRef(new CLoadingState(data, temp,&players)), false);
		hasChanges = true;
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

	addAsset("lifepoint", LIFEPOINTTEXTURE);
	addAsset("bomber", "res\\img\\lance-bombe.png");
	addAsset("lifePowerUp", "res\\img\\lifePowerUp.png");
	addAsset("enemyImage", ENEMYPNG_FILEPATH);
	addAsset("bulletSecond", "res\\img\\characters\\bullet_Second.png");
	addAsset("explosion", "res\\img\\explosion_sprite_sheet.png");
	addAsset("bombe", "res\\img\\bombe.png");
	addAsset("shooter", "res\\img\\ennemies\\shooter.png");
	addAsset("bulletTear", "res\\img\\ennemies\\bulletTear.png");
	addAsset("boss", "res\\img\\spacecraft_player_1.png");
	addAsset("rusher", "res\\img\\ennemies\\rusher.png");
	addAsset("enemyRush", "res\\sfx\\vaisseau_fonce.wav");
}

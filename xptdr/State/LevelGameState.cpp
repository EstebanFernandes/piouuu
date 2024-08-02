#include "LevelGameState.h"


void StateNS::LevelGameState::GameOver()
{
	if (isThistheEnd == false)
	{
		isThistheEnd = true;
		std::vector<Character> temp;
		totalScore = 0;

		for (auto i = players.begin(); i != players.end(); i++)
		{
			temp.push_back(*i);
			totalScore += i->getScore();
		}
		//data->machine.AddState(StateRef(new StateNS::GameOver<LevelGameState>(data, temp, totalScore)), true);
	}
}

void StateNS::LevelGameState::STEResume()
{
	if (level.isLevelSet&&isLevelInit==false)
	{
		GameState::STEInit();
		for (auto it = players.begin(); it != players.end(); it++)
		{
			it->curUpgrade.push_back(US.initVert(ARME_PRINCIPALE));
			it->curUpgrade.push_back(US.initVert(ARME_SECONDAIRE));
		}
		// Durée à partir duquel il faut changer de difficulté (difficulté max atteinte en 4mn)
		level.nextDifficultyClock = 240.f / level.maxDifficultyPattern;

		level.setEnnemyList(&entityList);
		level.setClock(&time);
		isLevelInit = true;
	hasChanges = false;
	currentTransi.initTransition();
	}
	GameState::STEResume();
}

void StateNS::LevelGameState::STEDraw(float delta)
{
	sf::RenderWindow& rWindow = data->window;
	drawOnTarget(rWindow,delta);
}

void StateNS::LevelGameState::afterTransi()
{
	startLevel();
}



void StateNS::LevelGameState::drawOnTarget(sf::RenderTarget& target, float interpolation)
{
		GameState::drawOnTarget(target,interpolation);	
	if (currentTransi.transiouuuuu == true)
	{
		currentTransi.renderTransition(target);
		for (auto i = players.begin(); i != players.end(); i++)
			i->renderEntity(target);
	}
}

void StateNS::LevelGameState::updateBackground(float delta)
{
	GameState::updateBackground(delta);
}




void StateNS::LevelGameState::deleteEntity(int& i)
{
	if (entityList[i]->getType() == 1)
	{
		level.deleteEnemy(entityList[i]);
	}
	GameState::deleteEntity(i);
}

void StateNS::LevelGameState::deleteEntity(std::vector<HittingEntity*>::iterator& entity)
{
	if ((*entity)->getType() == 1)
	{
		level.deleteEnemy((*entity));
	}
	entity = entityList.erase(entity);
}

void StateNS::LevelGameState::startLevel()
{
	level.startLevel();
	gameTime = sf::Time::Zero;
	clock.restart();
}

void StateNS::LevelGameState::initBackground()
{
	GameState::initBackground();
	if(level.isInfinite)
	{
		//Pour que l'on voit le soleil en haut à gauche
		indexForSun = static_cast<int>((float)ellipseForSun.getPointCount()*0.88);
		BG1.getLayer("sun").sprite.setPosition(ellipseForSun.getPoint(indexForSun));
		lightShader.setUniform("lightPoint", utilities::glslCoord(ellipseForSun.getPoint(indexForSun), (float)Engine::SCREEN_HEIGHT));
	}
}

StateNS::LevelGameState::LevelGameState(GameDataRef _data)
{
	setData(_data);
}

StateNS::LevelGameState::LevelGameState(GameDataRef _data, std::vector<Character>& characters)
	:LevelGameState(_data)
{
	Player temp;
	for (int i = 0; i < characters.size(); i++)
	{
		temp.updateStates(characters[i]);
		players.push_back(temp);
	}
}

StateNS::LevelGameState::LevelGameState(GameDataRef _data, std::vector<Character>& characters, std::string filePath)
: LevelGameState(_data,characters){
	levelFilePath = filePath;
}

void StateNS::LevelGameState::STEInit()
{
	useIMGUI = true;
	//Le init du cgamestate est appelé au moment du resume
	initAssets();
	initPlayer();
	infoForloading temp;
	temp.bulletStorage = &bulletstorage;
	temp.fileName = levelFilePath;
	temp.level = &level;
	temp.US = &US;
	temp.assetToLoadForGame = &assetToload;
	temp.assetHandler = &data->assets;
	data->machine.AddState(StateRef(new LoadingState(data, temp, &players)), false);
	hasChanges = true;
	isLevelSet = true;
}

void StateNS::LevelGameState::STEUpdate(float delta)
{
	if(isThistheEnd == false&&level.isLevelSet)
	{
		updateBackground(delta);
		//On check d'abord les collisions entre le joueur et les entités. ensuite on update
		if (players.size() == 1)
		{
			players.front().updateEntity(delta);
			if (players.front().getMainWeapon()->typeTir == typeAim::autoAim && players.front().seekForTarget)
			{
				Mob* cible = nearEnemy(&players.front());
				players.front().getMainWeapon()->changeTarget(cible);
				players.front().seekForTarget = false;
			}
		}
		else
		{
			for (auto i = players.begin(); i != players.end(); i++)
			{
				Player& otherPlayer = (i == players.begin()) ? players.back() : players.front();
				if (i->isBetweenLifeAndDeath())
				{
					if (otherPlayer.needDelete)
						i->needDelete = true;
					otherPlayer.setReviveness(false);
					i->updateCercleRevive(otherPlayer);
					i->getMainWeapon()->updateWeapon(delta);
					i->getSecondaryWeapon()->updateWeapon(delta);
				}
				else
				{
					otherPlayer.setReviveness(true);
					i->updateEntity(delta);
					if (i->getMainWeapon()->typeTir == typeAim::autoAim && i->seekForTarget)
					{
						Mob* cible = nearEnemy(&(*i));
						i->getMainWeapon()->changeTarget(cible);
						i->seekForTarget = false;
					}
				}
			}
		}
		for (std::vector<HittingEntity*>::iterator entity = entityList.begin();entity!=entityList.end();)
		{
			for (auto player = players.begin(); player != players.end(); player++)
				(*entity)->updatewPlayer(delta, (*player));
			if ((*entity)->needDelete == true)
			{
				deleteEntity(entity);
			}
			else
			{
				(*entity)->updateEntity(delta);
				if ((*entity)->seekForTarget)
				{
					(*entity)->setTarget(nearestPlayer((*entity)->getPosition()));
				}
				entity++;
			}
		}
		if (players.begin()->needDelete && players.back().needDelete)
			GameOver();
		updateClock();

		updateXpPlayers();
		if (level.updateLevel())
			GameOver();
	}
}

void StateNS::LevelGameState::initAssets()
{
	std::vector<std::string> ouioui;
	for (auto i = players.begin(); i != players.end(); i++)
		ouioui.push_back(i->getName());
	data->assets.deleteEverythingBut(ouioui);
	data->assets.clearSoundBuffer();

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

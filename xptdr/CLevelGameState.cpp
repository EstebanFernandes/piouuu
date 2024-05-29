#include "CLevelGameState.h"


void CLevelGameState::GameOver()
{
	if (isThistheEnd == false)
	{
		isThistheEnd = true;
		std::vector<CCharacter> temp;
		totalScore = 0;

		for (auto i = players.begin(); i != players.end(); i++)
		{
			temp.push_back(*i);
			totalScore += i->getScore();
		}
		data->machine.AddState(StateRef(new CGameOver<CLevelGameState>(data, temp, totalScore)), true);
	}
}

void CLevelGameState::STEResume()
{
	if (level.isLevelSet&&isLevelInit==false)
	{
		CGameState::STEInit();
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
		renderBackground(r);
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



void CLevelGameState::drawOnTarget(sf::RenderTarget& target, float interpolation)
{
	if (currentTransi.transiouuuuu == false)
	{
		CGameState::drawOnTarget(target,interpolation);
	}
	else
	{
		renderBackground(target);
		for (int i = 0; i < entityList.size(); i++)
		{
			entityList[i]->renderEntity(target);
		}

		target.setView(data->window.getDefaultView());
		//Permet de remettre la vue par défaut et donc pas de soucis sur la suite
		for (int i = 0; i < entityList.size(); i++)
		{
			entityList[i]->renderUI(target);
		}
		for (auto i = players.begin(); i != players.end(); i++)
		{
			i->renderUI(data->window);
		}
		target.draw(uitext);
		target.draw(gameClockText);
		currentTransi.renderTransition(target);
		for (auto i = players.begin(); i != players.end(); i++)
			i->renderEntity(target);
	}
}



void CLevelGameState::deleteEntity(int& i)
{
	if (entityList[i]->getType() == 1)
	{
		level.deleteEnemy(entityList[i]);
	}
	CGameState::deleteEntity(i);
}

void CLevelGameState::deleteEntity(std::vector<CHittingEntity*>::iterator& entity)
{
	if ((*entity)->getType() == 1)
	{
		level.deleteEnemy((*entity));
	}
	entity = entityList.erase(entity);
}

void CLevelGameState::startLevel()
{
	level.startLevel();
	gameTime = sf::Time::Zero;
	clock.restart();
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
	if(isThistheEnd == false&&level.isLevelSet)
	{
		updateBackground(delta);
		//Auto aim
		updateBackground(delta);
		//Auto aim
		//On check d'abord les collisions entre le joueur et les entités. ensuite on update
		if (players.size() == 1)
		{
			players.front().updateEntity(delta);
			if (players.front().getMainWeapon()->typeTir == typeAim::autoAim && players.front().seekForTarget)
			{
				CMob* cible = nearEnemy(&players.front());
				players.front().getMainWeapon()->changeTarget(cible);
				players.front().seekForTarget = false;
			}
		}
		else
		{
			for (auto i = players.begin(); i != players.end(); i++)
			{
				CPlayer& otherPlayer = (i == players.begin()) ? players.back() : players.front();
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
						CMob* cible = nearEnemy(&(*i));
						i->getMainWeapon()->changeTarget(cible);
						i->seekForTarget = false;
					}
				}
			}
		}
		for (std::vector<CHittingEntity*>::iterator entity = entityList.begin();entity!=entityList.end();)
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

void CLevelGameState::initAssets()
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

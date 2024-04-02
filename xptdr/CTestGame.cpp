#include "CTestGame.h"
#include"CUpgradeState.h"
#include<math.h>
#include"dot.h"
CTestGame::CTestGame(GameDataRef _data)
{
	setData(_data);
	US.addGraphs("res/data/principalweapon.csv");
	US.addGraphs("res/data/secondaryweapon.csv");
}

CTestGame::CTestGame(GameDataRef _data, CCharacter characterParam)
	:CTestGame(_data)
{
	CPlayer temp;
	temp.updateStates(characterParam);
	players.push_back(temp);
	players.push_back(temp);
}

CTestGame::CTestGame(GameDataRef _data, std::vector<CCharacter>& characters)
	:CTestGame(_data)
{
	
	CPlayer temp;
	for (int i = 0; i < characters.size(); i++)
	{
		temp.updateStates(characters[i]);
		players.push_back(temp);
	}
}

void CTestGame::STEInit()
{
	initAssets();
	*enemyNumber = 0;
	initPlayer();
	initBackground();
	data->assets.jouerMusique("PartieJour");
	bulletstorage = bulletStorage(&(data->assets));
	entityList.push_back(&bulletstorage);
	for (auto it =players.begin();it != players.end();it++)
	{
		it->curUpgrade.push_back(US.initVert(ARME_PRINCIPALE));
		it->curUpgrade.push_back(US.initVert(ARME_SECONDAIRE));
	}
}

void CTestGame::initAssets()
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
	data->assets.LoadTexture("rusher", "res\\img\\ennemies\\rusher.png");
	data->assets.LoadTexture("logonormal", "res\\img\\characters\\logonormal2.png");
	data->assets.LoadTexture("bulletTear", "res\\img\\ennemies\\bulletTear.png");
	data->assets.LoadSFX("bulletSound", "res\\sfx\\Piou.wav");
	data->assets.LoadSFX("enemyRush", "res\\sfx\\vaisseau_fonce.wav");
	
}

void CTestGame::STEHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{
		for (auto i = players.begin(); i != players.end(); i++)
			i->PLYupdateMovement(event);
		if (sf::Event::Closed == event.type)
			data->window.close();
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::Escape)
			{
				data->machine.AddState(StateRef(new CGameMenu(data)), false);
			}
			if (event.key.code == sf::Keyboard::Space)
			{
				players.begin()->gainXP(5);
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
				for (auto i = players.begin(); i != players.end(); i++)
				{
					i->gainXP(4);
				}
			
			}
			//TEMP C POUR MOURIR
			if (event.key.code == sf::Keyboard::M)
			{
				players.begin()->reduceHP(players.begin()->getMaxHealth());
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
		std::vector<CCharacter> temp;
		for (auto i = players.begin(); i != players.end(); i++)
			temp.push_back(*i);
	data->machine.AddState(StateRef(new CGameOver<CTestGame>(data, temp, totalScore)), true);
	}
}

void CTestGame::STEUpdate(float delta)
{
	updateBackground(delta);
	//Auto aim
	//On check d'abord les collisions entre le joueur et les entités. ensuite on update
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
	for (auto player = players.begin(); player != players.end(); player++)
	{
		if (player->hasLevelUp == true )
		{
			// Les graphes doivent dépendre des joueurs
			data->machine.AddState(StateRef(new CUpgradeState(data, &(*player),&US )), false);
		}
	}
	totalScore = 0;
	for (auto player = players.begin(); player != players.end(); player++)
	{
		totalScore += player->getScore();
	}
}

#include "TestGame.h"
#include"UpgradeState.h"
#include<math.h>
#include"../Game/Buff/dot.h"
#include"../Game/Buff/thunder.h"
StateNS::TestGame::TestGame(GameDataRef _data)
{
	setData(_data);
}

StateNS::TestGame::TestGame(GameDataRef _data, Character characterParam)
	:TestGame(_data)
{
	Player temp;
	temp.updateStates(characterParam);
	players.push_back(temp);
	players.push_back(temp);
}

StateNS::TestGame::TestGame(GameDataRef _data, std::vector<Character>& characters)
	:TestGame(_data)
{
	
	Player temp;
	for (int i = 0; i < characters.size(); i++)
	{
		temp.updateStates(characters[i]);
		players.push_back(temp);
	}
}

void StateNS::TestGame::STEInit()
{
	US.setAssets(&data->assets);
	US.init();
	initAssets();
	*enemyNumber = 0;
	initPlayer();
	initBackground();
	data->assets.jouerMusique("PartieJour");
	bulletstorage = bulletStorage(&(data->assets));
	entityList.push_back(&bulletstorage);
	currentTransi.initTransition();
	int i = 0;
	for (auto it = players.begin(); it != players.end(); it++)
	{
		it->curUpgrade.push_back(US.initVert(ARME_PRINCIPALE));
		it->curUpgrade.push_back(US.initVert(ARME_SECONDAIRE));
	}

	useIMGUI = true;
}

void StateNS::TestGame::initAssets()
{
	std::vector<std::string> ouioui;
	for (auto i = players.begin(); i != players.end(); i++)
		ouioui.push_back(i->getName());
	data->assets.deleteEverythingBut(ouioui);
	data->assets.clearSoundBuffer();
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
	data->assets.LoadTexture("muzzleFlash", "res\\img\\muzzleFlash.png");
	data->assets.LoadSFX("bulletSound", "res\\sfx\\Piou.wav");
	data->assets.LoadSFX("enemyRush", "res\\sfx\\vaisseau_fonce.wav");
	data->assets.LoadSFX("planeSound", "res\\sfx\\plane.mp3");
	data->assets.LoadTexture("fireSpriteSheet", "res\\img\\fireSheet.png");
	data->assets.LoadTexture("thunder", "res\\img\\thunder.png");
	thunder::initializeThunder(&data->assets);
}

void StateNS::TestGame::STEHandleInput(sf::Event& event)
{
	for (auto i = players.begin(); i != players.end(); i++)
		i->PLYupdateMovement(event);
	if (sf::Event::Closed == event.type)
		data->window.close();
	if (event.type == sf::Event::KeyReleased) {
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
				//i->AAAA();
			i->gainXP(10);
			}
			
		}
		//TEMP C POUR MOURIR
		if (event.key.code == sf::Keyboard::M)
		{
			for (auto it = players.begin(); it != players.end(); it++)
			{
				it->reduceHP(40);

			}
			//GameOver();
		}
	}
	else if(event.type==sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			data->machine.AddState(StateRef(new GameMenu(data, this)), false);
		}
	}

}



void StateNS::TestGame::debugInfo()
{
	string ="x pos :" +std::to_string(ellipseForSun.getPoint(indexForSun).x) + " y pos : " + std::to_string(ellipseForSun.getPoint(indexForSun).y);
	ImGui::Text(string.c_str());
}

void StateNS::TestGame::addPowerUp()
{
	entityList.push_back(new PowerUp(&(data->assets)));
}


void StateNS::TestGame::GameOver()
{
	if (isThistheEnd == false)
	{
		isThistheEnd = true;
		std::vector<Character> temp;
		for (auto i = players.begin(); i != players.end(); i++)
			temp.push_back(*i);
	//data->machine.AddState(StateRef(new GameOver<TestGame>(data, temp, totalScore)), true);
	}
}

void StateNS::TestGame::STEUpdate(float delta)
{
	updateBackground(delta);

	//Auto aim
	//On check d'abord les collisions entre le joueur et les entit�s. ensuite on update
	if (players.size() == 1)
	{
		players.front().updateEntity(delta);
		if (players.front().getMainWeapon()->typeTir == typeAim::autoAim && players.front().seekForTarget)
		{
			Mob* cible = nearEnemy(&players.front());
			players.front().getMainWeapon()->changeTarget(cible);
			players.front().seekForTarget = false;
		}
	}else
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
	size_t temp = entityList.size();
	int previousMax = (int)temp;
	std::vector<Mob*>mobs;
	for (HittingEntity* entity : entityList) {
		// Utilisez dynamic_cast pour v�rifier le type r�el � l'ex�cution
		if (Mob* mob = dynamic_cast<Mob*>(entity)) {
			mobs.push_back(mob);
		}
		else {
			std::cerr << "Erreur : L'entit� ne peut pas �tre cast�e en Mob" << std::endl;
		}
	}
	BuffEntity::useGlobal(mobs);
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
	updateClock();
	updateXpPlayers();
	for (auto player = players.begin(); player != players.end(); player++)
	{
		totalScore += player->getScore();
	}
}

//void TestGame::updateXpPlayers()
//{
//	bool wantToLevelUpOne = true
//		, wantToLevelUpTwo = (players.size() == 1) ? false : true;
//	for (auto player = players.begin(); player != players.end(); player++)
//	{
//		if (player == players.begin())
//		{
//			if (!player->wantToLevelUp)
//				wantToLevelUpOne = false;
//		}
//		else {
//			if (!player->wantToLevelUp)
//				wantToLevelUpTwo = false;
//		}
//	}
//	if (wantToLevelUpOne && wantToLevelUpTwo && players.size() == 2)
//		data->machine.AddState(StateRef(new UpgradeState(data, &players, &US, this)), false);
//	else if (wantToLevelUpOne)
//		data->machine.AddState(StateRef(new UpgradeState(data, &(*players.begin()), &US, this)), false);
//	else if (players.size() == 2 && wantToLevelUpTwo)
//		data->machine.AddState(StateRef(new UpgradeState(data, &players.back(), &US, this)), false);
//
//}
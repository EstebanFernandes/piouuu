#include "CLoadingState.h"



CLoadingState::CLoadingState(GameDataRef data_, infoForloading info_,std::list<CPlayer>* pointerToPlayers)
{
	data = data_;
	info = info_;
	players = pointerToPlayers;
}

void CLoadingState::STEInit()
{
	useIMGUI = true;
	//Initialisation du visuel
	float height = (float)data->assets.sCREEN_HEIGHT;
	float width = (float)data->assets.sCREEN_WIDTH;
	for (auto player = players->begin(); player != players->end(); player++)
	{
		playerPos.push_back(player->getPosition());
		player->setPositionEntity(-player->getPosition().x/2.f, playerPos.back().y);
	}
	levelNameText.setFont(data->assets.GetFont("Nouvelle"));
	if (info.fileName != "")
	{
		std::string nomNiveau = info.fileName.substr(info.fileName.find_last_of('/') + 1);
		levelNameText.setString("Niveau : " + nomNiveau);
	}
	else
		levelNameText.setString("Test Zone");
	levelNameText.setPosition(width * 0.4f, height * 0.1f);
	validText.setFont(data->assets.GetFont("Nouvelle"));
	validText.setString("Appuyer sur entrée pour lancer la partie ");
	validText.setPosition(width * 0.3f, height * 0.85f);
	//Lancement du thread
	


	// le premier argument de la fonction est this car c'est une fonction membre
	std::thread t(&CLoadingState::threadFunction,this, &this->info);
	t.detach();//Lance le thread en parallèle du reste
}

void CLoadingState::STEHandleInput(sf::Event& event)
{
	if (sf::Event::Closed == event.type)
		data->window.close();
	if (event.key.code == sf::Keyboard::Enter&& isPlayerSet==true && info.level->isLevelSet)
	{
		currentTransi = CTransition(&data->assets, SENS_TRANSITION::GAUCHE, 1, TEMPS_TRANSI);
		data->machine.RemoveState();
	}
}

void CLoadingState::STEUpdate(float delta)
{
	int tempPlayerSet = 0;
	int i = 0;
	for (auto player = players->begin(); player != players->end(); player++)
	{
		player->updateFx();
		if (player->getPosition().x<playerPos[i].x)
		{
			player->moveEntity(sf::Vector2f(speed, 0.f));
			//std::cout << "update loading level ! Move of "<<speed<<std::endl;
		}
		else
		{
			tempPlayerSet++;
		}
		i++;
	}
	if (tempPlayerSet == playerPos.size())
		isPlayerSet = true;
}

void CLoadingState::STEDraw(float delta)
{
	for (auto player = players->begin(); player != players->end(); player++)
	{
		player->renderEntity(data->window);
	}
	data->window.draw(levelNameText);
	if (isPlayerSet&& info.level->isLevelSet)
		data->window.draw(validText);
}

void CLoadingState::threadFunction(infoForloading* infop)
{
	std::cout << "Start threaded function !";
	if (infop->assetToLoadForGame != NULL)
	{
		for (int i = 0; i < infop->assetToLoadForGame->size(); i++)
		{
			std::pair<std::string, std::string>& currentPair = infop->assetToLoadForGame->at(i);
			load(infop->assetHandler, currentPair);
	
		}

		infop->assetToLoadForGame->clear();
	}
	if(infop->US!=NULL)
	{
		infop->US->addGraphs("res/data/principalweapon.csv");
		infop->US->addGraphs("res/data/secondaryweapon.csv");
	}
	if(infop->fileName!="")
	{
		CParserXML P(infop->fileName, infop->assetHandler, infop->bulletStorage);
		P.coreFunction();
	*(infop->level) = P.getLevel();
	infop->level->isLevelSet = true;
	}
	std::cout << "End of threaded function !";
}

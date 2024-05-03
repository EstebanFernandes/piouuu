#include "CLoadingState.h"



CLoadingState::CLoadingState(GameDataRef data_, infoForloading info_,std::list<CPlayer>* pointerToPlayers)
{
	data = data_;
	info = info_;
	players = pointerToPlayers;
}

void CLoadingState::STEInit()
{
	float height = (float)data->assets.sCREEN_HEIGHT;
	float width = (float)data->assets.sCREEN_WIDTH;
	//Lancement du thread
	// le premier argument de la fonction est this car c'est une fonction membre
	std::thread t(&CLoadingState::threadFunction,this, &this->info,&(data->assets));
	t.detach();//Lance le thread en parallèle du reste
	//Initialisation du visuel
	for (auto player = players->begin(); player != players->end(); player++)
	{
		playerPos.push_back(player->getPosition());
		player->setPositionEntity(-player->getGlobalBounds().width*2.f , playerPos.back().y);
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
}

void CLoadingState::STEHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
			data->window.close();
		if (event.key.code == sf::Keyboard::Enter&& isPlayerSet==true && info.level->isLevelSet)
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

void CLoadingState::threadFunction(infoForloading* infop,CAssetManager* asset)
{
	if (infop->assetToLoadForGame != NULL)
	{
		for (int i = 0; i < infop->assetToLoadForGame->size(); i++)
		{
			std::pair<std::string, std::string>& currentPair = infop->assetToLoadForGame->at(i);
			load(asset, currentPair);
	
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
		CParserXML P(infop->fileName, &(data->assets), infop->bulletStorage);
		P.coreFunction();
	*(infop->level) = P.getLevel();
	infop->level->isLevelSet = true;
	}
	std::cout << "niveau charge !";
}

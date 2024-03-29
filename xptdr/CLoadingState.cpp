#include "CLoadingState.h"



CLoadingState::CLoadingState(GameDataRef data_, infoForloading info_)
{
	data = data_;
	info = info_;
}

void CLoadingState::STEInit()
{// le premier argument de la fonction est this car c'est une fonction membre
	std::thread t(&CLoadingState::threadFunction,this, &this->info);
	t.join();
}

void CLoadingState::STEHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{

		if (event.key.code == sf::Keyboard::Enter)
			data->machine.RemoveState();
	}
}

void CLoadingState::STEUpdate(float delta)
{
}

void CLoadingState::STEDraw(float delta)
{
	data->window.clear(sf::Color::Red);
	data->window.display();
}

void CLoadingState::threadFunction(infoForloading* infoquoi)
{
	CParserXML P(infoquoi->fileName, &(data->assets), nullptr, infoquoi->bulletStorage);
	P.coreFunction();
	*(infoquoi->level) = P.getLevel();
	infoquoi->level->isLevelSet = true;
	std::cout << "niveau charge !";
}

#include "CMainMenuState.h"
#include "CGameState.h"
#include "CInfiniteGameState.h"
#include "CTestGame.h"
CMainMenuState::CMainMenuState(GameDataRef _data) : data(_data)
{
}

void CMainMenuState::STEInit()
{
	index = 0;
	data->assets.LoadFont("Lato", FONT_FILE_PATH); //Load la police d'écriture

	data->assets.LoadTexture("Title",
	MAIN_MENU_TITLE_PATH); // On charge les textures




	temp.setString("Mode infini");
	temp.setPos((data->assets.sCREEN_WIDTH / 2) - temp.getGlobalBounds().width / 2,
		data->assets.sCREEN_HEIGHT * 0.35f);
	where.push_back(0.35f);
	buttons.push_back(temp);

	temp.setString("Comment jouer");
	//temp.setCharacterSize(50);
	temp.setPos((data->assets.sCREEN_WIDTH / 2) - temp.getGlobalBounds().width / 2,
		data->assets.sCREEN_HEIGHT * 0.5f);
	where.push_back(0.5f);
	buttons.push_back(temp);

	temp.setString("Reglages");
	//temp.setCharacterSize(50);
	temp.setPos((data->assets.sCREEN_WIDTH / 2) - (temp.getGlobalBounds().width / 2),
		data->assets.sCREEN_HEIGHT * 0.65f);
	where.push_back(0.65f);
	buttons.push_back(temp);

	CMMQuitButton.setPosition((data->assets.sCREEN_WIDTH / 2) - CMMQuitButton.getGlobalBounds().width / 2,
		(data->assets.sCREEN_HEIGHT *0.8f));

	if (menuMusic.openFromFile("res/sfx/musique_menu_test.wav"))
	{
		menuMusic.play();
		menuMusic.setLoop(true);
	}
	else
	{
		std::cout << "Erreur lors du chargement de la musique des reglages." << std::endl;
	}
}

void CMainMenuState::STEHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{
		int previousSelec = index;
		if (sf::Event::Closed == event.type)
		{
			menuMusic.stop();
			data->window.close();
		else if (event.type == sf::Event::KeyPressed)
		{
			menuMusic.stop();
			data->machine.AddState(StateRef(new CInfiniteGameState(data)), true);
		}
		if (data->inputs.IsTextClicked(CMMHowToPlay, sf::Mouse::Left, data->window))
		{
			menuMusic.stop();
			std::string test;
			data->machine.AddState(StateRef(new CClavierVirtuel(data, 2, 1, test)), false);
		}
		else if (data->inputs.IsTextClicked(CMMPlayButton, sf::Mouse::Left, data->window))
		{
			menuMusic.stop();
			data->machine.AddState(StateRef(new CCharacterSelection(data)), true);
		}
		else if (data->inputs.IsTextClicked(CMMSettingsButton, sf::Mouse::Left, data->window))
		{
			data->machine.AddState(StateRef(new CSettingState(data)), false);
		}
		else if (data->inputs.IsTextClicked(CMMQuitButton, sf::Mouse::Left, data->window))
		{
			menuMusic.stop();
			data->window.close();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
		{
			data->assets.changeScreenType(data->window, data->isFullScreen);
			resizeScreen();
		}
			buttons[previousSelec].setOutlineThickness(0.f);
			buttons[index].setOutlineThickness(3.f);
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.key.code == sf::Mouse::Left)
				choosedButton();
		}
	}
}
void CMainMenuState::resizeScreen()
{
	sf::Vector2f scale;
		if(data->assets.sCREEN_WIDTH == 1920)
		{
			scale.x = data->assets.sCREEN_WIDTH / 1280.f;
			scale.y = data->assets.sCREEN_HEIGHT / 720.f;
		}
		else {
			scale.x =  1280.f/ data->assets.sCREEN_WIDTH;
			scale.y = 720.f/ data->assets.sCREEN_HEIGHT;
		}
		CMMTitle.setScale(scale);
	CMMTitle.setPosition((data->assets.sCREEN_WIDTH / 2) - CMMTitle.getGlobalBounds().width / 2,
		CMMTitle.getGlobalBounds().height * 0.7f);
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].setScale(scale);
		buttons[i].setPos((data->assets.sCREEN_WIDTH / 2) - buttons[i].getGlobalBounds().width / 2,
			(data->assets.sCREEN_HEIGHT *where[i]));
	}
}

void CMainMenuState::STEUpdate(float delta)
{
}

void CMainMenuState::choosedButton()
{
	switch (index) {
	case 0:
		data->machine.AddState(StateRef(new CCharacterSelection(data)), true);
		break;
	case 1:
		data->machine.AddState(StateRef(new CInfiniteGameState(data)), true);
	case 2:
		//data->machine.AddState(StateRef(new CClavierVirtuel(data, 2, 1)), true);
		break;
	case 3:
		data->machine.AddState(StateRef(new CSettingState(data)), false);
		break;
	case 4:
		data->window.close();
		break;

	}
}

void CMainMenuState::outline(int previndex)
{
	switch (index) {
	case 0:
		
		break;
	case 1:
		//data->machine.AddState(StateRef(new CClavierVirtuel(data, 2, 1)), true);
	case 2:
		data->machine.AddState(StateRef(new CInfiniteGameState(data)), true);
		break;
	case 3:
		data->machine.AddState(StateRef(new CSettingState(data)), false);
		break;
	case 4:
		data->window.close();
		break;

	}
}

void CMainMenuState::STEDraw(float delta)
{
	data->window.clear(sf::Color(174, 177, 184));
	data->window.draw(CMMTitle);
	for (int i = 0; i < buttons.size(); i++)
		data->window.draw(buttons[i]);
	data->window.display();
}



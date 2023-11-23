#include "CMainMenuState.h"
#include "CGameState.h"
#include "CInfiniteGameState.h"
#include "CTestGame.h"
CMainMenuState::CMainMenuState(GameDataRef _data) : data(_data)
{
}

void CMainMenuState::STEInit()
{


	data->assets.LoadFont("Lato", FONT_FILE_PATH); //Load la police d'écriture

	data->assets.LoadTexture("Title",
		MAIN_MENU_TITLE_PATH); // On charge les textures


	CMMPlayButton.setFont(data->assets.GetFont("Lato"));
	CMMPlayButton.setString("Jouer");
	CMMPlayButton.setCharacterSize(50);

	CMMHowToPlay.setFont(data->assets.GetFont("Lato"));
	CMMHowToPlay.setString("Comment jouer");
	CMMHowToPlay.setCharacterSize(50);

	CMMInfinitePlayButton.setFont(data->assets.GetFont("Lato"));
	CMMInfinitePlayButton.setString("Mode infini");
	CMMInfinitePlayButton.setCharacterSize(50);

	CMMQuitButton.setFont(data->assets.GetFont("Lato"));
	CMMQuitButton.setString("Quitter");
	CMMQuitButton.setCharacterSize(50);

	CMMSettingsButton.setFont(data->assets.GetFont("Lato"));
	CMMSettingsButton.setString("Reglages");
	CMMSettingsButton.setCharacterSize(50);

	CMMTitle.setTexture(data->assets.GetTexture("Title")); // On les appliques
	
	CMMTitle.setPosition((data->assets.sCREEN_WIDTH / 2) - CMMTitle.getGlobalBounds().width / 2,
		CMMTitle.getGlobalBounds().height*0.7f);

	CMMPlayButton.setPosition( (data->assets.sCREEN_WIDTH / 2)-CMMPlayButton.getGlobalBounds().width/2,
							   (data->assets.sCREEN_HEIGHT *0.2f));

	CMMInfinitePlayButton.setPosition((data->assets.sCREEN_WIDTH / 2) - CMMInfinitePlayButton.getGlobalBounds().width / 2,
		data->assets.sCREEN_HEIGHT * 0.35f);

	CMMHowToPlay.setPosition((data->assets.sCREEN_WIDTH / 2) - CMMHowToPlay.getGlobalBounds().width / 2,
		data->assets.sCREEN_HEIGHT * 0.5f);


	CMMSettingsButton.setPosition((data->assets.sCREEN_WIDTH / 2) - (CMMSettingsButton.getGlobalBounds().width / 2),
		data->assets.sCREEN_HEIGHT * 0.65f);

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
		if (sf::Event::Closed == event.type)
		{
			menuMusic.stop();
			data->window.close();
		}
		if (data->inputs.IsTextClicked(CMMInfinitePlayButton, sf::Mouse::Left, data->window))
		{
			menuMusic.stop();
			data->machine.AddState(StateRef(new CInfiniteGameState(data)), true);
		}
		if (data->inputs.IsTextClicked(CMMHowToPlay, sf::Mouse::Left, data->window))
		{
			menuMusic.stop();
			data->machine.AddState(StateRef(new CClavierVirtuel(data, 2, 1)), true);
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
	}
}

void CMainMenuState::resizeScreen()
{
	CMMTitle.setPosition((data->assets.sCREEN_WIDTH / 2) - CMMTitle.getGlobalBounds().width / 2,
		CMMTitle.getGlobalBounds().height * 0.7f);

	CMMPlayButton.setPosition((data->assets.sCREEN_WIDTH / 2) - CMMPlayButton.getGlobalBounds().width / 2,
		(data->assets.sCREEN_HEIGHT * 0.2f));

	CMMInfinitePlayButton.setPosition((data->assets.sCREEN_WIDTH / 2) - CMMInfinitePlayButton.getGlobalBounds().width / 2,
		data->assets.sCREEN_HEIGHT * 0.35f);

	CMMHowToPlay.setPosition((data->assets.sCREEN_WIDTH / 2) - CMMHowToPlay.getGlobalBounds().width / 2,
		data->assets.sCREEN_HEIGHT * 0.5f);


	CMMSettingsButton.setPosition((data->assets.sCREEN_WIDTH / 2) - (CMMSettingsButton.getGlobalBounds().width / 2),
		data->assets.sCREEN_HEIGHT * 0.65f);

	CMMQuitButton.setPosition((data->assets.sCREEN_WIDTH / 2) - CMMQuitButton.getGlobalBounds().width / 2,
		(data->assets.sCREEN_HEIGHT * 0.8f));
}

void CMainMenuState::STEUpdate(float delta)
{
	
}


void CMainMenuState::STEDraw(float delta)
{
	data->window.clear(sf::Color(174, 177, 184));
	data->window.draw(CMMTitle);
	data->window.draw(CMMInfinitePlayButton);
	data->window.draw(CMMHowToPlay);
	data->window.draw(CMMPlayButton);
	data->window.draw(CMMQuitButton);
	data->window.draw(CMMSettingsButton);
	data->window.display();
}



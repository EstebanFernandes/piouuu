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
	data->assets.LoadTexture("Background",
		MAIN_MENU_BACKGROUND_FILEPATH);

	CMMBackground.setTexture(data->assets.GetTexture("Background"));
	CMMBackground.setScale(1.2f, 1.2f);
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
	CMMTitle.setPosition((SCREEN_WIDTH / 2) - CMMTitle.getGlobalBounds().width / 2,
		CMMTitle.getGlobalBounds().height*0.7f);

	CMMPlayButton.setPosition( (SCREEN_WIDTH / 2)-CMMPlayButton.getGlobalBounds().width/2, 
							   (SCREEN_HEIGHT*0.2f));

	CMMInfinitePlayButton.setPosition((SCREEN_WIDTH / 2) - CMMInfinitePlayButton.getGlobalBounds().width / 2,
		SCREEN_HEIGHT* 0.35f); 

	CMMHowToPlay.setPosition((SCREEN_WIDTH / 2) - CMMHowToPlay.getGlobalBounds().width / 2,
		SCREEN_HEIGHT * 0.5f);


	CMMSettingsButton.setPosition((SCREEN_WIDTH / 2) - (CMMSettingsButton.getGlobalBounds().width / 2),
		SCREEN_HEIGHT* 0.65f);

	CMMQuitButton.setPosition((SCREEN_WIDTH / 2) - CMMQuitButton.getGlobalBounds().width / 2,
		(SCREEN_HEIGHT*0.8f));

	//file chargement
	//aaaa.addKeyWords("numero,Titre,Description,Type,spawn,pre");
	//aaaa.setFileName("C:\\Users\\scizz\\Desktop\\principalWeapon.txt");
	//aaaa.FileAnalysis();
	//aaaa.showValueList();
}

void CMainMenuState::STEHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
			data->window.close();
		if (data->inputs.IsTextClicked(CMMInfinitePlayButton, sf::Mouse::Left, data->window))
		{
			data->machine.AddState(StateRef(new CInfiniteGameState(data)), true);
		}
		if (data->inputs.IsTextClicked(CMMHowToPlay, sf::Mouse::Left, data->window))
		{
			data->machine.AddState(StateRef(new CScoreboardname(data)), true);
		}
		else if (data->inputs.IsTextClicked(CMMPlayButton, sf::Mouse::Left, data->window))
		{
			data->machine.AddState(StateRef(new CTestGame(data)), true);
		}
		else if (data->inputs.IsTextClicked(CMMSettingsButton, sf::Mouse::Left, data->window))
		{
			data->machine.AddState(StateRef(new CSettingState(data)), false);
		}
		else if (data->inputs.IsTextClicked(CMMQuitButton, sf::Mouse::Left, data->window))
		{
			data->window.close();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
		{
			if (!data->isFullScreen)
			{
				data->isFullScreen = true;
				data->window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "ihih", sf::Style::Fullscreen);
			}
			else
			{
				data->isFullScreen = false;
				data->window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "title", sf::Style::Close | sf::Style::Titlebar);
			}
		}
	}
}

void CMainMenuState::STEUpdate(float delta)
{

}

void CMainMenuState::STEDraw(float delta)
{
	data->window.clear();
	data->window.draw(CMMBackground);
	data->window.draw(CMMTitle);
	data->window.draw(CMMInfinitePlayButton);
	data->window.draw(CMMHowToPlay);
	data->window.draw(CMMPlayButton);
	data->window.draw(CMMQuitButton);
	data->window.draw(CMMSettingsButton);
	data->window.display();
}

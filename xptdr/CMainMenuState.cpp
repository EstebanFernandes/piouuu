#include "CMainMenuState.h"
#include "CGameState.h"
#include "CTestGame.h"
#include"CLevelGameState.h"
#include"CButtonState.h"
CMainMenuState::CMainMenuState(GameDataRef _data) : data(_data)
{
}

void CMainMenuState::STEInit()
{
	data->assets.jouerMusique("MenuPrincipal");
	index = 0;
	data->assets.LoadFont("Nouvelle", "res\\font\\SuperLegendBoy-4w8Y.ttf");
	data->assets.LoadFont("Lato", FONT_FILE_PATH); //Load la police d'écriture
	info.setCharacterSize(40);
	info.setFillColor(sf::Color::Transparent);
	info.setOutlineThickness(1.f);
	info.setPosition(20, 20);
	info.setOutlineColor(sf::Color::White);
	info.setFont(data->assets.GetFont("Nouvelle"));
	data->assets.LoadTexture("Title",
		MAIN_MENU_TITLE_PATH); // On charge les textures

	CMMTitle.setTexture(data->assets.GetTexture("Title")); // On les appliques
	sf::Vector2f scale;
	scale.x = data->assets.sCREEN_HEIGHT / CMMTitle.getGlobalBounds().height;
			scale.y = scale.x;
			CMMTitle.setScale(scale);
	CMMTitle.setPosition(data->assets.sCREEN_WIDTH  - CMMTitle.getGlobalBounds().width,0);
	CButton temp(&(data->assets));
	temp.changeBackVisibilty(false);
	temp.setThicknessColor(sf::Color(51,51,51));
	temp.setFontColor(sf::Color(51, 51, 51));
	temp.setString("Test zone");
	temp.setSize(data->assets.sCREEN_WIDTH * 0.15f, data->assets.sCREEN_HEIGHT * 0.1f);
	temp.setPosition((CMMTitle.getGlobalBounds().left / 2.f) - (temp.getGlobalBounds().width / 2.f),
		(data->assets.sCREEN_HEIGHT * 0.2f));
	where.push_back(0.2f);
	buttons.push_back(temp);

	temp.setString("Mode infini");
	temp.setPosition(temp.getGlobalBounds().left,
		data->assets.sCREEN_HEIGHT * 0.35f);
	where.push_back(0.35f);
	buttons.push_back(temp);

	temp.setString("Comment jouer");
	//temp.setCharacterSize(50);
	temp.setPosition(temp.getGlobalBounds().left,
		data->assets.sCREEN_HEIGHT * 0.5f);
	where.push_back(0.5f);
	buttons.push_back(temp);

	temp.setString("Reglages");
	//temp.setCharacterSize(50);
	temp.setPosition(temp.getGlobalBounds().left,
		data->assets.sCREEN_HEIGHT * 0.65f);
	where.push_back(0.65f);
	buttons.push_back(temp);

	temp.setString("Quitter");
	//temp.setCharacterSize(50);
	temp.setPosition(temp.getGlobalBounds().left,(data->assets.sCREEN_HEIGHT * 0.8f));
	where.push_back(0.8f);
	buttons.push_back(temp);

	buttons[index].setOutlineThickness(3.f);
	std::vector<CUI*> mdrr;
	for (int i = 0; i < buttons.size(); i++)
	{
		mdrr.push_back(&buttons[i]);
	}
	applymaxMinCharSize(mdrr);
}

void CMainMenuState::STEHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{
		int previousSelec = index;
		if (sf::Event::Closed == event.type)
			data->window.close();
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Z)
			{
				if (index == 0) {
					index = (int)buttons.size() - 1;
				}
				else {
					index = (index - 1) % buttons.size();
				}
			}
			else if (event.key.code == sf::Keyboard::S)
			{
				index = (index + 1) % buttons.size();
			}
			else if (event.key.code == sf::Keyboard::Enter)
				choosedButton();
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
	scale.x = data->assets.sCREEN_HEIGHT / CMMTitle.getLocalBounds().height;
	scale.y = scale.x;
	CMMTitle.setScale(scale);
	CMMTitle.setPosition(data->assets.sCREEN_WIDTH - CMMTitle.getGlobalBounds().width, 0);
	sf::Vector2f size(data->assets.sCREEN_WIDTH * 0.15f, data->assets.sCREEN_HEIGHT * 0.1f);
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].setSize(size);
		buttons[i].setPosition((CMMTitle.getGlobalBounds().left/2.f) - buttons[i].getGlobalBounds().width / 2.f,
			(data->assets.sCREEN_HEIGHT * where[i]));
	}
	std::vector<CUI*> mdrr;
	for (int i = 0; i < buttons.size(); i++)
	{
		mdrr.push_back(&buttons[i]);
	}
	applymaxMinCharSize(mdrr);
}

void CMainMenuState::STEUpdate(float delta)
{
	std::stringstream ss;
	sf::Vector2i mousePositionScreen = sf::Mouse::getPosition(data->window);
	ss << "mouse position : \n" << "Window : " << mousePositionScreen.x << " " << mousePositionScreen.y << "\n";
	info.setString("Bonjour");
}

void CMainMenuState::choosedButton()
{
	const std::vector<std::string> blabla{ "1 Joueur","2 Joueurs" };
	switch (index) {
	case 0:
		data->machine.AddState(StateRef(new CButtonState(data,blabla,&nbJoueur)), false);
		break;
	case 1:
		data->machine.AddState(StateRef(new CButtonState(data, blabla, &nbJoueur)), false);
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

void CMainMenuState::addLevelType()
{
	switch (index) {
	case 0:
		data->machine.AddState(StateRef(new CTestGame(data,characters)), true);
		break;
	case 1:
		data->machine.AddState(StateRef(new CLevelGameState(data, characters, "res/level/deuxiemeniveau.piou")), true);
		break;
	case 2:
		//data->machine.AddState(StateRef(new CInfiniteGameState(data)), true);
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
	data->window.clear(sf::Color(53,128,200));
	data->window.draw(CMMTitle);
	for (int i = 0; i < buttons.size(); i++)
		data->window.draw(buttons[i]);
	data->window.draw(info);
	data->window.display();
}

void CMainMenuState::STEResume()
{
	resizeScreen();
	std::cout << nbJoueur;
	int indexChara = -1;
	if (nbJoueur == "1 Joueur")
	{
		if (characters.size() == 0)
		{
			characters.push_back(CCharacter());
			data->machine.AddState(StateRef(new CCharacterSelection(data, &characters.back(),(int)characters.size())), false);
		}
		else
			addLevelType();
	}
	else if (nbJoueur == "2 Joueurs")
	{
		if (characters.size() <= 1)
		{
			characters.push_back(CCharacter());
			data->machine.AddState(StateRef(new CCharacterSelection(data, &characters.back(), (int)characters.size())), false);
		}
		else
			addLevelType();
	}
}

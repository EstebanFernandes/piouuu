#include "CMainMenuState.h"
#include "CGameState.h"
#include "CInfiniteGameState.h"
#include "CTestGame.h"
#include"CLevelGameState.h"
CMainMenuState::CMainMenuState(GameDataRef _data) : data(_data)
{
}

void CMainMenuState::STEInit()
{
	data->assets.jouerMusique("MenuPrincipal");
	index = 0;
	data->assets.LoadFont("Lato", FONT_FILE_PATH); //Load la police d'écriture
	info.setCharacterSize(12);
	info.setFillColor(sf::Color::White);
	info.setFont(data->assets.GetFont("Lato"));
	data->assets.LoadTexture("Title",
		MAIN_MENU_TITLE_PATH); // On charge les textures

	CButton temp(&(data->assets));
	temp.setString("Test zone");
	temp.setSize(data->assets.sCREEN_WIDTH * 0.15f, data->assets.sCREEN_HEIGHT * 0.1f);
	temp.setPosition((data->assets.sCREEN_WIDTH / 2) - temp.getGlobalBounds().width / 2,
		(data->assets.sCREEN_HEIGHT * 0.2f));
	where.push_back(0.2f);
	buttons.push_back(temp);



	temp.setString("Mode infini");
	temp.setPosition((data->assets.sCREEN_WIDTH / 2) - temp.getGlobalBounds().width / 2,
		data->assets.sCREEN_HEIGHT * 0.35f);
	where.push_back(0.35f);
	buttons.push_back(temp);

	temp.setString("Comment jouer");
	//temp.setCharacterSize(50);
	temp.setPosition((data->assets.sCREEN_WIDTH / 2) - temp.getGlobalBounds().width / 2,
		data->assets.sCREEN_HEIGHT * 0.5f);
	where.push_back(0.5f);
	buttons.push_back(temp);

	temp.setString("Reglages");
	//temp.setCharacterSize(50);
	temp.setPosition((data->assets.sCREEN_WIDTH / 2) - (temp.getGlobalBounds().width / 2),
		data->assets.sCREEN_HEIGHT * 0.65f);
	where.push_back(0.65f);
	buttons.push_back(temp);

	temp.setString("Quitter");
	//temp.setCharacterSize(50);
	temp.setPosition((data->assets.sCREEN_WIDTH / 2) - temp.getGlobalBounds().width / 2,
		(data->assets.sCREEN_HEIGHT * 0.8f));
	where.push_back(0.8f);
	buttons.push_back(temp);

	CMMTitle.setTexture(data->assets.GetTexture("Title")); // On les appliques

	CMMTitle.setPosition((data->assets.sCREEN_WIDTH / 2) - CMMTitle.getGlobalBounds().width / 2,
		CMMTitle.getGlobalBounds().height * 0.7f);
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
	if (data->assets.sCREEN_WIDTH == 1920)
	{
		scale.x = data->assets.sCREEN_WIDTH / 1280.f;
		scale.y = data->assets.sCREEN_HEIGHT / 720.f;
	}
	else {
		scale.x = 1280.f / data->assets.sCREEN_WIDTH;
		scale.y = 720.f / data->assets.sCREEN_HEIGHT;
	}
	CMMTitle.setScale(scale);
	sf::Vector2f size(data->assets.sCREEN_WIDTH * 0.15f, data->assets.sCREEN_HEIGHT * 0.1f);
	CMMTitle.setPosition((data->assets.sCREEN_WIDTH / 2) - CMMTitle.getGlobalBounds().width / 2,
		CMMTitle.getGlobalBounds().height * 0.7f);
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].setSize(size);
		buttons[i].setPosition((data->assets.sCREEN_WIDTH / 2) - buttons[i].getGlobalBounds().width / 2,
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
	info.setString(ss.str());
}

void CMainMenuState::choosedButton()
{
	switch (index) {
	case 0:
		data->machine.AddState(StateRef(new CCharacterSelection(data)), true);
		break;
	case 1:
		data->machine.AddState(StateRef(new CCharacterSelection(data,&chara)), false);
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
	data->window.draw(info);
	data->window.display();
}

void CMainMenuState::STEResume()
{
	resizeScreen();
	if (chara.getCanonNumber() < 40)
	{
		data->machine.AddState(StateRef(new CLevelGameState(data, chara, "res/level/essai.xml")), true);
	}
}

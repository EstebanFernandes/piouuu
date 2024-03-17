#include "CGameMenu.h"

void CGameMenu::choosedButton()
{
	switch (index)
	{
	case 0:
		resumeClicked = true;
		ahah = resumeClock.restart().Zero;
		data->assets.reprendreMusique("PartieJour");
		decompte.setFont(data->assets.GetFont("Nouvelle"));
		break;
	case 1:
		data->machine.AddState(StateRef(new CSettingState(data)), false);
		break;
	case 2:
		data->machine.RemoveState();
		data->machine.AddState(StateRef(new CMainMenuState(data)), true);
		data->assets.stopMusique("PartieJour");
		break;
	}
}

CGameMenu::CGameMenu(GameDataRef _data) : data(_data)
{
}

void CGameMenu::STEInit()
{
	data->assets.pauseMusique("PartieJour");
	texta.create(data->window.getSize().x, data->window.getSize().y);
	texta.update(data->window);
	backGroundImage.setTexture(texta);
	CButton temp(&(data->assets));
	temp.setString("Reprendre");
	temp.setSize(data->assets.sCREEN_WIDTH * 0.3f, data->assets.sCREEN_HEIGHT * 0.1f);
	temp.changeBackVisibilty(false);
	where.push_back(0.4f);
	buttons.push_back(temp);



	temp.setString("Réglages");

	where.push_back(0.6f);
	buttons.push_back(temp);

	temp.setString("Retour vers le menu principal");
	where.push_back(0.8f);
	buttons.push_back(temp);
	buttons[index].setOutlineThickness(3.f);
	resizeScreen();
}

void CGameMenu::STEHandleInput()
{
	if (!resumeClicked)
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
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					index = 0;
					choosedButton();
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
}

void CGameMenu::STEUpdate(float delta)
{
	if (resumeClicked)
	{
		float temp = resumeClock.getElapsedTime().asSeconds()- ahah.asSeconds();
		std::string temp2;
		if (temp > 3.f)
		{
			data->machine.RemoveState();
		}
		else if (temp > 2.f)
			temp2 = "1";
		else if (temp > 1.f)
			temp2 = "2";
		else
			temp2 = "3";
		decompte.setString(temp2);
		decompte.setPosition(data->window.getSize().x/2.f - decompte.getGlobalBounds().width/2.f,
			data->window.getSize().y / 2.f - decompte.getGlobalBounds().height / 2.f);
	}
}

void CGameMenu::STEDraw(float delta)
{
	data->window.clear(sf::Color::Red);
	data->window.draw(backGroundImage);
	if(resumeClicked)
		data->window.draw(decompte);
	else {
		for (int i = 0; i < buttons.size(); i++)
			data->window.draw(buttons[i]);
	}
	data->window.display();
}


void CGameMenu::resizeScreen()
{
	sf::Vector2f size(data->assets.sCREEN_WIDTH * 0.3f, data->assets.sCREEN_HEIGHT * 0.1f);
	sf::Vector2f targetSize((float)data->assets.sCREEN_WIDTH, (float)data->assets.sCREEN_HEIGHT);

	backGroundImage.setScale(
		targetSize.x / backGroundImage.getLocalBounds().width,
		targetSize.y / backGroundImage.getLocalBounds().height);
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

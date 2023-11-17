#include "CGameMenu.h"

CGameMenu::CGameMenu(GameDataRef _data) : data(_data)
{
}

void CGameMenu::STEInit()
{
	backGroundImage.setTexture(data->assets.GetTexture("pauseScreen"));
	resume.setFont(data->assets.GetFont("Lato"));
	resume.setString("Reprendre");
	resume.setCharacterSize(30);
	resume.setPosition((data->assets.sCREEN_WIDTH / 2.f) - (resume.getGlobalBounds().width / 2.f),
		(data->assets.sCREEN_HEIGHT * 0.7f));
	quitToMMenu.setFont(data->assets.GetFont("Lato"));
	quitToMMenu.setString("Revenir au menu principal");
	quitToMMenu.setCharacterSize(30);


	quitToMMenu.setPosition((data->assets.sCREEN_WIDTH / 2) - (quitToMMenu.getGlobalBounds().width / 2),
		data->assets.sCREEN_HEIGHT * 0.8f);
}

void CGameMenu::STEHandleInput()
{
	if(!resumeClicked)
	{
		sf::Event event;
		while (data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
				data->window.close();
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
			{
				data->assets.changeScreenType(data->window, data->isFullScreen);
			}if (data->inputs.IsTextClicked(resume, sf::Mouse::Left, data->window))
			{
				resumeClicked = true;
			ahah =	resumeClock.restart().Zero;
				//data->machine.RemoveState();
			}
			else if (data->inputs.IsTextClicked(quitToMMenu, sf::Mouse::Left, data->window))
			{
				data->machine.RemoveState();
				data->machine.AddState(StateRef(new CMainMenuState(data)), true);
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Escape)
				{
					resumeClicked = true;
					resumeClock.restart();
				}
			}

		}
	}
	else {

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
		resume.setString(temp2);
		resume.setPosition(data->window.getSize().x/2.f - resume.getGlobalBounds().width/2.f,
			data->window.getSize().y / 2.f - resume.getGlobalBounds().height / 2.f);
	}
}

void CGameMenu::STEDraw(float delta)
{
	data->window.clear(sf::Color::Red);
	data->window.draw(backGroundImage);
	data->window.draw(resume);
	if(!resumeClicked)
		data->window.draw(quitToMMenu);
	data->window.display();
}

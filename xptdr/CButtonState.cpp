#include "CButtonState.h"


CButtonState::CButtonState(GameDataRef _data)
{
	data = _data;
	index = 0;
	selected = NULL;
}

CButtonState::CButtonState(GameDataRef _data, std::vector<std::string> listOfChoices, std::string* choice)
{
	data = _data;
	index = 0;
	selected = NULL;
	choices = listOfChoices;
	selected = choice;
}

void CButtonState::STEInit()
{
	sf::Vector2f pos;
	int screen_Height = data->assets.sCREEN_HEIGHT;
	int screen_Width = data->assets.sCREEN_WIDTH;
	int nbOfButton = (int)choices.size();
	CButton temp(&(data->assets));
	temp.setThicknessColor(sf::Color::White);
	temp.setFontColor(sf::Color::White);
	for (int i = 0; i < nbOfButton; i++)
	{
		temp.setString(choices.at(i));
		temp.setSize(data->assets.sCREEN_WIDTH * 0.15f, data->assets.sCREEN_HEIGHT * 0.1f);
		float ratio = 1 / (float)nbOfButton;
		float t = screen_Width - (temp.getGlobalBounds().width * nbOfButton);
		float spaceBetweenCard = t / (float)(nbOfButton + 1);
		pos.x = spaceBetweenCard + (spaceBetweenCard + temp.getGlobalBounds().width) * i;
		pos.y = (screen_Height / 2.f) - (temp.getGlobalBounds().height / 2.f);
		temp.setPosition(pos);
		buttonList.push_back(temp);
	}
	backFonce = sf::RectangleShape(sf::Vector2f((float)screen_Width, (float)screen_Height));
	backFonce.setFillColor(sf::Color(0, 0, 0, 122));
	back.create(data->window.getSize().x, data->window.getSize().y);
	back.update(data->window);
	spritz.setTexture(back);
}

void CButtonState::STEHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
			data->window.close();
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Q)
			{
				if (index == 0) {
					index = (int)buttonList.size() - 1;
				}
				else {
					index = (index - 1) % buttonList.size();
				}
			}
			else if (event.key.code == sf::Keyboard::D)
			{
				index = (index + 1) % buttonList.size();
			}
			else if (event.key.code == sf::Keyboard::Enter)
				choosedButton();
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.key.code == sf::Mouse::Left)
				choosedButton();
		}
	}
}

void CButtonState::choosedButton()
{
	*selected = choices[index];
	data->machine.RemoveState();
}
void CButtonState::STEUpdate(float delta)
{
	buttonList[index].setOutlineThickness(10.f);
	for (int i = 0; i < buttonList.size(); i++)
	{
		if (i != index)
			buttonList[i].setOutlineThickness(0.f);
	}
}

void CButtonState::STEDraw(float delta)
{
	data->window.clear(sf::Color::Red);
	data->window.draw(spritz);
	data->window.draw(backFonce);
	for (int i = 0; i < buttonList.size(); i++)
	{
		buttonList.at(i).renderButton(data->window);
	}
}

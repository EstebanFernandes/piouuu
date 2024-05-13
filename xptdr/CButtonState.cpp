#include "CButtonState.h"


CButtonState::CButtonState(GameDataRef _data)
{
	data = _data;
	index = 0;
	selected = NULL;
}

CButtonState::CButtonState(GameDataRef _data, std::vector<std::string> listOfChoices, std::string* choice, CState* prevState)
{
	data = _data;
	index = 0;
	selected = NULL;
	choices = listOfChoices;
	selected = choice;
	this->prevState = prevState;
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
			if (event.key.code == inputOfPlayers[0].moveLeft)
			{
				if (index == 0) {
					index = (int)buttonList.size() - 1;
				}
				else {
					index = (index - 1) % buttonList.size();
				}
			}
			else if (event.key.code == inputOfPlayers[0].moveRight)
			{
				index = (index + 1) % buttonList.size();
			}
			else if (event.key.code == inputOfPlayers[0].button1)
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
	prevState->STEUpdate(delta);
	buttonList[index].setOutlineThickness(10.f);
	for (int i = 0; i < buttonList.size(); i++)
	{
		if (i != index)
			buttonList[i].setOutlineThickness(0.f);
	}
}

void CButtonState::STEDraw(float delta)
{
	prevState->STEDraw(delta);
	data->window.draw(backFonce);
	for (int i = 0; i < buttonList.size(); i++)
	{
		buttonList.at(i).renderButton(data->window);
	}
}

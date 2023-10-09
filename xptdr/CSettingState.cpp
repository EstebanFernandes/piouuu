#include "CSettingState.h"


CSettingState::CSettingState(GameDataRef _data) : data(_data)
{
}

void CSettingState::STEInit()
{
	backbutton.setFont(data->assets.GetFont("Lato"));
	backbutton.setString("Revenir au menu principal");
	backbutton.setCharacterSize(60);
	backbutton.setPosition((SCREEN_WIDTH / 2) - (backbutton.getGlobalBounds().width / 2),
		SCREEN_HEIGHT * 0.6);
	//comboBox->onItemSelect(callbackcombobox);
	//Ahouais?

}

void CSettingState::STEHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{
		
		if (sf::Event::Closed == event.type)
			data->window.close();
		else if (data->inputs.IsTextClicked(backbutton, sf::Mouse::Left, data->window))
		{
			data->machine.RemoveState();
		}
	}



}

void CSettingState::STEUpdate(float delta)
{
}

void CSettingState::STEDraw(float delta)
{
	data->window.clear(sf::Color::Red);
	data->window.draw(backbutton);
	data->window.display();

}

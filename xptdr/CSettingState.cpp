#include "CSettingState.h"


int CSettingState::matchKW(std::string word)
{
	for (int i = 0; i < keyWord.size(); i++)
	{
		if (word.find(keyWord[i]) != std::string::npos)
		{
			return i;
		}
	}
	return -2;
}

void CSettingState::outlineGood(int index, int previousSelec)
{
	if (previousSelec != index)
	{
		switch (index)
		{
		case 0:
			musicVolume.setOutlineThickness(outlineThickness);
			break;
		case 1:
			SoundVolume.setOutlineThickness(outlineThickness);
			break;
		case 2:
			fullScreenCon.setOutlineThickness(outlineThickness);
			break;
		}

		switch (previousSelec)
		{
		case 0:
			musicVolume.setOutlineThickness(0.f);
			break;
		case 1:
			SoundVolume.setOutlineThickness(0.f);
			break;
		case 2:
			fullScreenCon.setOutlineThickness(0.f);
			break;
		}



	}
}

CSettingState::CSettingState(GameDataRef _data) : data(_data)
{
}

void CSettingState::STEInit()
{
	float screenheight = (float)data->assets.sCREEN_HEIGHT;
	float screenwidth = (float)data->assets.sCREEN_WIDTH;
	keyWord = { "soundVolume","musicVolume","isFullScreen" };
	value = { 100,100,0 };
	backbutton.setFont(data->assets.GetFont("Lato"));
	backbutton.setString("Revenir au menu principal");
	backbutton.setCharacterSize(60);
	backbutton.setPosition((data->assets.sCREEN_WIDTH / 2) - (backbutton.getGlobalBounds().width / 2),
		data->assets.sCREEN_HEIGHT * 0.6f);
	sf::Vector2f size = sf::Vector2f(300.f, 100.f);
	musicVolume = CSlider(&(data->assets),size,"Volume de la musique");
	sf::Vector2f pos = sf::Vector2f(screenwidth/2.f - musicVolume.getSize().x/2.f
		, screenheight * 0.25f- +musicVolume.getSize().y / 2.f);
	musicVolume.setPosition(pos);
	SoundVolume = CSlider(&(data->assets), size, "Volume des sons");
	pos = sf::Vector2f(screenwidth / 2.f - SoundVolume.getSize().x / 2.f
		, screenheight * 0.5f - +SoundVolume.getSize().y / 2.f);
	fullScreenCon = CCheckbox(&(data->assets), "Plein écran");
	SoundVolume.setPosition(pos);
	pos = sf::Vector2f(screenwidth / 2.f - fullScreenCon.getSize().x / 2.f
		, screenheight * 0.75f - +fullScreenCon.getSize().y / 2.f);
	fullScreenCon.setPosition(pos);
	//On va charger les infos du sons etc depuis ce fichier
	CParserCSV parser = CParserCSV("res/data/settings.csv");
	parser.displayInfo();
	std::vector<std::vector<std::string>> settingsInfo = parser.getElements();
	for (int i = 0; i < settingsInfo.size(); i++)
	{
		int tempIndex = matchKW(settingsInfo[i][0]);
		if (tempIndex != -1)
		{
			value[tempIndex] = std::stoi(settingsInfo[i][1]);
			switch (tempIndex)
			{
			case 0:
				SoundVolume.setValue(value[tempIndex]);
				break;
			case 1:
				musicVolume.setValue(value[tempIndex]);
				break;
			case 2:
				fullScreenCon.setValue(value[tempIndex]);
				break;
			}
		}
	}
	musicVolume.setOutlineThickness(outlineThickness);
}

void CSettingState::STEHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{
		int previousSelec = index;


		if (sf::Event::Closed == event.type)
			data->window.close();
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
		{
			data->assets.changeScreenType(data->window, data->isFullScreen);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			onAction(index, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			onAction(index, 1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			index = (index + 1) % keyWord.size();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (index == 0) {
				index = (int)keyWord.size() - 1;
			}
			else {
				index = (index - 1) % keyWord.size();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			onAction(index, 2);
		}


		else if (data->inputs.IsTextClicked(backbutton, sf::Mouse::Left, data->window))
		{
			data->machine.RemoveState();
		}
		outlineGood(index, previousSelec);
	}



}

void CSettingState::STEUpdate(float delta)
{

}

void CSettingState::STEDraw(float delta)
{
	data->window.clear(sf::Color::Red);
	data->window.draw(backbutton);
	data->window.draw(SoundVolume);
	data->window.draw(musicVolume);
	data->window.draw(fullScreenCon);
	data->window.display();

}

void CSettingState::onAction(int index, int type)
{
	switch (index)
	{
	case 0:
		if (type == 0)
		{
			musicVolume.slideLeft();
		}
		else if (type ==1)
			musicVolume.slideRight();
		data->assets.setOverAllvolumeMusique((float)musicVolume.getValue());
		break;
	case 1:
		if (type == 0)
			SoundVolume.slideLeft();
		else if (type == 1)
			SoundVolume.slideRight();
		break;
	case 2:
		if (type == 2)
		{
			fullScreenCon.changeValue();
			data->assets.changeScreenType(data->window, data->isFullScreen);
		}
		break;
	}
}

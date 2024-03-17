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
		case 3:
			backbutton.setOutlineThickness(outlineThickness);
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
		case 3:
			backbutton.setOutlineThickness(0.f);
			break;
		}



	}
}

CSettingState::CSettingState(GameDataRef _data) : data(_data)
{
}

void CSettingState::STEInit()
{
	outlineThickness = 5.f;
	float screenheight = (float)data->assets.sCREEN_HEIGHT;
	float screenwidth = (float)data->assets.sCREEN_WIDTH;
	keyWord = { "musicVolume","soundVolume","isFullScreen","Retour"};
	value = { 100,100,0,0 };
	sf::Vector2f size(data->assets.sCREEN_WIDTH * 0.5f, data->assets.sCREEN_HEIGHT * 0.2f);
	musicVolume = CSlider(&(data->assets),size,"Volume de la musique");
	SoundVolume = CSlider(&(data->assets), size, "Volume des sons");
	fullScreenCon = CCheckbox(&(data->assets), "Plein écran");
	backbutton = CButton(&(data->assets) , "Retour", 300.f, 100.f);
	resizeScreen();


	//On va charger les infos du sons etc depuis ce fichier
	CParserCSV parser = CParserCSV("res/data/settings.csv");
	parser.displayInfo();
	 settingsInfo = parser.getElements();
	for (int i = 0; i < settingsInfo.size(); i++)
	{
		int tempIndex = matchKW(settingsInfo[i][0]);
		if (tempIndex != -1)
		{
			value[tempIndex] = std::stoi(settingsInfo[i][1]);
			switch (tempIndex)
			{
			case 0:
				musicVolume.setValue(value[tempIndex]);
				break;
			case 1:
				SoundVolume.setValue(value[tempIndex]);
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
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Q)
			{
				onAction(index, 0);
			}
			else if (event.key.code == sf::Keyboard::D)
			{
				onAction(index, 1);
			}
			if (event.key.code == sf::Keyboard::Z)
			{
				if (index == 0) {
					index = (int)keyWord.size() - 1;
				}
				else {
					index = (index - 1) % keyWord.size();
				}
			}
			else if (event.key.code == sf::Keyboard::S)
			{
				index = (index + 1) % keyWord.size();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				onAction(index, 2);
			}
			outlineGood(index, previousSelec);
		}
	}



}

void CSettingState::STEUpdate(float delta)
{

}

void CSettingState::STEDraw(float delta)
{
	data->window.clear(sf::Color(174, 177, 184));
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
		data->assets.setOverAllvolumeSon((float)SoundVolume.getValue());
		break;
	case 2:
		if (type == 2)
		{
			fullScreenCon.changeValue();
			data->assets.changeScreenType(data->window, data->isFullScreen);
			resizeScreen();
		}
		break;
	case 3:
		if (type == 2)
		{
			updateSettingsFile();
			data->machine.RemoveState();
		}
		break;

	}
}

void CSettingState::updateSettingsFile()
{
	for (int i = 0; i < settingsInfo.size(); i++)
	{
		int tempIndex = matchKW(settingsInfo[i][0]);
		if (tempIndex != -1)
		{
			switch (tempIndex)
			{
			case 0:
				settingsInfo[i][1] = std::to_string(musicVolume.getValue());
				break;
			case 1:
				settingsInfo[i][1] = std::to_string(SoundVolume.getValue());
				break;
			case 2:
				settingsInfo[i][1] = std::to_string(fullScreenCon.getValue());
				break;
			}
		}
	}
	std::ofstream outputFile("res/data/settings.csv");
	for (const auto& row : settingsInfo) {
		for (size_t i = 0; i < row.size(); ++i) {
			outputFile << row[i];

			// Ajouter une virgule sauf pour le dernier élément
			if (i < row.size() - 1) {
				outputFile << ";";
			}
		}
		outputFile << std::endl;  // Passer à la ligne après chaque ligne du tableau
	}

	outputFile.close();
}

void CSettingState::resizeScreen()
{
	sf::Vector2f size(data->assets.sCREEN_WIDTH * 0.35f, data->assets.sCREEN_HEIGHT * 0.15f);
	float screenheight = (float)data->assets.sCREEN_HEIGHT;
	float screenwidth = (float)data->assets.sCREEN_WIDTH;
	musicVolume.setSize(size);
	sf::Vector2f pos = sf::Vector2f(screenwidth / 2.f - musicVolume.getSize().x / 2.f
		, screenheight * 0.2f - +musicVolume.getSize().y / 2.f);
	musicVolume.setPosition(pos);
	SoundVolume.setSize(size);
	pos = sf::Vector2f(screenwidth / 2.f - SoundVolume.getSize().x / 2.f
		, screenheight * 0.4f - +SoundVolume.getSize().y / 2.f);
	SoundVolume.setPosition(pos);
	fullScreenCon.setSize(size);
	pos = sf::Vector2f(screenwidth / 2.f - fullScreenCon.getSize().x / 2.f
		, screenheight * 0.6f - +fullScreenCon.getSize().y / 2.f);
	fullScreenCon.setPosition(pos);
	backbutton.setSize(size);
	backbutton.setPosition((data->assets.sCREEN_WIDTH / 2) - (backbutton.getGlobalBounds().width / 2),
		data->assets.sCREEN_HEIGHT * 0.8f);
	std::vector<CUI*> mdrr;
	mdrr.push_back(&SoundVolume);
	mdrr.push_back(&musicVolume);
	mdrr.push_back(&fullScreenCon);
	mdrr.push_back(&backbutton);
	applymaxMinCharSize(mdrr);
}

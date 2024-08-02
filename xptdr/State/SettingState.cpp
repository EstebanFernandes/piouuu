#include "SettingState.h"


int StateNS::SettingState::matchKW(std::string word)
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

void StateNS::SettingState::outlineGood(int index, int previousSelec)
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

StateNS::SettingState::SettingState(GameDataRef _data)
{
	data = _data;
}

void StateNS::SettingState::STEInit()
{
	data->assets.LoadSFX("button", "res\\sfx\\testbutton.wav");
	data->assets.addSFX("button", &selectionButton);
	data->assets.LoadSFX("slideSelect", "res\\sfx\\selectCharacter.wav");
	data->assets.addSFX("slideSelect", &slideSound);
	outlineThickness = 5.f;
	float screenheight = (float)Engine::SCREEN_HEIGHT;
	float screenwidth = (float)Engine::SCREEN_WIDTH;
	keyWord = { "musicVolume","soundVolume","isFullScreen","Retour"};
	value = { 100,100,0,0 };
	sf::Vector2f size(Engine::SCREEN_WIDTH * 0.5f, Engine::SCREEN_HEIGHT * 0.2f);
	musicVolume = Slider(&(data->assets),size,"Volume de la musique");
	musicVolume.setColor(sf::Color(0,0,0,100));
	SoundVolume = Slider(&(data->assets), size, "Volume des sons");
	SoundVolume.setColor(sf::Color(0, 0, 0, 100));
	fullScreenCon = Checkbox(&(data->assets), "Plein �cran");
	fullScreenCon.setColor(sf::Color(0, 0, 0, 100));
	backbutton = Button(&(data->assets) , "Retour", 300.f, 100.f);
	backbutton.setColor(sf::Color(0, 0, 0, 100));
	resizeScreen();

	//On va charger les infos du sons etc depuis ce fichier
	settingsInfo = IO::retrieveCSVFile("res/data/settings.csv");
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

void StateNS::SettingState::STEHandleInput(sf::Event& event)
{
	int previousSelec = index;
	if (sf::Event::Closed == event.type)
		data->window.close();
	else if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == inputOfPlayers[0].moveLeft)
		{
			onAction(index, 0);
		}
		else if (event.key.code == inputOfPlayers[0].moveRight)
		{
			onAction(index, 1);
		}
		if (event.key.code == inputOfPlayers[0].moveUp)
		{
			if (index == 0) {
				index = (int)keyWord.size() - 1;
			}
			else {
				index = (index - 1) % keyWord.size();
			}
			selectionButton->play();
		}
		else if (event.key.code == inputOfPlayers[0].moveDown)
		{
			index = (index + 1) % keyWord.size();
			selectionButton->play();
		}
		else if (sf::Keyboard::isKeyPressed(inputOfPlayers[0].button1))
		{
			onAction(index, 2);
		}
		outlineGood(index, previousSelec);
	}
}

void StateNS::SettingState::STEUpdate(float delta)
{
	updateTime();
	background.updateBackground(delta);
}

void StateNS::SettingState::STEDraw(float delta)
{
	background.renderBackground(data->window);
	data->window.draw(backbutton);
	data->window.draw(SoundVolume);
	data->window.draw(musicVolume);
	data->window.draw(fullScreenCon);

}

void StateNS::SettingState::onAction(int index, int type)
{
	switch (index)
	{
	case 0:
		if (type == 0)
		{
			musicVolume.slideLeft();
			slideSound->play();
		}
		else if (type ==1)
			musicVolume.slideRight();
		data->assets.setOverAllvolumeMusique((float)musicVolume.getValue());
		slideSound->play();
		break;
	case 1:
		if (type == 0)
			SoundVolume.slideLeft();
		else if (type == 1)
			SoundVolume.slideRight();
		data->assets.setOverAllvolumeSon((float)SoundVolume.getValue());
		slideSound->play();
		break;
	case 2:
		if (type == 2)
		{
			fullScreenCon.changeValue();
			data->assets.changeScreenType(data->window, data->isFullScreen);
			slideSound->play();
			resizeScreen();

		}
		break;
	case 3:
		if (type == 2)
		{
			updateSettingsFile();
			data->machine.RemoveState();
		slideSound->play();
		}
		break;
	}
}

void StateNS::SettingState::updateSettingsFile()
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

			// Ajouter une virgule sauf pour le dernier �l�ment
			if (i < row.size() - 1) {
				outputFile << ";";
			}
		}
		outputFile << std::endl;  // Passer � la ligne apr�s chaque ligne du tableau
	}

	outputFile.close();
}

void StateNS::SettingState::resizeScreen()
{
	sf::Vector2f size(Engine::SCREEN_WIDTH * 0.35f, Engine::SCREEN_HEIGHT * 0.15f);
	float screenheight = (float)Engine::SCREEN_HEIGHT;
	float screenwidth = (float)Engine::SCREEN_WIDTH;
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
	backbutton.setPosition((Engine::SCREEN_WIDTH / 2) - (backbutton.getGlobalBounds().width / 2),
		Engine::SCREEN_HEIGHT * 0.8f);
	std::vector<UI*> mdrr;
	mdrr.push_back(&SoundVolume);
	mdrr.push_back(&musicVolume);
	mdrr.push_back(&fullScreenCon);
	mdrr.push_back(&backbutton);
	applymaxMinCharSize(mdrr);
	background.setWindowSize(sf::Vector2u((unsigned int)Engine::SCREEN_WIDTH, (unsigned int)Engine::SCREEN_HEIGHT));
}
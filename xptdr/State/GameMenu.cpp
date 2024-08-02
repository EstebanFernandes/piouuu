#include "GameMenu.h"

void StateNS::GameMenu::choosedButton()
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
		data->machine.AddState(StateRef(new SettingState(data)), false);
		break;
	case 2:
		data->machine.RemoveState();
		data->machine.AddState(StateRef(new MainMenuState(data)), true);
		data->assets.stopMusique("PartieJour");
		break;
	}
}

StateNS::GameMenu::GameMenu(GameDataRef _data, State* prevState)
	: data(_data),gamePointer(prevState)
{
	index = 0;
}

void StateNS::GameMenu::STEInit()
{
	data->assets.pauseMusique("PartieJour");
	Button temp(&(data->assets));
	temp.setString("Reprendre");
	temp.setSize(Engine::SCREEN_WIDTH * 0.3f, Engine::SCREEN_HEIGHT * 0.1f);
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
	if (!blurShader.loadFromFile("shaders/blurFrag.frag",sf::Shader::Fragment))
		std::cout << "bof";
	blurShader.setUniform("textureSampler", sf::Shader::CurrentTexture);
	blurShader.setUniform("u_resolution", sf::Glsl::Vec2((float)Engine::SCREEN_WIDTH, (float)Engine::SCREEN_HEIGHT));
}

void StateNS::GameMenu::STEHandleInput(sf::Event& event)
{
	if (!resumeClicked)
	{
		int previousSelec = index;
		if (sf::Event::Closed == event.type)
			data->window.close();
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == inputOfPlayers[0].moveUp)
			{
				if (index == 0) {
					index = (int)buttons.size() - 1;
				}
				else {
					index = (index - 1) % buttons.size();
				}
			}
			else if (event.key.code == inputOfPlayers[0].moveDown)
			{
				index = (index + 1) % buttons.size();
			}
			else if (event.key.code == inputOfPlayers[0].button1)
				choosedButton();
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				index = 0;
				choosedButton();
			}
			buttons[previousSelec].setOutlineThickness(0.f);
			buttons[index].setOutlineThickness(3.f);
		}
	}

}

void StateNS::GameMenu::STEUpdate(float delta)
{
	if (resumeClicked)
	{
		float temp = resumeClock.getElapsedTime().asSeconds()- ahah.asSeconds();
		std::string temp2;
		if (temp > 3.f)
		{
			data->machine.RemoveState();
			hasChanges = true;
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

void StateNS::GameMenu::STEDraw(float delta)
{
	sf::RenderTexture back;
	back.create(Engine::SCREEN_WIDTH, Engine::SCREEN_HEIGHT);
	back.clear();
	gamePointer->drawOnTarget(back, delta);
	back.display();
	backGroundImage = sf::Sprite(back.getTexture());
	data->window.draw(backGroundImage, &blurShader);
	if(resumeClicked)
		data->window.draw(decompte);
	else {
		for (int i = 0; i < buttons.size(); i++)
			data->window.draw(buttons[i]);
	}
}


void StateNS::GameMenu::resizeScreen()
{
	sf::Vector2f size(Engine::SCREEN_WIDTH * 0.3f, Engine::SCREEN_HEIGHT * 0.1f);
	sf::Vector2f targetSize((float)Engine::SCREEN_WIDTH, (float)Engine::SCREEN_HEIGHT);

	backGroundImage.setScale(
		targetSize.x / backGroundImage.getLocalBounds().width,
		targetSize.y / backGroundImage.getLocalBounds().height);
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].setSize(size);
		buttons[i].setPosition((Engine::SCREEN_WIDTH / 2) - buttons[i].getGlobalBounds().width / 2,
			(Engine::SCREEN_HEIGHT * where[i]));
	}
	std::vector<UI*> mdrr;
	for (int i = 0; i < buttons.size(); i++)
	{
		mdrr.push_back(&buttons[i]);
	}
	applymaxMinCharSize(mdrr);
}

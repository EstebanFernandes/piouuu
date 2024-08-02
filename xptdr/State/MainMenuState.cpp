#include "MainMenuState.h"
#include "GameState.h"
#include "TestGame.h"
#include "LevelGameState.h"
#include "ButtonState.h"
#include "CharacterSelectionMultiState.h"
#include "CommentJouer.h"
#include"../Engine/Transition.h"
StateNS::MainMenuState::~MainMenuState()
{
	data->assets.deleteSound(buttonSound);
	delete levelToLaunch;
}
StateNS::MainMenuState::MainMenuState(GameDataRef _data)
{
	data = _data;
	levelToLaunch = new std::string();
}

void StateNS::MainMenuState::STEInit()
{
	offset = time;
	float screenWidth = (float)Engine::SCREEN_WIDTH;
	float screenHeight = (float)Engine::SCREEN_HEIGHT;

	data->assets.jouerMusique("MenuPrincipal");
	data->assets.LoadTexture("logoPiou", "res\\img\\logoPiou.png");
	data->assets.LoadTexture("avion", "res\\img\\characters\\BaseCharacterSpriteSheet.png");

	index = 0;
	data->assets.LoadFont("Nouvelle", "res\\font\\SuperLegendBoy-4w8Y.ttf");
	data->assets.LoadFont("Lato", FONT_FILE_PATH); //Deprecated
	data->assets.LoadSFX("button", "res\\sfx\\testbutton.wav");
	data->assets.addSFX("button", &buttonSound);
	info.setCharacterSize(40);
	info.setFillColor(sf::Color::White);
	info.setString("Test");
	info.setPosition(20, 20);
	info.setOutlineColor(sf::Color::White);
	info.setFont(data->assets.GetFont("Nouvelle"));
	Button temp(&(data->assets));
	temp.changeBackVisibilty(false);
	temp.setThicknessColor(sf::Color::White);
	temp.setFontColor(sf::Color::White);
	temp.setString("Test zone");
	temp.setSize(screenWidth * 0.15f, screenHeight * 0.1f);
	temp.setPosition((screenWidth * 0.15f) - (temp.getGlobalBounds().width / 2.f),
		(Engine::SCREEN_HEIGHT * 0.2f));
	where.push_back(0.2f);
	buttons.push_back(temp);

	temp.setString("Mode infini");
	temp.setPosition(temp.getGlobalBounds().left,
		Engine::SCREEN_HEIGHT * 0.35f);
	where.push_back(0.35f);
	buttons.push_back(temp);

	temp.setString("Comment jouer");
	//temp.setCharacterSize(50);
	temp.setPosition(temp.getGlobalBounds().left,
		Engine::SCREEN_HEIGHT * 0.5f);
	where.push_back(0.5f);
	buttons.push_back(temp);

	temp.setString("Reglages");
	//temp.setCharacterSize(50);
	temp.setPosition(temp.getGlobalBounds().left,
		Engine::SCREEN_HEIGHT * 0.65f);
	where.push_back(0.65f);
	buttons.push_back(temp);

	temp.setString("Quitter");
	//temp.setCharacterSize(50);
	temp.setPosition(temp.getGlobalBounds().left, (Engine::SCREEN_HEIGHT * 0.8f));
	where.push_back(0.8f);
	buttons.push_back(temp);

	buttons[index].setOutlineThickness(3.f);
	std::vector<UI*> mdrr;
	for (int i = 0; i < buttons.size(); i++)
	{
		mdrr.push_back(&buttons[i]);
	}
	applymaxMinCharSize(mdrr);
	titleSprite.setTexture(data->assets.GetTexture("logoPiou"));
	titleSprite.setOrigin(titleSprite.getLocalBounds().width / 2.f,0.f);
	titleSprite.setPosition(screenWidth * 0.6f , screenHeight * 0.02f);

	demiFond.setSize(sf::Vector2f(buttons[0].getGlobalBounds().width +2* buttons[0].getGlobalBounds().left ,screenHeight));
	demiFond.setFillColor(sf::Color(0, 0, 0, 140));
	
	//Light shader
	renderTexture.create(data->window.getSize().x, data->window.getSize().y);
	lightShader.loadFromFile("shaders/lightFrag.frag",sf::Shader::Fragment);
	lightShader.setUniform("u_resolution", sf::Glsl::Vec2(getEcranBound()));
	lightShader.setUniform("lightPoint", lightPoint);
	
	//Imgui initialization
	useIMGUI = true;
}

void StateNS::MainMenuState::STEHandleInput(sf::Event& event)
{
	int previousSelec = index;
	if (sf::Event::Closed == event.type)
		data->window.close();
	else if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == inputOfPlayers[0].moveUp)
		{
			buttonSound->play();
			if (index == 0) {
				index = (int)buttons.size() - 1;
			}
			else {
				index = (index - 1) % buttons.size();
			}
		}
		else if (event.key.code == inputOfPlayers[0].moveDown)
		{
			buttonSound->play();
			index = (index + 1) % buttons.size();
		}
		else if (event.key.code == inputOfPlayers[0].button1)
			choosedButton();
		buttons[previousSelec].setOutlineThickness(0.f);
		buttons[index].setOutlineThickness(3.f);
	}
}
void StateNS::MainMenuState::resizeScreen()
{
	sf::Vector2f size(Engine::SCREEN_WIDTH * 0.15f, Engine::SCREEN_HEIGHT * 0.1f);
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].setSize(size);
		buttons[i].setPosition((Engine::SCREEN_WIDTH * 0.15f) - (buttons[i].getGlobalBounds().width / 2.f),
			(Engine::SCREEN_HEIGHT * where[i]));
	}
	std::vector<UI*> mdrr;
	for (int i = 0; i < buttons.size(); i++)
	{
		mdrr.push_back(&buttons[i]);
	}
	applymaxMinCharSize(mdrr);
	demiFond.setSize(sf::Vector2f(buttons[0].getGlobalBounds().width + 2 * buttons[0].getGlobalBounds().left,(float) Engine::SCREEN_HEIGHT));
	renderTexture.create(data->window.getSize().x, data->window.getSize().y);
	lightShader.setUniform("u_resolution", sf::Glsl::Vec2(getEcranBound()));
}

void StateNS::MainMenuState::updateTitle()
{
	if (isUp)
	{
		scaleTitle += 0.0002f;
		if (scaleTitle >= 1.25f)
			isUp = false;
	}
	else {
		scaleTitle -= 0.0002f;
		if (scaleTitle <= 1.f)
			isUp = true;
	}
	titleSprite.setScale(scaleTitle,scaleTitle);
}

void StateNS::MainMenuState::updateLight()
{
	Button& currentButton = buttons[index];
	if (lightPoint.x == 0.f && lightPoint.y == 0.f)//Première fois
	{
		lightPoint = sf::Vector2f(currentButton.getGlobalBounds().left, currentButton.getTextPosition().y);
	}
	else {
		float leftBorder = currentButton.getGlobalBounds().left;
		float percent = (lightPoint.x - leftBorder) / (currentButton.getGlobalBounds().width );
		percent += 0.1f;
		if (percent > 1.f)
			percent = 0;
		lightPoint.x = leftBorder + currentButton.getGlobalBounds().width * percent;
	}
}

void StateNS::MainMenuState::STEUpdate(float delta)
{
	updateTime();
	updateTitle();
	background.updateBackground(delta);
	if (lightClock.getElapsedTime().asSeconds() > 0.5f)
	{
		//updateLight();
		lightClock.restart();
	}
	// Mise à jour de la position de la lumière en fonction de la position de la souris
	lightPoint = utilities::glslCoord(sf::Vector2f(buttons[index].getGlobalBounds().left+ buttons[index].getGlobalBounds().width/2.f,
		buttons[index].getGlobalBounds().top + buttons[index].getGlobalBounds().height / 2.f),(float)Engine::SCREEN_HEIGHT);
	lightShader.setUniform("lightPoint", lightPoint);
	//if (std::abs(time-offset )<= 1.f)
	test1++;
}

void StateNS::MainMenuState::choosedButton()
{
	const std::vector<std::string> oneandTwoP{ "1 Joueur","2 Joueurs" };
	switch (index) {
	case 0:
		data->machine.AddState(StateRef(new ButtonState(data, oneandTwoP,&nbJoueur, this)), false);
		isTest = true;
		break;
	case 1:
		data->machine.AddState(StateRef(new ButtonState(data, oneandTwoP, &nbJoueur,this)), false);
		break;
	case 2:
		data->machine.AddState(StateRef(new CCommentJouer(data)), false);
		break;
	case 3:
		data->machine.AddState(StateRef(new SettingState(data)), false);
		break;
	case 4:
		data->window.close();
		break;
	}
	
}

void StateNS::MainMenuState::addLevelType()
{
	switch (index) {
	case 0:
		data->machine.AddState(StateRef(new TestGame(data,characters)), true);
		break;
	case 1:
		data->machine.AddState(StateRef(new LevelGameState(data, characters, "res/level/"+*levelToLaunch)), true);
		break;
	case 2:
		//data->machine.AddState(StateRef(new CInfiniteGameState(data)), true);
		break;
	case 3:
		currentTransi = Transition(&(data->assets), Engine::SENS_TRANSITION::DROITE, TEMPS_TRANSI);
		currentTransi.initTransition();
		data->machine.AddState(StateRef(new SettingState(data)), false);
		break;
	case 4:
		data->window.close();
		break;

	}
}

void StateNS::MainMenuState::STEDraw(float delta)
{
	sf::RenderTexture back;
	back.create(data->window.getSize().x, data->window.getSize().y);
	back.clear();
	background.renderBackground(back);
	back.draw(demiFond);
	back.draw(buttons[index]);
	back.draw(titleSprite);
	for (int i = 0; i < buttons.size(); i++)
	{
		if (i != index)
			back.draw(buttons[i]);
	}
	back.display();
	spriteRender.setTexture(back.getTexture());
	//data->window.draw(spriteRender, &lightShader);
	data->window.draw(spriteRender);

}

void StateNS::MainMenuState::STEResume()
{
	resizeScreen();
	std::cout << nbJoueur;
	int indexChara = -1;
	if (nbJoueur == "1 Joueur")
	{
		if (characters.size() == 0)
		{
			characters.push_back(Character());
			if(isTest)
				data->machine.AddState(StateRef(new CharacterSelection(data, &characters.back(), (int)characters.size())),false);
			else
			data->machine.AddState(StateRef(new LevelSelectionState(data, &characters, levelToLaunch)), false);
		}
		else if(characters[0].getName()=="")
		{
			characters.clear();
			nbJoueur = "";
			isTest = false;
		}
		else
			addLevelType();
	}
	else if (nbJoueur == "2 Joueurs")
	{
		if (characters.size() != 2)
		{
			characters.push_back(Character());
			characters.push_back(Character());
			if(isTest)
				data->machine.AddState(StateRef(new CharacterSelectionMultiState(data, &characters)), false);
			else
			data->machine.AddState(StateRef(new LevelSelectionState(data, &characters, levelToLaunch)), false);
		}
		else if (characters[0].getName() == "")
		{
			nbJoueur = "";
			characters.clear();
			isTest = false;
		}
		else
			addLevelType();
	}
}

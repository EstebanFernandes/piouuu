#include "CGameState.h"

CGameState::CGameState()
{
}

CGameState::CGameState(GameDataRef _data) : data(_data)
{
	
}

CGameState::CGameState(GameDataRef _data, CCharacter characterParam) : data(_data)
{
	player1.updateStates(characterParam);
}


CGameState::~CGameState()
{
}
void CGameState::initPlayer()
{
	player1.setAssets(& (data->assets));
	player1.updateMisc();
	player1.setPositionEntity(400.f, 400.f);
}

void CGameState::initBackground()
{
	sf::Vector2u TextureSize;  //Added to store texture size.
	sf::Vector2u WindowSize;   //Added to store window size.
	BG1.setAssets(&(data->assets));
	BG1.setWindowSize(data->window.getSize());
	sf::Sprite t1,t2,t3,t4,t5;

	data->assets.LoadTexture("background", 
		"res\\img\\layers\\parallax-mountain-bg.png");

	TextureSize = data->assets.GetTexture("background").getSize(); //Get size of texture.
	WindowSize = data->window.getSize();

	float ScaleX = (float)(WindowSize.x*1.1f) / TextureSize.x;
	float ScaleY = (float)WindowSize.y / TextureSize.y;     //Calculate scale.

	t1.setTexture(data->assets.GetTexture("background"));
	t1.setScale(ScaleX, ScaleY);      //Set scale. 
	BG1.addLayer(t1, "background", 0.0001f,CBackground::background);

	data->assets.LoadTexture("firstLayer", 
		"res\\img\\layers\\parallax-mountain-montain-far.png");
	TextureSize = data->assets.GetTexture("firstLayer").getSize(); //Get size of texture.
	WindowSize = data->window.getSize();

	ScaleX = (float)(WindowSize.x * 1.1f) / TextureSize.x;
	ScaleY = (float)WindowSize.y / TextureSize.y;
	t2.setTexture(data->assets.GetTexture("firstLayer")); 
	t2.setScale(ScaleX, ScaleY);      //Set scale. 

	BG1.addLayer(t2, "firstlayer", 0.1f, CBackground::bot); 
	BG1.addAndScaleLayer("res\\img\\layers\\parallax-mountain-mountains.png",
		"secondLayer", 0.2f);
	BG1.addAndScaleLayer("res\\img\\layers\\parallax-mountain-trees.png",
		"thirdlayer", 0.4f);
	BG1.addAndScaleLayer("res\\img\\layers\\parallax-mountain-foreground-trees.png",
		"forthlayer", 0.5f);

	uitext.setCharacterSize(12);
	uitext.setFillColor(sf::Color::White);
	uitext.setFont(data->assets.GetFont("Lato"));

	gameClockText.setCharacterSize(20);
	gameClockText.setFillColor(sf::Color::White);
	gameClockText.setFont(data->assets.GetFont("Lato"));
	gameTime.Zero;
}
void CGameState::STEInit()
{
	*enemyNumber = 0;
	initPlayer();
	initBackground();
	data->assets.jouerMusique("PartieJour");
	bulletstorage = bulletStorage(&(data->assets));
	entityList.push_back(&bulletstorage);
}

void CGameState::STEHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{
		player1.PLYupdateMovement(event);
		if (sf::Event::Closed == event.type)
			data->window.close();
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::Escape)
			{
				data->machine.AddState(StateRef(new CGameMenu(data)), false);
			}
		}
	}

}

void CGameState::addEnemy(std::string enemyName)
{
	if (enemyName == "roaming") {
		RoamingEnemy* enemy = new RoamingEnemy(&(data->assets));
		entityList.push_back(enemy);
		(*enemyNumber)++;
	}
	else if (enemyName == "shooter") {
		ShootingEnemy* enemy = new ShootingEnemy(&(data->assets), &player1);
		enemy->setBulletStorage(&bulletstorage);
		entityList.push_back(enemy);
		(*enemyNumber)++;
	}
	else if (enemyName == "bomber") {
		BomberEnemy* enemy = new BomberEnemy(&(data->assets));
		enemy->setBulletStorage(&bulletstorage);
		entityList.push_back(enemy);
		(*enemyNumber)++;
	}
	else if (enemyName == "bomberInverse") {
		BomberEnemy* enemy = new BomberEnemy(&(data->assets), false);
		enemy->setBulletStorage(&bulletstorage);
		entityList.push_back(enemy);
		(*enemyNumber)++;
	}
	else if (enemyName == "pantin") {
		sf::Vector2f mousePos((float)sf::Mouse::getPosition(data->window).x, (float)sf::Mouse::getPosition(data->window).y);
		testEnemy* enemy = new testEnemy(&(data->assets), mousePos, 50);
		entityList.push_back(enemy);
		(*enemyNumber)++;
	}
	else if (enemyName == "rusher") {
		RusherEnemy* enemy = new RusherEnemy(&(data->assets), &player1);
		entityList.push_back(enemy);
		(*enemyNumber)++;
	}
	else if (enemyName == "boss") {
		Boss* enemy = new Boss(&(data->assets), &player1, &entityList, enemyNumber);
		enemy->setBulletStorage(&bulletstorage);
		entityList.push_back(enemy);
		(*enemyNumber)++;
	}
	else {
		std::cout << "tentative d'invocation d'un ennemi qui n'existe pas";
	}

}

void CGameState::addPowerUp(sf::Vector2f pos)
{
	entityList.push_back(new CPowerUp(pos,&(data->assets)));
}


void CGameState::STEUpdate(float delta)
{
	updateBackground(delta);
	//Auto aim
	CMob* nearEnemy = NULL;
	sf::Vector2f lessDir(1920.f, 1080.f);
	//On check d'abord les collisions entre le joueur et les entités. ensuite on update
	player1.updateEntity(delta);
	size_t temp = entityList.size();
	int previousMax = (int)temp;
	//Si c'est un AutoAim
	if (player1.getMainWeapon()->typeTir == player1.getMainWeapon()->autoAim)
	{
		for (int i = 0; i < temp; i++)
		{
			entityList[i]->updatewPlayer(delta, player1);
			if (entityList[i]->needDelete == true)
			{
				deleteEntity(i);
				temp--;
			}
			else
			{
				entityList[i]->updateEntity(delta);
				if (entityList[i]->getType() == 1 && entityList[i]->isDead == false)
				{
					sf::Vector2f dirTemp = entityList[i]->getDistance(player1);
					float un = (float)std::sqrt(pow(lessDir.x, 2) + pow(lessDir.y, 2));
					float deux = (float)std::sqrt(pow(dirTemp.x, 2) + pow(dirTemp.y, 2));
					if (un > deux)
					{
						lessDir = dirTemp;
						nearEnemy = entityList[i];
					}
				}
			}
		}
		if (player1.seekForTarget == true && nearEnemy != NULL)
		{
			player1.getMainWeapon()->changeTarget(nearEnemy);
			player1.seekForTarget = false;
		}
	}
	else {
		for (int i = 0; i < temp; i++)
		{
			entityList[i]->updatewPlayer(delta, player1);
			if (entityList[i]->needDelete == true)
			{
				deleteEntity(i);
				temp--;
			}
			else
				entityList[i]->updateEntity(delta);
		}
	}
	if (player1.needDelete)
		GameOver();

	if (previousMax != temp)
	{
		data->assets.checkSound();
	}
	//Information / Clock updates
	sf::Vector2f tempw = player1.getSprite().getPosition();
	std::stringstream ss;
	ss << "Player level : " << player1.getLevel() << std::endl <<
		"XP : " << player1.getXp() << std::endl <<
		"Max xp : " << player1.getMaxXp() << "\n" <<
		"Score : " << player1.getScore() << std::endl << "\n";
	//"Bullet number : " << player1.BAW.getVector()->size() << "\n";
	uitext.setString(ss.str());
	clock = (gameTime.asSeconds() + gameClock.getElapsedTime().asSeconds()) * 100.f;
	clock = ceil(clock);
	clock = clock / 100.f;
	std::string i = std::to_string(clock);
	size_t r = i.find('.') + 3;
	i.erase(r, i.size() - r);
	size_t ti = gameClockText.getString().getSize();
	gameClockText.setString(i);
	if (ti != i.size())
		gameClockText.setPosition(sf::Vector2f(data->assets.sCREEN_WIDTH / 2 - gameClockText.getGlobalBounds().width / 2, 20.f));

	//Condition qui assure que le joueur prend bien un niveau par un niveau
	if (player1.hasLevelUp == true && currentLevelOfplayer != player1.getLevel())
	{
		currentLevelOfplayer++;
		data->machine.AddState(StateRef(new CUpgradeState(data, &player1, &Upgradegraphs)), false);
	}
}


void CGameState::updateBackground(float delta)
{
	BG1.updateCBackground(delta);
}

void CGameState::deleteEntity(int& i)
{
	if (entityList[i]->getType() == 1) {
		{
			(*enemyNumber)--;
			int random = 1 + (rand() % 99);
			if (random <= 15)
			{
				sf::Vector2f r(entityList[i]->getGlobalBounds().getPosition().x + entityList[i]->getGlobalBounds().width / 2,
					entityList[i]->getGlobalBounds().getPosition().y + entityList[i]->getGlobalBounds().height / 2);
				addPowerUp(r);
			}

		}
	}
	//entityList[i]->die(entityList);
	delete entityList[i];
	entityList.erase(entityList.begin() + i);
	if (i != 0)
		i--;
}


void CGameState::renderBackground()
{
	BG1.renderBackground(data->window);
}

void CGameState::STEDraw(float delta)
{
	sf::RenderWindow& r = data->window;
	r.clear(sf::Color::Red);
	renderBackground();
	player1.renderEntity(r);
	for (int i = 0; i < entityList.size(); i++)
	{
		entityList[i]->renderEntity(r);
	}
	//DrawPlayer();
	//Permet de remettre la vue par défaut et donc pas de soucis sur la suite
	r.setView(data->window.getDefaultView());
	r.draw(uitext);
	r.draw(gameClockText);
	r.display();
}

void CGameState::STEResume()
{
	data->assets.DeleteTexture("pauseScreen");
	gameClock.restart();
	CESTBON = false;
	player1.resetMovement();
	player1.updateMisc();
	if (player1.hasLevelUp == true && currentLevelOfplayer == player1.getLevel())
		player1.hasLevelUp = false;
}

GameDataRef CGameState::getData()
{
	return data;
}

void CGameState::STEPause()
{
	gameTime += gameClock.getElapsedTime();
}




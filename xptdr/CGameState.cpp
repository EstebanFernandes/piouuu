#include "CGameState.h"

CGameState::CGameState()
{
}

CGameState::CGameState(GameDataRef _data) : data(_data)
{
	
}

CGameState::~CGameState()
{
}
void CGameState::initPlayer()
{
	player1.setAssets(& (data->assets));
		
}

void CGameState::initBackground()
{
	sf::Vector2u TextureSize;  //Added to store texture size.
	sf::Vector2u WindowSize;   //Added to store window size.
	BG1.setAssets(&(data->assets));
	BG1.setWindowSize(data->window.getSize());
	sf::Sprite t1,t2,t3,t4,t5;
	data->assets.LoadTexture("background", 
		"C:\\Users\\scizz\\source\\repos\\xptdr\\res\\img\\layers\\parallax-mountain-bg.png");
	TextureSize = data->assets.GetTexture("background").getSize(); //Get size of texture.
	WindowSize = data->window.getSize();
	float ScaleX = (float)(WindowSize.x*1.1f) / TextureSize.x;
	float ScaleY = (float)WindowSize.y / TextureSize.y;     //Calculate scale.
	t1.setTexture(data->assets.GetTexture("background"));
	t1.setScale(ScaleX, ScaleY);      //Set scale. 
	BG1.addLayer(t1, "background", 0.0001f,CBackground::background);

	data->assets.LoadTexture("firstLayer", 
		"C:\\Users\\scizz\\source\\repos\\xptdr\\res\\img\\layers\\parallax-mountain-montain-far.png");
	TextureSize = data->assets.GetTexture("firstLayer").getSize(); //Get size of texture.
	WindowSize = data->window.getSize();
	ScaleX = (float)(WindowSize.x * 1.1f) / TextureSize.x;
	ScaleY = (float)WindowSize.y / TextureSize.y;
	t2.setTexture(data->assets.GetTexture("firstLayer")); 
	t2.setScale(ScaleX, ScaleY);      //Set scale. 
	BG1.addLayer(t2, "firstlayer", 0.1f, CBackground::bot); 
	BG1.addAndScaleLayer("C:\\Users\\scizz\\source\\repos\\xptdr\\res\\img\\layers\\parallax-mountain-mountains.png",
		"secondLayer", 0.2f);
	BG1.addAndScaleLayer("C:\\Users\\scizz\\source\\repos\\xptdr\\res\\img\\layers\\parallax-mountain-trees.png",
		"thirdlayer", 0.4f);
	BG1.addAndScaleLayer("C:\\Users\\scizz\\source\\repos\\xptdr\\res\\img\\layers\\parallax-mountain-foreground-trees.png",
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
	initPlayer();
	initBackground();
	initEnemy();
}

void CGameState::STEHandleInput()
{
	sf::Event event;
	while (data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
			data->window.close();
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
		{
			if (!data->isFullScreen)
			{
				data->isFullScreen = true;
				data->window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "ihih", sf::Style::Fullscreen);
			}
			else
			{
				data->isFullScreen = false;
				data->window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "title", sf::Style::Close | sf::Style::Titlebar);
			}
		}if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::Escape)
			{
				sf::Texture texture;
				texture.create(SCREEN_WIDTH, SCREEN_HEIGHT);
				texture.update(data->window);
				data->assets.LoadTexture("pauseScreen", texture);
				gameTime += gameClock.getElapsedTime();
				data->machine.AddState(StateRef(new CGameMenu(data)), false);
			}
		}
	}

}

void CGameState::addEnemy()
{
	entityList.push_back(new CEnemy(&(data->assets)));
	enemyNumber++;
}


void CGameState::STEUpdate(float delta)
{
	updateBackground(delta);
	//On check d'abord les collisions entre le joueur et les entités. ensuite on update
	size_t temp = entityList.size();
	player1.updateEntity(delta);
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
	if (player1.needDelete)
		GameOver();
	//Information / Clock updates
	sf::Vector2f tempw = player1.getSprite().getPosition();
	std::stringstream ss;
	ss <<"Player level : "<<player1.getLevel()<<std::endl <<
		"XP : " << player1.xp<<std::endl <<
		"Max xp : " << player1.maxXp << "\n";
	uitext.setString(ss.str());
	float clock = gameTime.asSeconds() * 100.f + gameClock.getElapsedTime().asSeconds() * 100.f;
	clock = ceil(clock);
	clock =clock/ 100.f;
	std::string i = std::to_string(clock);
	size_t r = i.find('.')+3;
	i.erase(r, i.size() - r);
	size_t ti = gameClockText.getString().getSize();
	gameClockText.setString(i);
	if(ti!=i.size())
		gameClockText.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - gameClockText.getGlobalBounds().width / 2, 20.f));
}


void CGameState::updateBackground(float delta)
{
	BG1.updateCBackground(delta);
}



void CGameState::updateCollision(float dt)
{
	////top
	//if (moto->getGlobalBounds().top  <= 0)
	//{
	//	//moto->resetVelocityY();
	//	moto->setPositionEntity(
	//		moto->getGlobalBounds().left,0);
	//}
	////bot
	//if (moto->getGlobalBounds().top + moto->getGlobalBounds().height >= data->window.getSize().y)
	//{
	//	//moto->resetVelocityY();
	//	moto->setPositionEntity(
	//		moto->getGlobalBounds().left,
	//		data->window.getSize().y- moto->getGlobalBounds().height
	//	);
	//}
	////gauche
	//if (moto->getGlobalBounds().left <= 0)
	//{
	//	//moto->resetVelocityX();
	//	moto->setPositionEntity(0,moto->getGlobalBounds().top);
	//}
	////droite
	//if (moto->getGlobalBounds().left + moto->getGlobalBounds().width >= SCREEN_WIDTH)
	//{
	//	//moto->resetVelocityX();
	//	moto->setPositionEntity(
	//		SCREEN_WIDTH-moto->getGlobalBounds().width,
	//		moto->getGlobalBounds().top
	//	);
	//}

	////Collision between bullet and enemy
	//std::vector<CBullet>& r = moto->getBullets();
	//size_t temp = r.size();
	//size_t temp2 = enemyList.size();
	//	//update collision between bullets and boundaries
	//moto->updateBullets(dt);
	//temp = r.size();
	//if (temp != 0)
	//{
	//	//Update collison for each bullet with eachenemies
	//	for (int i = 0; i < temp;i++)
	//	{
	//		for (int j = 0; j<temp2 ;j++)
	//		{
	//		CEnemy& enemyI = enemyList[j];
	//			if (temp == 0)
	//				break;
	//			else {
	//				if (enemyI.isDead ==false)
	//				{
	//					if (r[i].checkCollisions(enemyI.getGlobalBounds()))
	//					{
	//						enemyI.reduceHP(r[i].getDamage());
	//						r.erase(r.begin() + i);
	//						if (i != 0)
	//							i--;
	//						if (enemyI.getLifePoint() <= 0)
	//						{
	//							enemyI.onAvance = false;
	//							enemyI.isDead = true;
	//						}
	//					}
	//				}
	//			}
	//		temp = r.size();
	//		}
	//	}
	//}

	//for (int i = 0; i < temp2; i++)
	//{
	//	CEnemy& enemyI = enemyList[i];
	//	//Si l'ops est mort on boucle jusqu'à ce que l'animation d'explosion soit fini
	//	if (enemyI.isDead == true)
	//	{
	//		if (enemyI.updateExplosionSprite())
	//		{
	//			moto->gainXP(enemyI.getLevel());
	//			enemyList.erase(enemyList.begin() + i); //efface la balle et permet de ne pas avoir trop d'élement
	//			temp2--;
	//			if (i != 0)
	//				i--;
	//		}
	//	}
	//	else {//Sinon on regarde si l'ennemi passe à travers le joueur
	//		if (enemyI.isHitting == false)
	//		{
	//			if (enemyI.updateEntity(moto->getGlobalBounds(),dt))
	//			{
	//				//Fonctionne pas
	//				moto->getSprite().setColor(sf::Color::Green);
	//				moto->reduceHP(3);
	//				enemyI.isHitting = true;
	//			}
	//		} //Sinon on check normal les collisions avec le bord de l'écran
	//		else if(enemyI.updateEntity(moto->getGlobalBounds(), dt)==false)
	//			enemyI.isHitting = false;
	//		enemyI.updateMovement(dt);
	//	}
	//}
}


void CGameState::DrawPlayer()
{
	//moto->renderEntity(data->window);
}

void CGameState::initEnemy()
{
	data->assets.LoadTexture("explosion", "C:\\Users\\scizz\\source\\repos\\xptdr\\res\\img\\explosion_sprite_sheet.png");
}

void CGameState::deleteEntity(int& i)
{
	if (entityList[i]->getType() == 1)
		enemyNumber--;
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
}




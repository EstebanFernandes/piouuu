#include "CGameState.h"

CGameState::CGameState()
{
}

CGameState::CGameState(GameDataRef _data) 
	: data(_data)
{
	
}

CGameState::CGameState(GameDataRef _data, std::vector<CCharacter>& characters)
	: data(_data)
{
	CPlayer temp;
	for (int i = 0; i < characters.size(); i++)
	{
		temp.updateStates(characters[i]);
		players.push_back(temp);
	}
}


CGameState::~CGameState()
{
	players.clear();
}
void CGameState::initPlayer()
{
	data->assets.LoadSFX("bulletSound", "res\\sfx\\Piou.wav");
	data->assets.LoadTexture("bulletImage", "res\\img\\characters\\bulletImage.png");
	data->assets.LoadTexture("bulletSecond", "res\\img\\characters\\bullet_Second.png");
	data->assets.LoadTexture("explosionPlayer", "res\\img\\characters\\explosionPlayer.png");
	data->assets.LoadTexture("bulletImageRancoeur", "res\\img\\characters\\bulletRancoeur.png");
	data->assets.LoadTexture("bulletImageGolden", "res\\img\\bullet_Golden.png");
	data->assets.LoadTexture("R2D2", "res\\img\\characters\\Droide2.png");
	data->assets.LoadTexture("logonormal", "res\\img\\characters\\logonormal2.png");
	data->assets.LoadSFX("planeSound", "res\\sfx\\plane.mp3");
	data->assets.LoadTexture("muzzleFlash", "res\\img\\muzzleFlash.png");
	data->assets.LoadTexture("buttonArcade", "res\\img\\UI\\boutonenfonce2.png");
	int numero = 1;
	for (auto i = players.begin(); i != players.end(); i++)
	{
		i->setAssets(&(data->assets));
		i->updateMisc();
		i->setNumero(numero);
		i->setTouche(&inputOfPlayers[numero - 1]);
		numero++;
	}
	if (numero == 2)//Qu'un joueur
	{
		players.begin()->setPositionEntity(data->assets.sCREEN_WIDTH * 0.2f, data->assets.sCREEN_HEIGHT * 0.5f);
		players.begin()->setReviveness(false);
	}
	else {
		float height = 0.4f;
		float width = 0.2f;
		for (auto i = players.begin(); i != players.end(); i++)
		{
			i->setPositionEntity(data->assets.sCREEN_WIDTH * width, data->assets.sCREEN_HEIGHT * height);
			width += 0.05f;
			height += 0.2f;
		}
	}
}

void CGameState::initBackground()
{
	sf::Vector2u TextureSize;  //Added to store texture size.
	sf::Vector2u WindowSize;   //Added to store window size.
	BG1.setAssets(&(data->assets));
	BG1.setWindowSize(data->window.getSize());
	sf::Sprite t1,t2,t3,t4,t5;
	sf::Vector2i zero(0, 0);
	CAnimation anim(NULL, zero, sf::Vector2i(1, 6), 0.f, 2);
	anim.changeIntRect(zero, sf::IntRect(0, 0, 34, 7));
	zero.y++;
	anim.changeIntRect(zero, sf::IntRect(0, 9, 117, 15));
	zero.y++;
	anim.changeIntRect(zero, sf::IntRect(0, 26, 43, 10));
	zero.y++;
	anim.changeIntRect(zero, sf::IntRect(0, 38, 50, 10));
	zero.y++;
	anim.changeIntRect(zero, sf::IntRect(0, 50, 97, 14));
	zero.y++;
	anim.changeIntRect(zero, sf::IntRect(0, 66, 61, 12));
	data->assets.LoadTexture("nuages",
		"res\\img\\layers\\nuages.png");
	data->assets.LoadTexture("sun",
		"res\\img\\layers\\soleil.png");
	data->assets.LoadTexture("background", 
		"res\\img\\layers\\fondvide.png");

	TextureSize = data->assets.GetTexture("background").getSize(); //Get size of texture.
	WindowSize = data->window.getSize();

	float ScaleX = (float)(WindowSize.x*1.1f) / TextureSize.x;
	float ScaleY = (float)WindowSize.y / TextureSize.y;     //Calculate scale.

	t1.setTexture(data->assets.GetTexture("background"));
	t1.setScale(ScaleX, ScaleY);      //Set scale. 
	BG1.addLayer(t1, "background", 0.f,CBackground::background);
	//Soleil
	sf::Sprite soleil(data->assets.GetTexture("sun"));
	soleil.setScale(2.f, 2.f);
	BG1.addLayer(soleil, "sun", 0.0f, CBackground::sun);
	BG1.addClouds("nuages", "nuage", 0.25f, anim);
	data->assets.LoadTexture("firstLayer", 
		"res\\img\\layers\\parallax-mountain-montain-far.png");
	ellipseForSun = EllipseShape(sf::Vector2f((float)data->assets.sCREEN_WIDTH / 2.f, (float)data->assets.sCREEN_HEIGHT ));
	ellipseForSun.setPointCount(600);
	ellipseForSun.setOrigin(ellipseForSun.getLocalBounds().width / 2.f, ellipseForSun.getLocalBounds().height / 2.f);
	ellipseForSun.setPosition(ellipseForSun.getRadius());
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
	gameClockText.setFont(data->assets.GetFont("Nouvelle"));
	gameTime.Zero;
	updateBackground(0.f);
}
void CGameState::STEInit()
{
	*enemyNumber = 0;
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
		for (auto i = players.begin(); i != players.end(); i++)
			i->PLYupdateMovement(event);
		if (sf::Event::Closed == event.type)
			data->window.close();
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape)
			{
				data->machine.AddState(StateRef(new CGameMenu(data,this)), false);
				hasChanges = true;
			}
		}
	}

}

void CGameState::addEnemy(std::string enemyName)
{
	enemyInfo e;
	e.spawnSide = "droite";
	e.isAim = true;
	if (enemyName == "roaming") {
		RoamingEnemy* enemy = new RoamingEnemy(&(data->assets));
		entityList.push_back(enemy);
		(*enemyNumber)++;
	}
	else if (enemyName == "shooter") {
		ShootingEnemy* enemy = new ShootingEnemy(&(data->assets), e);
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
		enemyInfo info_;
		info_.spawnSide = "gauche";
		BomberEnemy* enemy = new BomberEnemy(&(data->assets), info_);
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
		RusherEnemy* enemy = new RusherEnemy(&(data->assets));
		entityList.push_back(enemy);
		(*enemyNumber)++;
	}
	else if (enemyName == "boss") {
		//Boss* enemy = new Boss(&(data->assets), &player1, &entityList, enemyNumber);
		//enemy->setBulletStorage(&bulletstorage);
		//entityList.push_back(enemy);
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
	for (auto i = players.begin(); i != players.end(); i++)
	{
		i->updateEntity(delta);
		if (i->getMainWeapon()->typeTir == typeAim::autoAim && i->seekForTarget)
		{
			CMob* cible = nearEnemy(&(*i));
			i->getMainWeapon()->changeTarget(cible);
			i->seekForTarget = false;
		}
	}
	size_t temp = entityList.size();
	int previousMax = (int)temp;
	for (int i = 0; i < temp; i++)
	{
		for (auto player = players.begin(); player != players.end(); player++)
			entityList[i]->updatewPlayer(delta, (*player));
		if (entityList[i]->needDelete == true)
		{
			deleteEntity(i);
			i--;
			temp--;
		}
		else
			entityList[i]->updateEntity(delta);
	}
	if (players.begin()->needDelete && players.back().needDelete)
		GameOver();

	//Clock updates
	updateClock();
	updateXpPlayers();
}


void CGameState::updateBackground(float delta)
{
	BG1.updateCBackground(delta);
	indexForSun = static_cast<int>(floor(time/2.5f)+ (int)ellipseForSun.getPointCount()/2 + (int)ellipseForSun.getPointCount() / 4)% (int)ellipseForSun.getPointCount();
	BG1.getLayer("sun").sprite.setPosition(ellipseForSun.getPoint(indexForSun));
}

void CGameState::deleteEntity(int i)
{
	/*if (entityList[i]->getType() == 1) {
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
	}*/
	delete entityList.at(i);
	entityList.erase(entityList.begin() + i);
	if (i != 0)
		i--;
}

void CGameState::updateTime()
{
	time = (gameTime.asSeconds() + clock.getElapsedTime().asSeconds()) * 100.f;
	time = ceil(time);
	time = time / 100.f;
}


void CGameState::renderBackground(sf::RenderTarget& target)
{
	BG1.renderBackground(target);
}

void CGameState::STEDraw(float delta)
{
	drawOnTarget(data->window,delta);
}

void CGameState::drawOnTarget(sf::RenderTarget& target, float interpolation)
{
	renderBackground(target);
	for (auto i = players.begin(); i != players.end(); i++)
		i->renderEntity(target);
	for (int i = 0; i < entityList.size(); i++)
	{
		entityList[i]->renderEntity(target);
	}

	target.setView(data->window.getDefaultView());
	//Permet de remettre la vue par d�faut et donc pas de soucis sur la suite
	for (int i = 0; i < entityList.size(); i++)
	{
		entityList[i]->renderUI(target);
	}
	for (auto i = players.begin(); i != players.end(); i++)
	{
		i->renderUI(target);
	}
	target.draw(uitext);
	target.draw(gameClockText);
}

void CGameState::STEResume()
{
	data->assets.DeleteTexture("pauseScreen");
	clock.restart();
	CESTBON = false;
	for (auto i = players.begin(); i != players.end(); i++)
	{
		i->resetMovement();
		i->playSound();
	}

}
void CGameState::updateClock()
{
	updateTime();
	std::string i = std::to_string(time);
	size_t r = i.find('.') + 3;
	i.erase(r, i.size() - r);
	size_t ti = gameClockText.getString().getSize();
	gameClockText.setString(i);
	if (ti != i.size())
		gameClockText.setPosition(sf::Vector2f(data->assets.sCREEN_WIDTH / 2 - gameClockText.getGlobalBounds().width / 2, 20.f));

}
void CGameState::updateXpPlayers()
{
	bool wantToLevelUpOne = true
		, wantToLevelUpTwo = (players.size() == 1) ? false : true;
	for (auto player = players.begin(); player != players.end(); player++)
	{
		if (player == players.begin())
		{
			if (!player->wantToLevelUp)
				wantToLevelUpOne = false;
		}
		else {
			if (!player->wantToLevelUp)
				wantToLevelUpTwo = false;
		}
	}
	if (wantToLevelUpOne && wantToLevelUpTwo && players.size() == 2)
		data->machine.AddState(StateRef(new CUpgradeState(data, &players, &US, this)), false);
	else if (wantToLevelUpOne)
		data->machine.AddState(StateRef(new CUpgradeState(data, &(*players.begin()), &US, this)), false);
	else if (players.size() == 2 && wantToLevelUpTwo)
		data->machine.AddState(StateRef(new CUpgradeState(data, &players.back(), &US, this)), false);

}
void CGameState::afterTransi()
{
	clock.restart();
	gameTime = sf::Time::Zero;
	updateClock();
}
/// <summary>
/// Fonction qui renvoie l'ennemi le plus pr�s de l'entit� pass� en param�tre
/// 
/// </summary>
/// <param name="player"></param>
/// <returns>NULL si d�couvert(lol),sinon un pointer vers l'ennemi</returns>
CMob* CGameState::nearEnemy(CMob* player)
{
	CMob* nearEnemy = NULL;
	float bestDistanceNow = 5000.f;
	for (int i = 0; i < entityList.size(); i++)
	{
		if (entityList[i]->getType() == CEntity::Enemy)
		{

			float curEntityDistance  = utilities::getDistancefrom2Pos(player->getPosition(), entityList[i]->getPosition());
			if (bestDistanceNow > curEntityDistance)
			{
				bestDistanceNow = curEntityDistance;
				nearEnemy = entityList[i];
			}
		}
	}
	return nearEnemy;
}

CMob* CGameState::nearestPlayer(sf::Vector2f pos)
{
	float max = 2000.f;
	CMob* target = NULL;
	for (auto player = players.begin(); player != players.end(); player++)
	{
		float distance = utilities::getDistancefrom2Pos(pos, player->getSprite().getPosition());
		if (distance < max&&player->isDead==false)
		{
			max = distance;
			target = &(*player);
		}
	}
	return target;
}

GameDataRef CGameState::getData()
{
	return data;
}

void CGameState::STEPause()
{
	gameTime += clock.getElapsedTime();
	for (auto player = players.begin(); player != players.end(); player++)
	{
		player->playSound(false);
	}
}




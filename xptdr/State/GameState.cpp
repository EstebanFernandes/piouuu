#include "GameState.h"
#include"UpgradeState.h"
StateNS::GameState::GameState()
{
}

StateNS::GameState::GameState(GameDataRef _data)
	: data(_data)
{
	
}

StateNS::GameState::GameState(GameDataRef _data, std::vector<Character>& characters)
	: data(_data)
{
	Player temp;
	for (int i = 0; i < characters.size(); i++)
	{
		temp.updateStates(characters[i]);
		players.push_back(temp);
	}
}


StateNS::GameState::~GameState()
{
	players.clear();
}
void StateNS::GameState::initPlayer()
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
	data->assets.LoadTexture("beginLaser", "res\\img\\laser\\beginLaser.png");
	data->assets.LoadTexture("fullLaser", "res\\img\\laser\\fullLaser.png");
	data->assets.GetTexture("fullLaser").setRepeated(true);
	
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
		players.begin()->setPositionEntity(Engine::SCREEN_WIDTH * 0.2f, Engine::SCREEN_HEIGHT * 0.5f);
		players.begin()->setReviveness(false);
	}
	else {
		float height = 0.4f;
		float width = 0.2f;
		for (auto i = players.begin(); i != players.end(); i++)
		{
			i->setPositionEntity(Engine::SCREEN_WIDTH * width, Engine::SCREEN_HEIGHT * height);
			width += 0.05f;
			height += 0.2f;
		}
	}
}

void StateNS::GameState::initBackground()
{
	sf::Vector2u TextureSize;  //Added to store texture size.
	sf::Vector2u WindowSize;   //Added to store window size.
	BG1.setAssets(&(data->assets));
	BG1.setWindowSize(data->window.getSize());
	sf::Sprite t1,t2,t3,t4,t5;
	sf::Vector2i zero(0, 0);
	Animation anim(NULL, zero, sf::Vector2i(1, 6), 0.f, 2);
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
	BG1.addLayer(t1, "background", 0.f,Background::backgroundtype);
	//Soleil
	sf::Sprite soleil(data->assets.GetTexture("sun"));
	utilities::centerObject(soleil);
	soleil.setScale(2.f, 2.f);
	soleil.setPosition(0.f, (float)Engine::SCREEN_HEIGHT);
	BG1.addLayer(soleil, "sun", 0.0f, Background::sun);
	BG1.addClouds("nuages", "nuage", 0.25f, anim);
	data->assets.LoadTexture("firstLayer", 
		"res\\img\\layers\\parallax-mountain-montain-far.png");
	ellipseForSun = EllipseShape(sf::Vector2f((float)Engine::SCREEN_WIDTH / 2.f, (float)Engine::SCREEN_HEIGHT ));
	ellipseForSun.setPointCount(600);
	ellipseForSun.setOrigin(ellipseForSun.getLocalBounds().width / 2.f, ellipseForSun.getLocalBounds().height / 2.f);
	ellipseForSun.setPosition(ellipseForSun.getRadius());
	TextureSize = data->assets.GetTexture("firstLayer").getSize(); //Get size of texture.
	WindowSize = data->window.getSize();

	ScaleX = (float)(WindowSize.x * 1.1f) / TextureSize.x;
	ScaleY = (float)WindowSize.y / TextureSize.y;
	t2.setTexture(data->assets.GetTexture("firstLayer")); 
	t2.setScale(ScaleX, ScaleY);      //Set scale. 

	BG1.addLayer(t2, "firstlayer", 0.1f, Background::bot); 
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
	
	//Light shader
	renderTexture.create(data->window.getSize().x, data->window.getSize().y);
	//For the light effect
	shadowMask.create(data->window.getSize().x, data->window.getSize().y);
	lightShader.loadFromFile("shaders/lightFrag.frag", sf::Shader::Fragment);
	lightShader.setUniform("u_resolution", sf::Glsl::Vec2(getEcranBound()));
}

void StateNS::GameState::STEInit()
{
	*enemyNumber = 0;
	initBackground();
	data->assets.stopMusique("MenuPrincipal");
	data->assets.jouerMusique("PartieJour");
	bulletstorage = bulletStorage(&(data->assets));
	entityList.push_back(&bulletstorage);
}

void StateNS::GameState::STEHandleInput(sf::Event& event)
{
	for (auto i = players.begin(); i != players.end(); i++)
		i->PLYupdateMovement(event);
	if (sf::Event::Closed == event.type)
		data->window.close();
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape)
		{
			data->machine.AddState(StateRef(new GameMenu(data,this)), false);
			hasChanges = true;
		}
	}

}

void StateNS::GameState::addEnemy(std::string enemyName)
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

void StateNS::GameState::addPowerUp(sf::Vector2f pos)
{
	entityList.push_back(new PowerUp(pos,&(data->assets)));
}


void StateNS::GameState::STEUpdate(float delta)
{
	updateBackground(delta);
	//Auto aim
	for (auto i = players.begin(); i != players.end(); i++)
	{
		i->updateEntity(delta);
		if (i->getMainWeapon()->typeTir == typeAim::autoAim && i->seekForTarget)
		{
			Mob* cible = nearEnemy(&(*i));
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


void StateNS::GameState::updateBackground(float delta)
{
	BG1.updateBackground(delta);
	updateSun();
}

void StateNS::GameState::updateSun()
{
	indexForSun = static_cast<int>(floor(time) + (int)ellipseForSun.getPointCount() / 2 + (int)ellipseForSun.getPointCount() / 4) % (int)ellipseForSun.getPointCount();
	BG1.getLayer("sun").sprite.setPosition(ellipseForSun.getPoint(indexForSun));
	lightShader.setUniform("lightPoint", utilities::glslCoord(ellipseForSun.getPoint(indexForSun), (float)Engine::SCREEN_HEIGHT));
}

void StateNS::GameState::deleteEntity(int i)
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

void StateNS::GameState::updateTime()
{
	time = (gameTime.asSeconds() + clock.getElapsedTime().asSeconds()) * 100.f;
	time = ceil(time);
	time = time / 100.f;
}


void StateNS::GameState::renderBackground(sf::RenderTarget& target)
{
	BG1.renderBackground(target);
}

void StateNS::GameState::STEDraw(float delta)
{
	drawOnTarget(data->window,delta);
}

void StateNS::GameState::drawOnTarget(sf::RenderTarget& target, float interpolation)
{
	// 1. Dessiner la premi�re couche (background) sur la texture de rendu principale
	renderTexture.clear();
	BG1.drawFirstLayer(renderTexture, interpolation);
	drawOnTargetEntity(renderTexture, interpolation); // Dessiner les entit�s
	renderTexture.display();

	// 2. Dessiner les �l�ments qui bloquent la lumi�re sur la texture de masque d'ombres
	shadowMask.clear(sf::Color::White);
	drawOnTargetEntity(shadowMask, interpolation); // Dessiner les entit�s qui bloquent la lumi�re
	shadowMask.display();

	// 3. Configurer les uniformes du shader
	lightShader.setUniform("texture", renderTexture.getTexture());
	lightShader.setUniform("shadowMask", shadowMask.getTexture());

	spriteRender.setTexture(renderTexture.getTexture());
	target.draw(spriteRender, &lightShader);

	// 5. Dessiner les �l�ments de l'interface utilisateur directement sur la fen�tre
	drawOnTargetUI(target, interpolation);
}

void StateNS::GameState::STEResume()
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
void StateNS::GameState::updateClock()
{
	updateTime();
	std::string i = std::to_string(time);
	size_t r = i.find('.') + 3;
	i.erase(r, i.size() - r);
	size_t ti = gameClockText.getString().getSize();
	gameClockText.setString(i);
	if (ti != i.size())
		gameClockText.setPosition(sf::Vector2f(Engine::SCREEN_WIDTH / 2 - gameClockText.getGlobalBounds().width / 2, 20.f));

}
void StateNS::GameState::updateXpPlayers() {
	bool wantToLevelUpOne = players.front().wantToLevelUp;
	bool wantToLevelUpTwo = (players.size() == 1) ? false : players.back().wantToLevelUp;
	bool twoPUpdate = false;

	if (wantToLevelUpOne || wantToLevelUpTwo) {
		if (wantToLevelUpOne) {
			if (players.size() == 1 || players.back().hasLevelUp || players.back().wantToLevelUp) {
				twoPUpdate = true;
			}
			else {
				data->machine.AddState(StateRef(new UpgradeState(data, &(*players.begin()), &US, this)), false);
			}
		}
		else if (wantToLevelUpTwo) {
			if (players.front().hasLevelUp) {
				twoPUpdate = true;
			}
			else {
				data->machine.AddState(StateRef(new UpgradeState(data, &(players.back()), &US, this)), false);
			}
		}
		if (twoPUpdate) {
			data->machine.AddState(StateRef(new UpgradeState(data, &players, &US, this)), false);
		}
	}
}
void StateNS::GameState::afterTransi()
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
Mob* StateNS::GameState::nearEnemy(Mob* player)
{
	Mob* nearEnemy = NULL;
	float bestDistanceNow = 5000.f;
	for (int i = 0; i < entityList.size(); i++)
	{
		if (entityList[i]->getType() == Entity::EnemyType)
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

Mob* StateNS::GameState::nearestPlayer(sf::Vector2f pos)
{
	float max = 2000.f;
	Mob* target = NULL;
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

GameDataRef StateNS::GameState::getData()
{
	return data;
}

void StateNS::GameState::STEPause()
{
	gameTime += clock.getElapsedTime();
	for (auto player = players.begin(); player != players.end(); player++)
	{
		player->playSound(false);
	}
}



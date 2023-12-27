#include "CPlayer.h"




void CPlayer::setSprite()
{
	getSprite().setScale(0.7f, 0.7f);
	getSprite().setPosition((assets->sCREEN_WIDTH / 4.f) - (getSprite().getGlobalBounds().width/2), (assets->sCREEN_HEIGHT / 2.f) - (getSprite().getGlobalBounds().height/2.f));
}

void CPlayer::initStat()
{
	score = 0;
}

void CPlayer::setAssets(CAssetManager* a)
{
	assets = a;
	BAW.assets = a;
	getSprite().setTexture((*a).GetTexture(name));

	assets->LoadTexture("lifepoint", LIFEPOINTTEXTURE);
	if (isAnimated) anim = CAnimation(getPointerSprite(), sf::IntRect(0, 0, 153, 66), 4, 0.16f);
	initLifeBar();
	setSprite();
}

bool CPlayer::checkGlobalCollisions()
{
	//Top collision and bot collision
	if (getGlobalBounds().top <= 0)
		setPositionEntity(getGlobalBounds().left, 0);
	else if(getGlobalBounds().top + getGlobalBounds().height >= assets->sCREEN_HEIGHT)
		setPositionEntity(getGlobalBounds().left, assets->sCREEN_HEIGHT - getGlobalBounds().height);
	//Left and right collision
	if (getGlobalBounds().left <= 0)
		setPositionEntity(0, getGlobalBounds().top);
	else if (getGlobalBounds().left + getGlobalBounds().width >= assets->sCREEN_WIDTH)
		setPositionEntity(assets->sCREEN_WIDTH - getGlobalBounds().width, getGlobalBounds().top);
	return false;
}

void CPlayer::resetMovement()
{
	isMovingDown = false;
	isMovingLeft = false;
	isMovingRight = false;
	isMovingUp = false;
}

void CPlayer::traitermisc(std::string& misc)
{
	const std::vector<std::string> supportedMisc{ "autoAim","velocUp" ,"doubleTirs1","doubleTirs2","gunshot"};
	int pos = (int)(std::find(supportedMisc.begin(), supportedMisc.end(), misc) - supportedMisc.begin());
	if (pos >= supportedMisc.size()) {
		std::cout << "Rien a �t� trouv�\n";
	}
	else{
		switch (pos)
		{
		case 0:
			//auto aim
			BAW.addBulletMode(true,BAW.autoAim);
			break;
			//Velocity up
		case 1:

			break;
			//doubleTirs1
		case 2:
			BAW.addBulletMode(false, BAW.doubleTirs1);
			break;
			//doubleTirs2
		case 3:
			BAW.addBulletMode(false, BAW.doubleTirs2);
			break;
			//gunshot
		case 4:
			BAW.addBulletMode(false, BAW.gunshotAim);
			break;
		}
			misc.insert(0, "+");
	}
}

void CPlayer::updateMisc()
{
	for (int i = 0; i < specificites.size(); i++)
	{
		traitermisc(specificites[i]);
	}
}

 
CPlayer::CPlayer()
{
	setType(Player);
	initStat();
}

CPlayer::CPlayer(CAssetManager* a)
{
	imageName = "player1Image";
	setType(Player);
	setAssets(a);
}

CPlayer::~CPlayer()
{
}


void CPlayer::initLifeBar()
{
	float lp = 87.f;
	previouslifePoint = maxHealthPoint;
	previousMaxHealth = maxHealthPoint;
	float scaleFactor = 1.f;
	float lifebarwidth = lp * maxHealthPoint;
	if (lifebarwidth >= assets->sCREEN_WIDTH * 0.5f)
	{
		float maxWidthPerPoint = assets->sCREEN_WIDTH * 0.5f / (float)maxHealthPoint;
		scaleFactor = maxWidthPerPoint / lp;
	}
	for (int i = 0; i < maxHealthPoint; i++)
	{
		sf::Sprite temp;
		temp.setTexture(assets->GetTexture("lifepoint"));
		temp.setTextureRect(sf::IntRect(0, 0, (int)lp, 26));
		temp.setScale(scaleFactor, scaleFactor * 2.f);
		temp.setPosition(100.f + i * temp.getGlobalBounds().width , 30.f);
		lifeBar.push_back(temp);
	}
}


void CPlayer::PLYupdateMovement(sf::Event event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed :
		if (event.key.code == sf::Keyboard::Z )
			isMovingUp = true;
		else if(event.key.code == sf::Keyboard::Q)
			isMovingLeft = true;
		else if (event.key.code == sf::Keyboard::S)
			isMovingDown = true;
		else if (event.key.code == sf::Keyboard::D)
			isMovingRight = true;
		break;
	case sf::Event::KeyReleased:
		if (event.key.code == sf::Keyboard::Z)
			isMovingUp = false;
		else if (event.key.code == sf::Keyboard::Q)
			isMovingLeft = false;
		else if (event.key.code == sf::Keyboard::S)
			isMovingDown = false;
		else if (event.key.code == sf::Keyboard::D)
			isMovingRight = false;
		break;
	default:
		break;


	}
}

void CPlayer::updateMovement(float dt)
{
	if (isMovingUp == true)
	{
		moveEntity(0.f, -moveSpeed * dt*60.f);
		if (getAnimated()) {
			anim.setDifferentAnimation(1);
		}
	}
	else if (isAnimated && anim.getCurrentYFrameNumber() == 1) {
		anim.resetAnimation();
	}
		
	if (isMovingDown == true)
	{
		if (isAnimated) {
			anim.setDifferentAnimation(2);
		}
		moveEntity(0.f, moveSpeed * dt * 60.f);
	}
	else if (isAnimated && anim.getCurrentYFrameNumber() == 2)
		anim.resetAnimation();
		
	if (isMovingLeft == true)
	{
		moveEntity(-moveSpeed * dt * 60.f,0.f);
	}
	if (isMovingRight == true)
	{
		moveEntity(moveSpeed * dt * 60.f, 0.f);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//Si ce temps est trop faible on ne fait rien, 
		if (bulletClock.getElapsedTime().asSeconds() >= 1.f / attackSpeed) {
			sf::Vector2f r(getSprite().getPosition().x + getSprite().getGlobalBounds().width, getSprite().getPosition().y + (getSprite().getGlobalBounds().height / 2));
				if (BAW.typeBalle == 3)
					seekForTarget = true;
				if (BAW.typeTir == pow(2,(int)BAW.gunshotAim))
					BAW.setGunShotDistance(250.f);
				BAW.iNeedMoreBullets(r, damagePerBullet,bulletSpeed);

			// vient juste le restart le timer � la fin 
			bulletClock.restart();
		}
	}
}




void CPlayer::renderLifeBar(sf::RenderTarget& target)
{
	for (int i = 0; i < lifeBar.size(); i++)
	{
		target.draw(lifeBar[i]);
	}
}

void CPlayer::updateCollision(CEntity& b)
{
	
}
void CPlayer::gainXP(int levelofEntity)
{
	xp += 4 * levelofEntity;
}
void CPlayer::updateLifeBar()
{
	if (previouslifePoint > healthPoint)
	{
		for (int i = healthPoint; i < previouslifePoint; i++)
		{

			lifeBar[i].setTextureRect(sf::IntRect(87, 0, 87, 26));
		}
		previouslifePoint = healthPoint;
		hasBeenHit = false;
	}
	else 
	{
		for (int i = previouslifePoint; i < healthPoint; i++)
		{

			lifeBar[i].setTextureRect(sf::IntRect(0, 0, 87, 26));
		}
		previouslifePoint = healthPoint;
		hasBeenHit = false;
	}
	if (healthPoint <= 0)
		needDelete = true;
}
void CPlayer::updateEntity(float dt)
{
	updateMovement(dt);
	checkGlobalCollisions();
	updateFx();
	updateLifeBar();
 	if (xp >= maxXp&& hasLevelUp==false)
	{
		level++;
		xp -= maxXp;
		maxXp += 10;
		hasLevelUp = true;
	}
	BAW.updateEntity(dt);
}

void CPlayer::renderEntity(sf::RenderTarget& target)
{
	target.draw(getSprite());
	renderLifeBar(target);
	BAW.renderEntity(target);
}


void CPlayer::updateFx()
{
	if (getAnimated()) {
		anim.updateAnimation();
	}
	if (hasBeenHit)
	{
		hittype = true;
		getSprite().setColor(sf::Color::Red);
		isInvulnerable = true;
		std::cout << "debut invu" << std::endl;
		hitClock.restart();
	}
	if (hittype)
	{
		if (hitClock.getElapsedTime().asSeconds() >= 0.5f)
		{
			getSprite().setColor(sf::Color::White);
			hitClock.restart();
			isInvulnerable = false;
			std::cout << "fin invu" << std::endl;
			hittype = false;
			hasBeenHit = false;
		}
	}
}


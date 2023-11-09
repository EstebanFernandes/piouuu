#include "CPlayer.h"




void CPlayer::setSprite()
{
	getSprite().setScale(0.7f, 0.7f);
	getSprite().setPosition((assets->sCREEN_WIDTH / 4) - (getSprite().getGlobalBounds().width/2), (assets->sCREEN_HEIGHT / 2) - (getSprite().getGlobalBounds().height/2));
}

void CPlayer::initStat()
{
	moveSpeed = 0.5f;
	maxHealthPoint = 20;
	healthPoint = maxHealthPoint;
	xp = 0;
	maxXp = 10;
	damagePerBullet = 5;
	attackSpeed = 8.f;
}

void CPlayer::setAssets(CAssetManager* a)
{
	assets = a;
	BAW.assets = a;
	//setTexture(getName(), GAME_SPACESHIP_FILEPATH);
	getSprite().setTexture((*a).GetTexture(getName()));

	assets->LoadTexture("lifepoint", LIFEPOINTTEXTURE);
	if (getAnimated()) anim = CAnimation(getPointerSprite(), sf::IntRect(0, 0, 153, 66), 4, 0.16f);
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
	else if (getAnimated() && anim.getCurrentYFrameNumber() == 1) {
		anim.resetAnimation();
	}
		
	if (isMovingDown == true)
	{
		if (getAnimated()) {
			anim.setDifferentAnimation(2);
		}
		moveEntity(0.f, moveSpeed * dt * 60.f);
	}
	else if (getAnimated() && anim.getCurrentYFrameNumber() == 2)
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
		//Si se temps est trop faible on ne fait rien, 
		if (bulletClock.getElapsedTime().asSeconds() >= 1.f / attackSpeed) {
			sf::Vector2f r(getSprite().getPosition().x + getSprite().getGlobalBounds().width, getSprite().getPosition().y + (getSprite().getGlobalBounds().height / 2));
			BAW.iNeedMoreBullets(r, damagePerBullet);
			// vient juste le restart le timer à la fin 
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
	/*switch (b.getType())
	{
	case Enemy:
		if (checkCollisions(b))
		{
			if(b.isDead==false)
			{
				if (b.isHitting == false)
				{
					reduceHP(b.getDamage());
					b.isHitting = true;
				}
			}
			else if (isHitting == true)
				b.isHitting = false;
		}
		break;
			
	case EnemyFire:
		if (checkCollisions(b))
		{
			b.needDelete = true;
			reduceHP(b.getDamage());
		}
		break;
	case PowerUp:
		if (checkCollisions(b))
			b.needDelete = true;
	}*/
}
void CPlayer::gainXP(int levelofEntity)
{
	xp += 3 + 3 * levelofEntity;
	if (xp >= maxXp)
	{
		level++;
		xp = 0;
		maxXp += 10;
	}
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
void CPlayer::iNeedMoreBullet()
{
	BAW.iNeedMoreBullets(getSprite().getPosition(),damagePerBullet,bulletSpeed);
}
void CPlayer::updateEntity(float dt)
{
	updateMovement(dt);
	checkGlobalCollisions();
		updateFx();
	updateLifeBar();
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
		if (hitClock.getElapsedTime().asSeconds() >= 0.5f)
		{
			hittype = true;
			getSprite().setColor(sf::Color::Red);
			hitClock.restart();
		}
	}
	if (hittype)
	{
		if (hitClock.getElapsedTime().asSeconds() >= 0.5f)
		{
			getSprite().setColor(sf::Color::White);
			hitClock.restart();
			hittype = false;
		}
	}
}


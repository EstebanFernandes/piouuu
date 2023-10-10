#include "CPlayer.h"




void CPlayer::setSprite()
{
	getSprite().setScale(0.3f, 0.3f);
	getSprite().setPosition((SCREEN_WIDTH / 4) - (getSprite().getGlobalBounds().width/2), (SCREEN_HEIGHT / 2) - (getSprite().getGlobalBounds().height/2));
}

void CPlayer::initStat()
{
	maxhealth = 20;
	iENTLifePoint = maxhealth;
	xp = 0;
	maxXp = 10;
	damagePerBullet = 5;
}

void CPlayer::setAssets(CAssetManager* a)
{
	assets = a;
	BAW.assets = a;
	setTexture("spacecraftImage", GAME_SPACESHIP_FILEPATH);
	assets->LoadTexture("lifepoint", LIFEPOINTTEXTURE);
	initLifeBar();
	setSprite();
}

bool CPlayer::checkGlobalCollisions()
{
	//Top collision and bot collision
	if (getGlobalBounds().top <= 0)
		setPositionEntity(getGlobalBounds().left, 0);
	else if(getGlobalBounds().top + getGlobalBounds().height >= SCREEN_HEIGHT)
		setPositionEntity(getGlobalBounds().left, SCREEN_HEIGHT - getGlobalBounds().height);
	//Left and right collision
	if (getGlobalBounds().left <= 0)
		setPositionEntity(0, getGlobalBounds().top);
	else if (getGlobalBounds().left + getGlobalBounds().width >= SCREEN_WIDTH)
		setPositionEntity(SCREEN_WIDTH - getGlobalBounds().width, getGlobalBounds().top);
	return false;
}

 
CPlayer::CPlayer()
{
	setType(Player);
	initStat();
}

CPlayer::CPlayer(CAssetManager* a)
{
	setType(Player);
	setAssets(a);
}

CPlayer::~CPlayer()
{
}

void CPlayer::initLifeBar()
{
	float lp = 87.f;
	previouslifePoint = maxhealth;
	previousMaxHealth = maxhealth;
	float scaleFactor = 1.f;
	float lifebarwidth = lp * maxhealth;
	if (lifebarwidth >= SCREEN_WIDTH * 0.5f)
	{
		float maxWidthPerPoint = SCREEN_WIDTH * 0.5f / maxhealth;
		scaleFactor = maxWidthPerPoint / lp;
	}
	for (int i = 0; i < maxhealth; i++)
	{
		sf::Sprite temp;
		temp.setTexture(assets->GetTexture("lifepoint"));
		temp.setTextureRect(sf::IntRect(0, 0, (int)lp, 26));
		temp.setScale(scaleFactor, scaleFactor * 2.f);
		temp.setPosition(100.f + i * temp.getGlobalBounds().width , 30.f);
		lifeBar.push_back(temp);
	}
}


void CPlayer::PLYupdateMovement(float dt)
{
		if (sf::Keyboard::isKeyPressed( sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up ))
		{
			moveEntity(0.f, -playerSpeed*dt * 60.f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			moveEntity(0.f, playerSpeed*dt * 60.f);//move tout court c'est la fonction pour déplacer le perso, et la fonction move lié au sprite ça déplace
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			moveEntity(-playerSpeed*dt* 60.f, 0.f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			moveEntity(playerSpeed*dt* 60.f, 0.f);//move tout court c'est la fonction pour déplacer le perso, et la fonction move lié au sprite ça déplace
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			// cooldown enregistre le temps depuis la dernière balle envoyé
			bulletCooldown = bulletClock.getElapsedTime();
			//Si se temps est trop faible on ne fait rien, 
			if (bulletCooldown.asSeconds() >= 0.12f) {
				sf::Vector2f r(getSprite().getPosition().x + getSprite().getGlobalBounds().width, getSprite().getPosition().y + (getSprite().getGlobalBounds().height / 2));
				BAW.iNeedMoreBullets(r,damagePerBullet);
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

void CPlayer::updateCollision(CEntity1& b)
{
	switch (b.getType())
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
	}
}
void CPlayer::gainXP(int levelofEntity)
{
	xp += 3 + 3 * levelofEntity;
	if (xp >= maxXp)
	{
		setLevel(getLevel()+1);
		xp = 0;
		maxXp += 10;
	}
}
void CPlayer::updateLifeBar()
{
	if (previouslifePoint > iENTLifePoint)
	{
		for (int i = iENTLifePoint; i < previouslifePoint; i++)
		{

			lifeBar[i].setTextureRect(sf::IntRect(87, 0, 87, 26));
		}
		previouslifePoint = iENTLifePoint;
		hasBeenHit = false;
	}
	else 
	{
		for (int i = previouslifePoint; i < iENTLifePoint; i++)
		{

			lifeBar[i].setTextureRect(sf::IntRect(0, 0, 87, 26));
		}
		previouslifePoint = iENTLifePoint;
		hasBeenHit = false;
	}
	if (iENTLifePoint <= 0)
		needDelete = true;
}
void CPlayer::iNeedMoreBullet()
{
	BAW.iNeedMoreBullets(getSprite().getPosition(),damagePerBullet);
}
void CPlayer::updateEntity(float dt)
{
	checkGlobalCollisions();
	PLYupdateMovement(dt);
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


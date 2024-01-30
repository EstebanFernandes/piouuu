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
	mainWeapon = new CGunslinger();
	mainWeapon->assets = a;
	assets->addSFX("bulletSound", &BAW.bulletSound);
	setTexture(name);

	if (isAnimated) anim = CAnimation(getPointerSprite(), sf::IntRect(0, 0, 153, 66), 4, 0.16f);
	std::string nameImage;
	if (name.find("Rancoeur") != std::string::npos)
		BAW.setBulletAsset("bulletImageRancoeur");
	initLifeBar();
	setSprite();
}

bool CPlayer::checkGlobalCollisions()
{
	sf::FloatRect currentBounds = getGlobalBounds();
	sf::FloatRect nextBounds = currentBounds;
	nextBounds.left += currentBounds.width / 2.f;
	nextBounds.top += currentBounds.height / 2.f;
	//Top collision and bot collision

	if (currentBounds.top <= 0)
		setPositionEntity(nextBounds.left, currentBounds.height/2.f);
	else if(currentBounds.top + currentBounds.height >= assets->sCREEN_HEIGHT)
		setPositionEntity(nextBounds.left, assets->sCREEN_HEIGHT - currentBounds.height/2.f);
	//Left and right collision

	if (currentBounds.left <= 0)
		setPositionEntity(currentBounds.width/2.f, nextBounds.top);
	else if (currentBounds.left + currentBounds.width >= assets->sCREEN_WIDTH)
		setPositionEntity(assets->sCREEN_WIDTH - currentBounds.width/2.f, nextBounds.top);
	return false;
}

void CPlayer::resetMovement()
{
	isMovingDown = false;
	isMovingLeft = false;
	isMovingRight = false;
	isMovingUp = false;
}

Weapon* CPlayer::getMainWeapon()
{
	return mainWeapon;
}

void CPlayer::setMainWeapon(Weapon* weaponParam)
{
	delete mainWeapon;
	mainWeapon = weaponParam;
}

Weapon* CPlayer::getSecondaryWeapon()
{
	return secondaryWeapon;
}

void CPlayer::setSecondaryWeapon(Weapon* weaponParam)
{
	delete secondaryWeapon;
	secondaryWeapon = weaponParam;
}

void CPlayer::traitermisc(std::string& misc)
{
	const std::vector<std::string> supportedMisc{ "autoAim","velocUp" ,"doubleTirs1","doubleTirs2","gunshot","dot", "laser" };
	int pos = (int)(std::find(supportedMisc.begin(), supportedMisc.end(), misc) - supportedMisc.begin());
	if (pos >= supportedMisc.size()) {
		std::cout << "Rien a �t� trouv�\n";
	}
	else{
		switch (pos)
		{
		case 0:
			//auto aim
			BAW.addShootType(BAW.autoAim);
			break;
			//Velocity up
		case 1:

			break;
			//doubleTirs1
		case 2:
			BAW.addShootType(BAW.doubleTirs1);
			break;
			//doubleTirs2
		case 3:
			BAW.addShootType(BAW.doubleTirs2);
			break;
			//gunshot
		case 4:
			BAW.addShootType(BAW.gunshotAim);
			BAW.setGunShotDistance(250.f);
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

void CPlayer::iNeedMoreBullet()
{
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
	delete mainWeapon;
	delete secondaryWeapon;
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
		if (event.key.code == sf::Keyboard::Z)
			isMovingUp = true;
		else if (event.key.code == sf::Keyboard::Q)
			isMovingLeft = true;
		else if (event.key.code == sf::Keyboard::S)
			isMovingDown = true;
		else if (event.key.code == sf::Keyboard::D)
			isMovingRight = true;
		if (event.key.code == sf::Keyboard::V && !lasers.isLaserActive())
			lasers.changeActivity();
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
		if (event.key.code == sf::Keyboard::V && lasers.isLaserActive())
			lasers.changeActivity();
		break;
	default:
		break;


	}
}

void CPlayer::updateMovement(float dt)
{
	sf::Vector2f direction;
	if (isMovingUp)
		direction.y -= 1.f;
	if (isMovingDown)
		direction.y += 1.f;
	if (isMovingLeft)
		direction.x -= 1.f;
	if (isMovingRight)
		direction.x += 1.f;
	if (direction.y == 1.f)
		anim.setDifferentAnimation(2);
	else if (direction.y == -1.f)
		anim.setDifferentAnimation(1);
	else
		anim.resetAnimation();
	direction = direction * moveSpeed * dt * 60.f;
	moveEntity(direction.x, direction.y);
	//if (isMovingUp == true)
	//{
	//	moveEntity(0.f, -moveSpeed * dt*60.f);
	//	if (getAnimated()) {
	//		anim.setDifferentAnimation(1);
	//	}
	//}
	//else if (isAnimated && anim.getCurrentYFrameNumber() == 1) {
	//	anim.resetAnimation();
	//}
	//	
	/*if (isMovingDown == true)
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
	}*/
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//Si ce temps est trop faible on ne fait rien, 
		if (bulletClock.getElapsedTime().asSeconds() >= 1.f / attackSpeed) {
			sf::Vector2f nezdeLavion(
				getSprite().getPosition().x + getGlobalBounds().width/2.f,
				getSprite().getPosition().y );
				if (BAW.typeTir == BAW.autoAim)
					seekForTarget = true;
				BAW.iNeedMoreBullets(nezdeLavion);

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


void CPlayer::gainXP(int levelofEntity)
{
	xp += 4 * levelofEntity;
}
void CPlayer::updateLifeBar()
{
	if (previouslifePoint > healthPoint)
	{
		for (int i = (int)healthPoint; i < previouslifePoint; i++)
		{

			lifeBar[i].setTextureRect(sf::IntRect(87, 0, 87, 26));
		}
		previouslifePoint = healthPoint;
		hasBeenHit = false;
	}
	else 
	{
		for (int i = (int)previouslifePoint; i < healthPoint; i++)
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
	updateBuff(dt);
	updateLifeBar();
 	if (xp >= maxXp&& hasLevelUp==false)
	{
		level++;
		xp -= maxXp;
		maxXp += 10;
		hasLevelUp = true;
	}
	mainWeapon->updateWeapon(dt);

	//tempn on update le laser
	sf::Vector2f laserPos;
	laserPos.x = getSprite().getPosition().x + getSprite().getGlobalBounds().width / 2.f;
	laserPos.y = getSprite().getPosition().y;
	lasers.updateLasers(dt, laserPos, assets->sCREEN_WIDTH);
}

void CPlayer::renderEntity(sf::RenderTarget& target)
{
	target.draw(getSprite());
	renderLifeBar(target);
	mainWeapon->renderWeapon(target);
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


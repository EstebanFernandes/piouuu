#include "RusherEnemy.h"

RusherEnemy::RusherEnemy(CAssetManager* assetParam)
{
	initEnnemy(assetParam,info,"rusher");
	info.pos.x = assets->sCREEN_WIDTH * 0.95f;
	assets->addSFX("enemyRush", &fxRush);
	anim = CAnimation(getPointerSprite(), sf::IntRect(0, 0, 73, 86), 1, -1.f);
	anim.pxbetFrames = 2;
	setMoveSpeed(5.f);
	getSprite().setScale(1.5f, 1.5f);
	setSprite();
	direction = sf::Vector2f(-1.f, 0.f);
	target = NULL;
	info.isAim = true;
	if (info.isAim)
	{
		baseColor= sf::Color::Black;
		getSprite().setColor(baseColor);
	}
}

RusherEnemy::RusherEnemy(CAssetManager* assets, CCharacter stat, enemyInfo info_)
	:RusherEnemy(assets)
{
	setCharacterStats(stat);
	info_.scale = info.scale;
	info = info_;
	if (info.isAim)
	{
		getSprite().setColor(sf::Color::Black);
	}
}


RusherEnemy::~RusherEnemy()
{
	assets->deleteSound(fxRush);
}

void RusherEnemy::updateMovement(float delta)
{
	if (checkGlobalCollisions() && isPositionated)
		needDelete = true;
	updateLifeBar();
	// On avance pour se placer ou si il est l'heure de rush
	if((onAvance == true && !isPositionated) || isRushing)
	{
		sf::Vector2f avance = direction * moveSpeed * delta;
		moveEntity(avance);
	}
	if (!isPositionated && onestPose() ) {
		isPositionated = true;
		colorSwitchClock.restart();
	}
}

void RusherEnemy::initDirection(CMob* target_)
{
	target = target_;
	if (target == NULL)
	{
		CEnemy::initDirection();
	}
	else {
		baseColor = sf::Color(232,118,118,122);
		getSprite().setColor(baseColor);
	}
	direction = utilities::dirAtoB(spawnPos, info.pos);
}

void RusherEnemy::updateEntity(float delta)
{
	CEnemy::updateEntity(delta);
	updateAnim();
	if (isPositionated && counter < 3 && isRed == false && colorSwitchClock.getElapsedTime().asSeconds() >= dureeTotale/3.f) {
		isRed = true;
		counter++;
		dureePasseTotale += colorSwitchClock.getElapsedTime();
		colorSwitchClock.restart();
		getSprite().setColor(sf::Color::Red);
		redColorSwitchClock.restart();
		if(counter==3)
		{
			if (info.isAim)
			{
				seekForTarget = true;
			}
		}
	}
	else if (isRed == true && redColorSwitchClock.getElapsedTime().asSeconds() >= 0.5f) {
		getSprite().setColor(baseColor);
		isRed = false;
	}
	else if (isRushing==false&& counter == 3 && colorSwitchClock.getElapsedTime().asSeconds() >= dureeTotale/3.f) {
		setMoveSpeed(60.f);
		isRushing = true;
		if(fxRush->getStatus()== fxRush->Stopped)//  ca permet de s'assurer que le son n'est joué qu'une fois
		{
			if (target != NULL)
			{
				direction = utilities::dirAtoB(getSprite().getPosition(), target->getSprite().getPosition());
			}
			else
				direction = info.direction;
				if (isSpriteFlip())
					setRotation(utilities::getAngleFromDirection(direction) + 180.f);
				else
					setRotation(utilities::getAngleFromDirection(direction));
			fxRush->play();
		}
	}
}

void RusherEnemy::updateAnim()
{
	if (isRushing == false)
	{
		if ((colorSwitchClock.getElapsedTime() + dureePasseTotale).asSeconds() >= (dureeTotale / 5.f) * (counterAnim + 1))
		{
			if(counterAnim>5&&counterAnim%2==0)//Si on est pair
			{
				counterAnim++;
				anim.setcurrentXFrameNumber(5);
			}
			else if (counterAnim > 5)
			{
				counterAnim++;
				anim.setcurrentXFrameNumber(4);
			}
			else
				anim.setcurrentXFrameNumber(counterAnim++);
		}
	}
	else {
		if ((colorSwitchClock.getElapsedTime() + dureePasseTotale).asSeconds() >= (0.5f) * (counterAnim + 1))
		{
			if (counterAnim % 2 == 0)//Si on est pair
			{
				counterAnim++;
				anim.setcurrentXFrameNumber(5);
			}
			else 
			{
				counterAnim++;
				anim.setcurrentXFrameNumber(4);
			}
		}
	}
}

#include "RusherEnemy.h"

RusherEnemy::RusherEnemy(AssetManager* assetParam)
{
	initEnnemy(assetParam,info,"rusher");
	info.pos.x = Engine::SCREEN_WIDTH * 0.95f;
	assets->addSFX("enemyRush", &fxRush);
	anim = Animation(getPointerSprite(), sf::Vector2i( 73, 86),6, -1.f, 2);
	setMoveSpeed(5.f);
	getSprite().setScale(1.5f, 1.5f);
	setSprite();
	direction = sf::Vector2f(-1.f, 0.f);
	target = NULL;
	info.isAim = true;
}

RusherEnemy::RusherEnemy(AssetManager* assets, Character stat, enemyInfo info_)
	
{
	info_.scale = info.scale;
	info = info_;
	setCharacterStats(stat);
	target = NULL;
	setType(EnemyType);
	this->assets = assets;
	Enemy::initAnimation();
	setTexture("rusher");
	getSprite().setScale(info.scale);
	assets->addSFX("enemyRush", &fxRush);
	anim = Animation(getPointerSprite(), sf::Vector2i(73, 86), 6, -1.f, 2);
	getSprite().setScale(info.scale);
	setSprite();
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

void RusherEnemy::initDirection(Mob* target_)
{
	target = target_;
	if (target == NULL)
	{
		Enemy::initDirection();
	}
	direction = utilities::dirAtoB(spawnPos, info.pos);
	setRotation(utilities::getAngleFromDirection(direction)+180.f);
}

void RusherEnemy::updateEntity(float delta)
{
	Enemy::updateEntity(delta);
	if(isPositionated)
		updateAnim();
	if (isPositionated && counter < 3 && isRed == false && colorSwitchClock.getElapsedTime().asSeconds() >= dureeTotale/3.f) {
		isRed = true;
		counter++;
		dureePasseTotale += colorSwitchClock.getElapsedTime();
		colorSwitchClock.restart();
		baseColor = sf::Color::Red;
		getSprite().setColor(baseColor);
		std::cout << "rouge" << std::endl;
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
		baseColor = sf::Color::White;
		std::cout << "blanc" << std::endl;
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

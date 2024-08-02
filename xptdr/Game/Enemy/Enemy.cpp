#include "Enemy.h"


void Enemy::initAnimation()
{
	AssetManager &a = *assets;
	currentFrame = sf::IntRect(274 , 409, 1295, 1925);
	explosionSprite.setTexture(a.GetTexture("explosion"));
	explosionSprite.setTextureRect(currentFrame);
	explosionSprite.setScale(0.1f, 0.1f);
}


void Enemy::initEnnemy(AssetManager* a, enemyInfo info, std::string nameParam)
{
	setType(EnemyType);
	assets = a;
	initStat();
	initAnimation();
	if (nameParam == "")
		imageName = "enemyImage";
	else
		imageName = nameParam;
	setTexture(imageName);
	getSprite().setScale(info.scale);
	setInfo(info);
	setSprite();
}

void Enemy::initEnnemy(AssetManager* a, std::string nameParam)
{//DEPRECATED
	setType(EnemyType);
	assets = a;
	if (nameParam == "")
		imageName = "enemyImage";
	else
		imageName = nameParam;
	setTexture(imageName);
	flipSprite();
	getSprite().setScale(0.2f, 0.2f);
	initAnimation();
	initStat();
	setSprite();
}

void Enemy::initEnnemy(AssetManager* a, std::string nameParam, sf::Vector2f scale)
{
	//DEPRECATED
	setType(EnemyType);
	assets = a;
	enemyName = nameParam;
	setTexture(enemyName);
	getSprite().setScale(scale);
	initAnimation();
	initStat();
	setSprite();
}



void Enemy::setSprite()
{
	setLifeBar();
	setPositionEntity(spawnPos.x  , (float)spawnPos.y);
}



void Enemy::updateEntity(float delta)
{
	if (isDead == true)
	{
		if (updateExplosionSprite() == true)
			needDelete = true;
	}
	else {
		updateMovement(delta);
		updateBuff(delta);
		if (hasBeenHit)
		{
			getSprite().setColor(sf::Color::Red);
			hitClock.restart();
		}
		else if (hitClock.getElapsedTime().asSeconds() >= 0.5f)
		{
			getSprite().setColor(baseColor);
		}
		updateLifeBar();
	}
}

void Enemy::updatewPlayer(float delta, Player& player)
{
	if (checkCollisions(player)&&isDead==false)
	{
		player.reduceHP((float)damage);
	}
	
	reduceHP((float)player.getMainWeapon()->checkCollisions(*this));
		
	reduceHP((float)player.getSecondaryWeapon()->checkCollisions(*this));
	if (healthPoint <= 0)
	{
		isDead = true;
		onAvance = false;
		deleteBuffs();
	}
	if (isDead == true)
	{
		if(gavexP==false)
		{
			player.gainXP(info.xpGived);
			gavexP=true;
			player.addToScore((float)info.scoreGived);
			if (player.getMainWeapon()->typeTir == 1)
				player.seekForTarget = true;
		}
	}
}

void Enemy::setScoreGived(float scoreGivedParam)
{
	scoreGived = scoreGivedParam;
}


void Enemy::specialBehaviorwithPlayer(Player& player)
{
	player.gainXP(level);
}

float Enemy::getScoreGived()
{
	return scoreGived;
}



void Enemy::updateAnimation()
{
	if (animationTimer.getElapsedTime().asSeconds() > 0.5f)
	{
		currentFrame.left += 1295;
	}
}
//renvoie true si l'animation d'explosion est finie
bool Enemy::updateExplosionSprite()
{
	explosionSprite.setPosition(sf::Vector2f(getSprite().getPosition().x-(explosionSprite.getGlobalBounds().width/2),
		getSprite().getPosition().y - (explosionSprite.getGlobalBounds().width / 2)));
	if (r < 7)
	{
		if (animationTimer.getElapsedTime().asSeconds() > 0.1f)
		{
			currentFrame.left += 1295;
			explosionSprite.setTextureRect(currentFrame);
			r++;
			animationTimer.restart();
			return false;
		}
		return false;
	}
	return true;
}


void Enemy::renderEntity(sf::RenderTarget& target)
{
	if(isDead==false)
	{
		renderTheEntity(target);
	}
	else{
		target.draw(explosionSprite);
	}

}
void Enemy::setPosition(float positionXParam, float PositionYParam)
{
	setPositionEntity(positionXParam ,PositionYParam);
}

bool Enemy::onestPose()
{
	sf::Vector2f currentPos = getSprite().getPosition();
	if (info.spawnSide == "droite" || info.spawnSide == "bas" )
	{
		if (currentPos.x <= info.pos.x && currentPos.y <= info.pos.y)
			return true;
		return false;
	}
	else 
	{
		if (currentPos.x >= info.pos.x && currentPos.y >= info.pos.y)
			return true;
		return false;
	}
}

void Enemy::setInfo(enemyInfo info_)
{
	info = info_;
}

void Enemy::renderTheEntity(sf::RenderTarget& target)
{
	if (isDead == false)
	{
		Mob::renderTheEntity(target);
		renderBuffs(target);
	}
	else {
		target.draw(explosionSprite);
	}
}

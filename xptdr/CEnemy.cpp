#include "CEnemy.h"


void CEnemy::initAnimation()
{
	CAssetManager &a = *assets;
	currentFrame = sf::IntRect(274 , 409, 1295, 1925);
	explosionSprite.setTexture(a.GetTexture("explosion"));
	explosionSprite.setTextureRect(currentFrame);
	explosionSprite.setScale(0.1f, 0.1f);
}


void CEnemy::initEnnemy(CAssetManager* a, enemyInfo info, std::string nameParam)
{
	setType(Enemy);
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

void CEnemy::initEnnemy(CAssetManager* a, std::string nameParam)
{//DEPRECATED
	setType(Enemy);
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

void CEnemy::initEnnemy(CAssetManager* a, std::string nameParam, sf::Vector2f scale)
{
	//DEPRECATED
	setType(Enemy);
	assets = a;
	enemyName = nameParam;
	setTexture(enemyName);
	getSprite().setScale(scale);
	initAnimation();
	initStat();
	setSprite();
}



void CEnemy::setSprite()
{
	setLifeBar();
	setPositionEntity(spawnPos.x  , (float)spawnPos.y);
}



void CEnemy::updateEntity(float delta)
{
	if (isDead == true)
	{
		if (updateExplosionSprite() == true)
			needDelete = true;
	}
	else {
		updateLifeBar();
		updateMovement(delta);
		updateBuff(delta);
	}
}

void CEnemy::updatewPlayer(float delta, CPlayer& player)
{
	if (checkCollisions(player)&&isDead==false)
	{
		player.reduceHP((float)damage);
	}
	
	if (player.getMainWeapon()->checkCollisions(*this)) {
		reduceHP((float)player.getDamagePerBullet());
	}
	if (player.getSecondaryWeapon()->checkCollisions(*this)) {
		reduceHP((float)player.getDamagePerBullet());
	}
	if (healthPoint <= 0)
	{
		isDead = true;
		onAvance = false;
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

void CEnemy::setScoreGived(float scoreGivedParam)
{
	scoreGived = scoreGivedParam;
}


void CEnemy::specialBehaviorwithPlayer(CPlayer& player)
{
	player.gainXP(level);
}

float CEnemy::getScoreGived()
{
	return scoreGived;
}



void CEnemy::updateAnimation()
{
	if (animationTimer.getElapsedTime().asSeconds() > 0.5f)
	{
		currentFrame.left += 1295;
	}
}
//renvoie true si l'animation d'explosion est finie
bool CEnemy::updateExplosionSprite()
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


void CEnemy::renderEntity(sf::RenderTarget& target)
{
	if(isDead==false)
		renderTheEntity(target);
	else{
		//std::cout << r << std::endl;
		target.draw(explosionSprite);
	}
}
void CEnemy::setPosition(float positionXParam, float PositionYParam)
{
	setPositionEntity(positionXParam ,PositionYParam);
}

bool CEnemy::onestPose()
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

void CEnemy::setInfo(enemyInfo info_)
{
	info = info_;
	initPosition();
}

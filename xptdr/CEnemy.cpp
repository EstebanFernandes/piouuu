#include "CEnemy.h"


void CEnemy::initAnimation()
{
	CAssetManager &a = *assets;
	currentFrame = sf::IntRect(274 , 409, 1295, 1925);
	explosionSprite.setTexture(a.GetTexture("explosion"));
	explosionSprite.setTextureRect(currentFrame);
	explosionSprite.setScale(0.1f, 0.1f);
}



void CEnemy::initEnnemy(CAssetManager* a)
{
	setType(Enemy);
	assets = a;
	imageName = "enemyImage";
	setTexture(imageName);
	getSprite().setScale(0.2f, 0.2f);
	initAnimation();
	initStat();
	setSprite();
}

void CEnemy::initEnnemy(CAssetManager* a, std::string nameParam, sf::Vector2f scale)
{
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
	setPositionEntity(initPositionX  - getSprite().getGlobalBounds().width, (float)initPositionY);
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
	//Ici on regarde le type 

	std::vector<CBulletAuto>* guns = player.getBAW()->getVector();
	size_t temp =guns->size();
	for (size_t i = 0; i < temp; i++)
	{
		
		if (isDead == false)
		{

			if ((*guns)[i].checkCollisions((*this)))
			{
				reduceHP((float)(*guns)[i].getDamage());
			}
		}
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
			player.gainXP(level);
			gavexP=true;
			player.addToScore(scoreGived);
			if (player.BAW.typeTir == 1)
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
	explosionSprite.setPosition(sf::Vector2f(getSprite().getPosition().x+(getSprite().getGlobalBounds().width/2)-(explosionSprite.getGlobalBounds().width/2),
		getSprite().getPosition().y + (getSprite().getGlobalBounds().height / 2) - (explosionSprite.getGlobalBounds().width / 2)));
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

#pragma once
#include "CHittingEntity.h"
#include "DEFINITIONS.h"
#include<ctime>
#include <math.h>  
/// <summary>
/// Class abstraite, méthode à redéfinir :
/// void enemyShoot(); et 
/// void updateMovement(float delta);
/// </summary>
class CEnemy : public CHittingEntity
{
protected:
	std::string imageFile = ENEMYPNG_FILEPATH;
	std::string enemyName = "baseEnemy";

	sf::IntRect currentFrame;
	sf::Clock animationTimer;
	sf::Sprite explosionSprite;
	//float directionX = -3.f;
	float initPositionX = 0;
	int initPositionY = 0;
	//float directionY;
	int r = 0;
	bool gavexP=false;
	int damage;


	void initEnnemy(CAssetManager* a);

	/// <summary>
	/// DEPRECATED
	/// </summary>
	/// <param name="a"></param>
	/// <param name="nameParam"></param>
	/// <param name="imageFileParam"></param>
	void initEnnemy(CAssetManager* a, std::string nameParam, sf::Vector2f scale);
public:
	bool onAvance = true;
	void initAnimation();
	void initStat() {

		//TEMPORAIRE FAUDRA REFAIRE LES CLASSES ENNEMY
		scoreGived = 10;

		int a = assets->sCREEN_HEIGHT - (int)getGlobalBounds().height;
		initPositionY = rand() % a; 
		initPositionX = (float)assets->sCREEN_WIDTH;
		level = 0;
		damage = 3;
		maxHealthPoint = 20.f+15.f*level;
		healthPoint = maxHealthPoint;
	}
	void setScoreGived(float scoreGivedParam);
	float getScoreGived();
	//renvoie true si l'animation d'explosion est finie
	bool updateExplosionSprite();
	void setSprite();
	void updateEntity(float delta);
	void updatewPlayer( float delta,CPlayer& player);
	void specialBehaviorwithPlayer(CPlayer& player);
	void updateAnimation();
	void renderEntity(sf::RenderTarget& target);
	void setPosition(float positionXParam, float PositionYParam);

	virtual void updateMovement(float delta) = 0;
	virtual void enemyShoot() = 0;

	float RandomFloat(float min, float max)
	{
		float random = ((float)rand()) / (float)RAND_MAX;

		// generate (in your case) a float between 0 and (4.5-.78)
		// then add .78, giving you a float between .78 and 4.5
		float range = max - min;
		return (random * range) + min;
	}
};


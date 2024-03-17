#pragma once
#include "CHittingEntity.h"
#include "DEFINITIONS.h"
#include<ctime>
#include <math.h>  

/// <summary>
/// Structure utilisé pour passer les infos des personnages
/// On peut passer d'autres informations dans la struct afin de facilité le passage de données</summary>
struct enemyInfo {
	sf::Vector2f pos;
	std::string spawnSide;
	sf::Vector2f direction;
	sf::Vector2f scale;
	//Constructeur par défaut
	enemyInfo() : 
		pos(-1.f ,-1.f),
		spawnSide("droite"),
		direction(0.f, 0.f),
		scale(1.f,1.f)
	{
	}
};
/// <summary>
/// Class abstraite, méthode à redéfinir :
/// void enemyShoot(); et 
/// void updateMovement(float delta);
/// </summary>
class CEnemy : public CHittingEntity
{
protected:
	std::string enemyName = "baseEnemy";

	sf::IntRect currentFrame;
	sf::Clock animationTimer;
	sf::Sprite explosionSprite;
	//float directionX = -3.f;
	std::string spawnSide="droite";
	/// <summary>
	/// Position que l'ennemi, atteint
	/// </summary>
	enemyInfo info;
	/// <summary>
	/// Position de spawn de l'ennemi
	/// </summary>
	sf::Vector2f spawnPos = sf::Vector2f(0.f,0.f);
	//float directionY;
	int r = 0;
	bool gavexP=false;
	int damage;
	/// <summary>
	/// Cette fonction set les informations de la classe CEnemy.
	/// </summary>
	/// <param name="a"></param>
	/// <param name="info"></param>
	/// <param name="nameParam"></param>
	void initEnnemy(CAssetManager* a,enemyInfo info, std::string nameParam = "");
	void initEnnemy(CAssetManager* a, std::string nameParam = "");
	void initEnnemy(CAssetManager* a,sf::Vector2f , std::string nameParam = "");
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
		level = 0;
		damage = 3;
		maxHealthPoint = 20.f+15.f*level;
		healthPoint = maxHealthPoint;
	}
	void setScoreGived(float scoreGivedParam);
	float getScoreGived();
	//renvoie true si l'animation d'explosion est finie
	bool updateExplosionSprite();
	virtual void setSprite();
	void updateEntity(float delta);
	void updatewPlayer( float delta,CPlayer& player);
	void specialBehaviorwithPlayer(CPlayer& player);
	void updateAnimation();
	void renderEntity(sf::RenderTarget& target);
	void renderUI(sf::RenderTarget& target) {
		if (isDead == false)
		{
		target.draw(lifeBarBackground);
		target.draw(lifeBar);
		}
	}
	void setPosition(float positionXParam, float PositionYParam);

	virtual CEnemy* clone() = 0;
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
	/// <summary>
	/// Cette fonction applique la position où va spawner l'ennemi,
	/// selon le bord on a une position forcé (x côté gauche et droite et x côté gauche et droz)
	/// </summary>
	/// <param name="sideSpawn"></param>
	/// <param name="pos"></param>
	virtual void initPosition()
	{
		if (info.spawnSide == "droite")
		{
			spawnPos.x = (float)assets->sCREEN_WIDTH;
		}
		else if (info.spawnSide == "gauche")
		{
			spawnPos.x = 0.f;
		}
		if (info.pos.x == -1.f&&(info.spawnSide == "haut" || info.spawnSide == "bas"))
		{
				int a = assets->sCREEN_WIDTH - (int)getGlobalBounds().height;
				spawnPos.x = (float)(rand() % a);
				info.pos.x = spawnPos.x;
		}
		else if (info.spawnSide == "haut" || info.spawnSide == "bas")
			spawnPos.x = info.pos.x;



		if (info.spawnSide == "bas")
		{
			spawnPos.y = (float)assets->sCREEN_HEIGHT - getGlobalBounds().width / 2.f;
		}
		else if (info.spawnSide == "haut")
		{
			spawnPos.y = 0.f;
		}
		if (info.pos.y == -1.f && (info.spawnSide == "gauche" || info.spawnSide == "droite"))
		{
			int a = assets->sCREEN_HEIGHT - (int)getGlobalBounds().height;
			spawnPos.y = (float)(rand() % a);
			info.pos.y = spawnPos.y;
		}
		else if (info.spawnSide == "gauche" || info.spawnSide == "droite")
			spawnPos.y = info.pos.y;
	}
	
	/// <summary>
	/// Fonction a appelé après que les deux positions (spawn et final aient été set)
	/// On peut la redéfinir pour des comportements particulier
	/// Pour l'instant la fonction  ne fait que regarder si la direction est nul, si c'est le cas elle la set selon spawnPos et info.pos
	/// </summary>
	virtual void initDirection() {
		sf::Vector2f& dir = info.direction;
		if (dir.x == 0.f&&dir.y==0.f)
		{
			dir = utilities::dirAtoB(spawnPos, info.pos);
		}
	}
	
	/// <summary>
	/// Fonction qui dit, si on est positionné ou pas selon la position dans info et la position actuelle
	/// </summary>
	/// <returns></returns>
	bool onestPose();
	void setInfo(enemyInfo info_);
};


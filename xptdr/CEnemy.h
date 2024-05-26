#pragma once
#include "CHittingEntity.h"
#include "DEFINITIONS.h"
#include<ctime>
#include <math.h>  

/// <summary>
/// Structure utilis� pour passer les infos des personnages
/// On peut passer d'autres informations dans la struct afin de facilit� le passage de donn�es</summary>
struct enemyInfo {
	sf::Vector2f pos; //Position que l'ennemi doit atteindre
	std::string spawnSide;//Cot� o� on spawn, gauche droite haut ou bas
	sf::Vector2f direction;//Direction d'avanc�e
	sf::Vector2f scale;
	bool mustSetDirection;
	bool isAim; //Savoir si l'unit� doit viser un joueur
	int xpGived;
	int scoreGived;
	//Constructeur par d�faut
	enemyInfo() :
		pos(-1.f, -1.f),
		spawnSide("droite"),
		direction(0.f, 0.f),
		scale(1.f, 1.f),
		isAim(false),
		mustSetDirection(false),
		xpGived(0),
		scoreGived(0)
	{
	}
};
/// <summary>
/// Class abstraite, m�thode � red�finir :
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
	int damage;
	bool gavexP = false;
	sf::Clock hitClock;
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
	virtual void renderEntity(sf::RenderTarget& target);
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
	/// Cette fonction applique la position o� va spawner l'ennemi,
	/// selon le bord on a une position forc� (x c�t� gauche et droite et y en haut et en bas)
	/// </summary>
	virtual void initPosition()
	{


		if (info.spawnSide == "droite")
		{
			spawnPos.x = (float)assets->sCREEN_WIDTH;
			info.pos.x = (info.pos.x == -1.f) ? spawnPos.x - getGlobalBounds().width * 0.8f : info.pos.x;
		}
		else if (info.spawnSide == "gauche")
		{
			spawnPos.x = 0.f;
			info.pos.x = (info.pos.x == -1.f) ? getGlobalBounds().width * 0.8f : info.pos.x;
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
			spawnPos.y = (float)assets->sCREEN_HEIGHT;
			info.pos.y = (info.pos.y == -1.f) ? spawnPos.y - getGlobalBounds().height * 0.8f : info.pos.y;
		}
		else if (info.spawnSide == "haut")
		{
			spawnPos.y = 0.f;
			info.pos.y = (info.pos.y == -1.f) ? getGlobalBounds().height * 0.8f : info.pos.y;
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
	/// Fonction a appel� apr�s que les deux positions (spawn et final aient �t� set)
	/// On peut la red�finir pour des comportements particulier
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
	/// Fonction qui dit, si on est positionn� ou pas selon la position dans info et la position actuelle
	/// </summary>
	/// <returns></returns>
	bool onestPose();
	void setInfo(enemyInfo info_);
};


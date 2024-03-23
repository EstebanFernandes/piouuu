#pragma once

#include "CEnemy.h"

class RusherEnemy : public CEnemy
{
private:
	sf::Color baseColor = sf::Color::White;
	CAnimation anim;
	bool isPositionated = false;
	bool isRushing = false;
	bool isRed = false;
	int counter = 0;
	int counterAnim = 0;
	float dureeTotale = 3.f;
	sf::Time dureePasseTotale = sf::Time::Zero;
	sf::Sound *fxRush;
	sf::Clock colorSwitchClock;
	sf::Clock redColorSwitchClock;
	CMob* target;
	sf::Vector2f direction;
public:
	RusherEnemy(CAssetManager* assets);
	//M�thode qui fonctionne uniquement pour les levels, elle n'initialise pas vraiment les param�tres de rusher
	RusherEnemy(CAssetManager* assets,CCharacter stat ,enemyInfo info, CMob* target_);
	RusherEnemy(CAssetManager* assets,CMob* target_);
	~RusherEnemy();
	void updateMovement(float delta);
	/// <summary>
	/// Fonction a appel� apr�s que les deux positions (spawn et final aient �t� set)
	/// On peut la red�finir pour des comportements particulier
	/// Pour l'instant la fonction  ne fait que regarder si la direction est nul, si c'est le cas elle la set selon spawnPos et info.pos
	/// </summary>
	void initDirection(CMob* target);
	void updateEntity(float delta);
	void enemyShoot() {};
	CEnemy* clone()  override {
		RusherEnemy* temp = new RusherEnemy(*this);
		temp->initPosition();
		temp->initDirection(target);
		temp->setSprite();
		return temp;
	}
	//Update rusher animation
	void  updateAnim();
};


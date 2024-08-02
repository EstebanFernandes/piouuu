#pragma once

#include "Enemy.h"

class RusherEnemy : public Enemy
{
private:
	sf::Color baseColor = sf::Color::White;
	Animation anim;
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
	Mob* target;
	sf::Vector2f direction;
public:
	RusherEnemy(AssetManager* assets);
	//Méthode qui fonctionne uniquement pour les levels, elle n'initialise pas vraiment les paramètres de rusher
	RusherEnemy(AssetManager* assets,Character stat ,enemyInfo info);
	~RusherEnemy();
	void updateMovement(float delta);
	/// <summary>
	/// Fonction a appelé après que les deux positions (spawn et final aient été set)
	/// On peut la redéfinir pour des comportements particulier
	/// Pour l'instant la fonction  ne fait que regarder si la direction est nul, si c'est le cas elle la set selon spawnPos et info.pos
	/// </summary>
	void initDirection(Mob* target);
	void updateEntity(float delta);
	void enemyShoot() {};
	Enemy* clone()  override {
		RusherEnemy* temp = new RusherEnemy(*this);
		temp->assets = assets;
		temp->initPosition();
		temp->initDirection(target);
		temp->setSprite();
		temp->initAnimation();
		return temp;
	}
	//Update rusher animation
	void  updateAnim();
	void setTarget(Mob* target_) {
		target = target_;
	}
	void initAnimation()
	{
		anim = Animation(getPointerSprite(), sf::Vector2i(73, 86), 6, -1.f, 2);
		colorSwitchClock.restart();
		redColorSwitchClock.restart();
		if (info.spawnSide=="gauche")
			flipSprite();
	}
};


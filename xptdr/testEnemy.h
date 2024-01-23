#pragma once
#include"CEnemy.h"
/// <summary>
/// Cette classe représente un pantin que l'on peut faire spawn en appuyant sur une touche
/// il spawn selon une position qu'on lui donne et un montant d'hp
/// </summary>
class testEnemy : public CEnemy
{

public:
	testEnemy(CAssetManager* a,sf::Vector2i pos, int hp);
	void updateMovement(float delta);
	void enemyShoot();
};


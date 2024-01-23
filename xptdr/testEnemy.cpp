#include "testEnemy.h"

testEnemy::testEnemy(CAssetManager* a, sf::Vector2i pos, int hp)
{
	initEnnemy(a);
	maxHealthPoint = hp;
	healthPoint = maxHealthPoint;
	setSprite();
	setPosition((float)pos.x, (float)pos.y);
}

void testEnemy::updateMovement(float delta)
{
}

void testEnemy::enemyShoot()
{
}

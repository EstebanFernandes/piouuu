#include "testEnemy.h"

testEnemy::testEnemy(CAssetManager* a, sf::Vector2f pos, int hp)
{
	initEnnemy(a);
	maxHealthPoint = (float)hp;
	healthPoint = maxHealthPoint;
	setSprite();
	setPosition(pos.x, pos.y);
}

void testEnemy::updateMovement(float delta)
{
}

void testEnemy::enemyShoot()
{
}

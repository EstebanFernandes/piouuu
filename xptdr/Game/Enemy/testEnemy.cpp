#include "testEnemy.h"

testEnemy::testEnemy(AssetManager* a, sf::Vector2f pos, int hp)
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

void testEnemy::renderTheEntity(sf::RenderTarget& target)
{
	Enemy::renderTheEntity(target);
}
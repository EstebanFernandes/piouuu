#include "fire.h"
#include "BuffEntity.h"

void fire::initSprite()
{
	fireSprite.setTexture(assets->GetTexture("fireSpriteSheet"));
	fireAnimation = Animation(&fireSprite, sf::Vector2i(80, 80), 16, 0.16f);
	//float scale = fireSprite.getGlobalBounds().width * target->getSprite().getScale().x / target->getGlobalBounds().width;
	//fireSprite.setScale(scale, scale);
	fireSprite.setOrigin(
		fireSprite.getLocalBounds().width / 2.f,
		fireSprite.getLocalBounds().height);
}

fire::fire(Mob* targetparam, float damage, float timer, float duration, AssetManager* assets_)
	: dot(typeEffet::fire)
{
	target = targetparam;
	this->damage = damage;
	this->timer = timer;
	this->duration = duration;
	clock.restart();
	assets = assets_;
	if (targetparam != NULL)
		initSprite();
}

void fire::globalMethod(std::vector<Mob*>& entityList)
{
	for (auto& entity : entityList)
	{
		if (target->getSprite().getGlobalBounds().intersects(entity->getSprite().getGlobalBounds())&&target!=entity)
		{
			if( utilities::RandomFloat(0.f,100.f)<=probaPropag)
			{
				if (BuffEntity* buffMob = dynamic_cast<BuffEntity*>((entity)))
				{
					if(buffMob->checkForType(type))
					{
						fire* newAdd = (fire*)clone();
						newAdd->changeTarget(entity);
						buffMob->addBuff(newAdd, true);
					}
				}
			}
		}  

	}
}

void fire::update(float delta)
{
	if (ab++ == 1)
		fireAnimation.setSprite(&fireSprite);
	fireSprite.setPosition(target->getPosition());
	fireAnimation.updateAnimation();
	dot::update(delta);
}

void fire::action()
{
	dot::action();
}

void fire::renderBuff(sf::RenderTarget& target)
{
	target.draw(fireSprite);
}
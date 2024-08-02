#include "thunder.h"
#include"BuffEntity.h"
#include"../utilities.h"

// Initialisation de la variable statique thunderImage
image thunder::thunderImage;
sf::Sprite thunder::randomizeThunder()
{
	int random_number = std::rand() % 10;
	bool flip = std::rand() % 2;
	thunderImage.anim.setcurrentXFrameNumber(random_number);
	utilities::flipSprite(thunderImage.sprite);
	return thunderImage.sprite;
}
thunder::thunder(Mob* targetparam, Mob* thereFore, float damage_, float range_, AssetManager* assets_)
	:effetspecial(typeEffet::thunder), damage(damage_), 
	range(range_),asset(assets_),prevTarget(thereFore)
{
}

void thunder::globalMethod(std::vector<Mob*>& entityList)
{
	for (auto& entity : entityList)
	{
		float distance = utilities::minimumDistance(target->getGlobalBounds(), entity->getGlobalBounds());
		if (distance <= range && target != entity&& entity != prevTarget)
		{
			if (BuffEntity* buffMob = dynamic_cast<BuffEntity*>((entity)))
			{
				if (buffMob->checkForType(type))
				{
					thunder* newAdd = (thunder*)clone();
					newAdd->changeTarget(entity);
					newAdd->setPrevTarget(target);
					buffMob->addBuff(newAdd, true);
					setSprite(entity,distance);
				}
			}
		}
	}

}

void thunder::update(float delta)
{

}

void thunder::action()
{
}

void thunder::initializeThunder(AssetManager* am)
{
	thunderImage.sprite.setTexture(am->GetTexture("thunder"));
	thunderImage.anim = Animation(&thunderImage.sprite, sf::Vector2i(148, 371),10,-1.f);
}

void thunder::setSprite(Mob* otherTarget,float distance)
{
	//sf::Sprite temp = randomizeThunder();
	sf::RectangleShape temp;
	temp.setFillColor(sf::Color::White);
	temp.setSize(sf::Vector2f(3.f, utilities::getDistancefrom2Pos(target->getPosition(),otherTarget->getPosition())));
	temp.setOrigin(temp.getLocalBounds().width / 2.f , 0.f);
	float scale = distance/371.f;
	//temp.setScale(scale, scale);
	temp.setPosition(target->getPosition());
	temp.setRotation(utilities::getAngleFromDirection(utilities::dirAtoB(target->getPosition(), otherTarget->getPosition()))-90.f);
	hitSprite.push_back(temp);
}
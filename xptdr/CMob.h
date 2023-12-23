#pragma once
#include "DEFINITIONS.h"
#include <SFML/Graphics.hpp>
#include<iostream>
#include <string>
#include"CAssetManager.h"
#include"CEntity.h"
#include"CCharacter.h"
//Héritage de entité, classe de base qui permet de gérer les mobs (joueurs, npc,ennemies)
class CMob : public CEntity, public CCharacter
{
protected :

	bool hasBeenHit = false;
	sf::RectangleShape lifeBar;
	sf::RectangleShape lifeBarBackground;
public:
	CMob();
	//Méthode à redéfinir 

	void updateStates(CCharacter characterParam);

	void setLifeBar(){
		lifeBar = sf::RectangleShape(sf::Vector2f(100.f, 10.f));
		lifeBar.setFillColor(sf::Color::Red);
		lifeBarBackground = sf::RectangleShape(sf::Vector2f(100.f, 10.f));
		lifeBarBackground.setFillColor(sf::Color::Black);
	}
	void updateLifeBar() {
		if (hasBeenHit)
		{
			lifeBar.setSize(sf::Vector2f(100.f * healthPoint / maxHealthPoint, 10.f));
			hasBeenHit = false;
		}
	}
	void setPositionEntity(const float x, const float y) {
		sf::Sprite& temp = getSprite();
		getSprite().setPosition(x, y);
		float _x = x + (temp.getGlobalBounds().width / 2) - (lifeBarBackground.getGlobalBounds().width / 2);
		float _y = y - ((temp.getGlobalBounds().height / 4));
		lifeBar.setPosition(_x, _y);
		lifeBarBackground.setPosition(_x, _y);
	}
	void setPositionEntity(sf::Vector2f i) {
		setPositionEntity(i.x, i.y);
	}
	void moveEntity(sf::Vector2f mov) {
		if (mov.x != 0.f)
		{
			std::cout << "";
		}
		getSprite().move(mov);
		lifeBar.move(mov);
		lifeBarBackground.move(mov);
	}
	void moveEntity(float x, float y) {
		moveEntity(sf::Vector2f(x, y));
	}
	void renderTheEntity(sf::RenderTarget& target) {
		target.draw(getSprite());
		target.draw(lifeBarBackground);
		target.draw(lifeBar);
	}
	void reduceHP(int damage) {
		healthPoint -= damage;
		if (healthPoint < 0)
			healthPoint = 0;
		else if (healthPoint > maxHealthPoint)
			healthPoint = maxHealthPoint;
		hasBeenHit = true;
	}
	void gainHP(int damage)
	{
		reduceHP(damage);
		hasBeenHit = false;
	}

	sf::Vector2f getDistance(CMob& player) {

		sf::Vector2f posMob = getSprite().getPosition();
		sf::Vector2f pos = player.getSprite().getPosition();
		sf::Vector2f dir;
		dir.x = posMob.x - pos.x;
		dir.y = posMob.y - pos.y;
		return dir;
	}
};


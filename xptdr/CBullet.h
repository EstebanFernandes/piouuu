#pragma once
#include "SFML/Graphics.hpp"
#include "DEFINITIONS.h"
#include "CEntity.h"

class CBullet : public CEntity
{
protected:
	sf::Vector2f direction;
	float bulletSpeed = 2.f;
	int damage;
public :
	CBullet();
	CBullet(int damaage, sf::Vector2f pos, sf::Vector2f dir, std::string nameImage, CAssetManager* assetss);
	CBullet(int damaage, sf::Vector2f pos, sf::Vector2f dir, float bulletSpeed, std::string nameImage, CAssetManager* assetss);
	void setSprite(std::string nameImage);
	void updateEntity(float dt);
	void updateCollision(CEntity& b);
	void renderEntity(sf::RenderTarget& target);
	//Surchagrge pour les collisions entre objet
	int getDamage() { return damage; }
	//m�thode appeler automatiquement � la fin du constructeur qui s'occupe de r�gler le sprite selon la direction.
	//Le sprite de la balle doit �tre dessiner de base de la droite vers la gauche.
	//L'appel de cette fonction suppose que la direction de la balle a �t� d�clar�e
	void setDirectionSprite();
};


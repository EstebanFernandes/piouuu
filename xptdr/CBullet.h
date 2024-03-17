#pragma once
#include "SFML/Graphics.hpp"
#include "DEFINITIONS.h"
#include"CMob.h"
#include "CAnimation.h"
class CBullet : public CMob
{
protected:
	sf::Vector2f direction;
	sf::Vector2f bulletScale;
	float bulletSpeed = 2.f;
	int damage;
	int penetration = 0;
	bool isABombe = false;
	//pas encore sur mais ça se réfléchit
	std::vector<CMob*> entityHitting;
public :

	CBullet();
	CBullet(int damaage, sf::Vector2f pos, sf::Vector2f dir, int penetration
		,std::string nameImage, CAssetManager* assetss);
	CBullet(int damaage, sf::Vector2f pos, sf::Vector2f dir, float bulletSpeed, int penetration
		,std::string nameImage, CAssetManager* assetss, sf::Vector2f bulletScale);
	void setSprite(std::string nameImage);
	void updateEntity(float dt);
	void renderEntity(sf::RenderTarget& target);
	void renderUI(sf::RenderTarget& target) {

	}
	//Surchagrge pour les collisions entre objet
	int getDamage() { return damage; }
	//méthode appeler automatiquement à la fin du constructeur qui s'occupe de régler le sprite selon la direction.
	//Le sprite de la balle doit être dessiner de base de la droite vers la gauche.
	//L'appel de cette fonction suppose que la direction de la balle a été déclarée
	void setDirectionSprite();

	/// <summary>
	/// Méthode surchargé qui a un comportement différent du checkCollision de base
	/// 
	/// </summary>
	/// <param name="b"></param>
	/// <returns></returns>
	bool checkCollisions(CMob& b);
	void setBulletPos(sf::Vector2f pos) {
		getSprite().setPosition(pos);
	}


};


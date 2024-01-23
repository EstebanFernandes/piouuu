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
	int penetration = 0;
	//pas encore sur mais ça se réfléchit
	std::vector<CEntity*> entityHitting;
public :
	CBullet();
	CBullet(int damaage, sf::Vector2f pos, sf::Vector2f dir, int penetration
		,std::string nameImage, CAssetManager* assetss);
	CBullet(int damaage, sf::Vector2f pos, sf::Vector2f dir, float bulletSpeed, int penetration
		,std::string nameImage, CAssetManager* assetss);
	void setSprite(std::string nameImage);
	void updateEntity(float dt);
	void updateCollision(CEntity& b);
	void renderEntity(sf::RenderTarget& target);
	//Surchagrge pour les collisions entre objet
	int getDamage() { return damage; }
	//méthode appeler automatiquement à la fin du constructeur qui s'occupe de régler le sprite selon la direction.
	//Le sprite de la balle doit être dessiner de base de la droite vers la gauche.
	//L'appel de cette fonction suppose que la direction de la balle a été déclarée
	void setDirectionSprite();

	//méthode qu'on appelle quand la balle rentre on contacte avec quelque chose, selon la p
	//pénétration on veut ou non faire quelque chose
	void CONTACT();
	/// <summary>
	/// Méthode surchargé qui a un comportement différent du checkCollision de base
	/// 
	/// </summary>
	/// <param name="b"></param>
	/// <returns></returns>
	bool checkCollisions(CEntity& b);
};


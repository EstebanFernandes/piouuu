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
	//pas encore sur mais �a se r�fl�chit
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
	//m�thode appeler automatiquement � la fin du constructeur qui s'occupe de r�gler le sprite selon la direction.
	//Le sprite de la balle doit �tre dessiner de base de la droite vers la gauche.
	//L'appel de cette fonction suppose que la direction de la balle a �t� d�clar�e
	void setDirectionSprite();

	//m�thode qu'on appelle quand la balle rentre on contacte avec quelque chose, selon la p
	//p�n�tration on veut ou non faire quelque chose
	void CONTACT();
	/// <summary>
	/// M�thode surcharg� qui a un comportement diff�rent du checkCollision de base
	/// 
	/// </summary>
	/// <param name="b"></param>
	/// <returns></returns>
	bool checkCollisions(CEntity& b);
};


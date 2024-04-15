#pragma once
#include"SFML/Graphics.hpp"
#include"CAssetManager.h"
/// <summary>
/// Classe qui gère les transition
/// </summary>

enum SENS_TRANSITION {
	GAUCHE = 1,
	DROITE,
	HAUT,
	BAS,
	MILIEU,
	NULLTRANSITION
};
class CTransition 
{
private:
	int transiState = 0;//L'état défini où on en est, 0 pas commencé, 1 on a fait 1 tour, 2 on a fini
	SENS_TRANSITION sens = GAUCHE;
	sf::RectangleShape backTransi;
	CAssetManager* asset;
	//Temps total de la transition
	float time = -1.f;
	sf::Clock clock;
	sf::Vector2f dir;
	float speed = 0.f;
	bool isThisIt = true;
	//Permet de savoir si on a déjà rendu le 
	bool alreadyBeenRendered = false;
	/// <summary>
	/// Dit si l'objet de la transition est en dehors des limites de l'écran ou non 
	/// </summary>
	/// <returns></returns>
	bool globalCollision();
public :
	bool transiouuuuu = false;
	CTransition();
	CTransition(CAssetManager* a,SENS_TRANSITION param, float time);
	void initTransition();
	/// <summary>
	/// Return true if the transi is finished
	/// </summary>
	/// <param name="delta"></param>
	/// <returns></returns>
	bool updateTransition(float delta);
	void renderTransition(sf::RenderWindow& window);
	/// <summary>
	/// Dit si la transition est fini
	/// </summary>
	/// <returns></returns>
	bool finito() { return isThisIt; }
	//Permet de change le sens de la transition, attention cette fonction écrase la transition précédente
	void switchSens(SENS_TRANSITION newSens);

};


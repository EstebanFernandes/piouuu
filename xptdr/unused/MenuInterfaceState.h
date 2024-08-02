#pragma once
#include"../UI/Button.h"
/// <summary>
/// Classe pour g�rer les menus, ici on va mettre ce qui est commun � cela(bouton retour) 
/// </summary>
class CMenuInterfaceState
{
protected:
	AssetManager* asset;
	Button boutonRetour;
	//0 = en haut � gauche, 1 corner droit etc etc

	int emplacement;
	void init(AssetManager* asset_);
	void update(float dt);
	void handleInput(sf::Event& event);
	void draw(sf::RenderTarget& target);
};


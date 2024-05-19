#pragma once
#include"CButton.h"
/// <summary>
/// Classe pour g�rer les menus, ici on va mettre ce qui est commun � cela(bouton retour) 
/// </summary>
class CMenuInterfaceState
{
protected:
	CAssetManager* asset;
	CButton boutonRetour;
	//0 = en haut � gauche, 1 corner droit etc etc

	int emplacement;
	void init(CAssetManager* asset_);
	void update(float dt);
	void handleInput(sf::Event& event);
	void draw(sf::RenderTarget& target);
};


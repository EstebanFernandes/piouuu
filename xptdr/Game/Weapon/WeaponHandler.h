#pragma once
#include"Weapon.h"
/// <summary>
/// Classe qui gère un pointeur sur une arme, il permet de changer d'armes et est l'objet que doit tenir une unité qui tire, jamais un pointeur seul sur une arme
/// </summary>
class WeaponHandler
{
private:

	//Enum qui définit l'arme actuelle
	enum WeaponType {
		Gunslinger,
		ChargeShot,
		Laser,
		Gunshot
	};
	AssetManager* assets;
	//Booléen qui sert à savoir si le porteur recherche ou doit chercher une cible cf balle auto-guidé
	bool seekForTarget;
	Weapon* weapon;
	//Pointer sur le porteur
	Mob* pointerToMob;
	//Les effets sont indépendants de l'arme que l'on a
	std::vector<effetspecial*> effetOnHit;
	//Pareil pour les stats
	WeaponStat stat;
public:
	//Fonction qui 
	void setNewWeapon( Weapon* replacement, bool isFirstTime = false);
	void traitermisc(std::string misc);
	int checkCollisions(Mob& b) { return weapon->checkCollisions(b);}
	void weaponControls(sf::Event& event) { weapon->weaponControls(event); }
	void weaponShoot() { weapon->weaponShoot(); }
	void updateWeapon(float dt) { weapon->updateWeapon(dt); }
	void renderWeapon(sf::RenderTarget& target) { weapon->renderWeapon(target); }
	void setBulletAsset(std::string assetName) { weapon->setBulletAsset(assetName); }
	void addBuff(effetspecial* newEffet) { effetOnHit.push_back(newEffet); }
};


#pragma once
#include"Weapon.h"
/// <summary>
/// Classe qui g�re un pointeur sur une arme, il permet de changer d'armes et est l'objet que doit tenir une unit� qui tire, jamais un pointeur seul sur une arme
/// </summary>
class WeaponHandler
{
private:

	//Enum qui d�finit l'arme actuelle
	enum WeaponType {
		Gunslinger,
		ChargeShot,
		Laser,
		Gunshot
	};
	AssetManager* assets;
	//Bool�en qui sert � savoir si le porteur recherche ou doit chercher une cible cf balle auto-guid�
	bool seekForTarget;
	Weapon* weapon;
	//Pointer sur le porteur
	Mob* pointerToMob;
	//Les effets sont ind�pendants de l'arme que l'on a
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


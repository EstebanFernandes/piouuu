#include "CGunslinger.h"



void CGunslinger::updatebyIndex(float dt, int index)
{
		for (size_t i = 0; i < magasine.size(); i++)
		{
			if (magasine[i].needDelete == true)
			{
				magasine.erase(magasine.begin() + i);
				if (i != 0)
					i--;
				break;
			}
			magasine[i].updateEntity(dt);
			if (magasine[i].checkGlobalCollisions() == true)
				magasine[i].needDelete = true;
			if (magasine[i].needDelete == true)
			{
				magasine.erase(magasine.begin() + i);
				if (i != 0)
					i--;
			}
		}
}

void CGunslinger::pushByIndex(int index)
{

}

CGunslinger::CGunslinger()
{
	typeTir = (int)pow(2,0);
	typeBalle = (int)pow(2,0);
	setType(Gunslinger);
	if (bulletSoundBuffer.loadFromFile("res/sfx/Piou.wav"))
	{
		bulletSound.setBuffer(bulletSoundBuffer);
	}
	else
	{
		std::cout << "Erreur lors du chargement du son de tir." << std::endl;
	}
}

void CGunslinger::updateEntity(float dt)
{
	std::bitset<nbBullet> temp = std::bitset<nbBullet>(typeBalle);
	for (int i = 0; i < temp.size(); i++)
	{
		if (temp[i] != 0)
		{
			updatebyIndex(dt, i);
		}
	}
}

void CGunslinger::renderEntity(sf::RenderTarget& target)
{
		for (size_t i = 0; i < magasine.size(); i++)
		{
			magasine[i].renderEntity(target);
		}
}

void CGunslinger::updateCollision(CEntity& b)
{
		for (size_t i = 0; i < magasine.size(); i++)
		{
			magasine[i].updateCollision(b);

		}
}



//Méthode utilisé par le joueur
void CGunslinger::iNeedMoreBullets(sf::Vector2f pos, int damage)
{
	iNeedMoreBullets(pos, damage, 0.f);
}

void CGunslinger::iNeedMoreBullets(sf::Vector2f pos, int damage, float bulletSpeed)
{
	iNeedMoreBullets(pos, damage, bulletSpeed, sf::Vector2f(1.f, 0.f));
}

void CGunslinger::iNeedMoreBullets(sf::Vector2f pos, int damage, float bulletSpeed, sf::Vector2f dir)
{
	std::bitset<nbAim> temp = std::bitset<nbAim>(typeTir);
	//magazine.push_back(CBullet(damage, pos, sf::Vector2f(1, 0), assets));
	for (int i = 0; i < temp.size(); i++)
	{
		if (temp[i] != 0)
		{
			switch (i) {
			case classic:
				magasine.push_back(CBulletAuto(damage, pos, bulletSpeed, dir, nameBulletSkin, assets));
				break;
			case doubleTirs1:
				magasine.push_back(CBulletAuto(damage, pos, bulletSpeed, sf::Vector2f(1.f, 0.75f),nameBulletSkin, assets));
				magasine.push_back(CBulletAuto(damage, pos, bulletSpeed, sf::Vector2f(1.f, -0.75f), nameBulletSkin, assets));
				break;
			case doubleTirs2:
				pos.y += 3.f;
				magasine.push_back(CBulletAuto(damage, pos, bulletSpeed, sf::Vector2f(1.f, 0.f), nameBulletSkin, assets));
				pos.y -= 6.f;
				magasine.push_back(CBulletAuto(damage, pos, bulletSpeed, sf::Vector2f(1.f, 0.f), nameBulletSkin, assets));
				break;
			case gunshotAim:
				//magasine.push_back(CBulletAuto(damage, pos, sf::Vector2f(1.f, 1.f), bulletSpeed, gunshotDistance, assets));
				magasine.push_back(CBulletAuto(damage, pos, sf::Vector2f(1.f, 0.75f), bulletSpeed, gunshotDistance, nameBulletSkin, assets));
				magasine.push_back(CBulletAuto(damage, pos, sf::Vector2f(1.f, 0.50f), bulletSpeed, gunshotDistance, nameBulletSkin, assets));
				magasine.push_back(CBulletAuto(damage, pos, sf::Vector2f(1.f, 0.25f), bulletSpeed, gunshotDistance, nameBulletSkin, assets));
				magasine.push_back(CBulletAuto(damage, pos, sf::Vector2f(1.f, 0.f), bulletSpeed, gunshotDistance, nameBulletSkin, assets));
				magasine.push_back(CBulletAuto(damage, pos, sf::Vector2f(1.f, -0.25f), bulletSpeed, gunshotDistance, nameBulletSkin, assets));
				magasine.push_back(CBulletAuto(damage, pos, sf::Vector2f(1.f, -0.50f), bulletSpeed, gunshotDistance, nameBulletSkin, assets));
				magasine.push_back(CBulletAuto(damage, pos, sf::Vector2f(1.f, -0.75f), bulletSpeed, gunshotDistance, nameBulletSkin, assets));
				//magasine.push_back(CBulletAuto(damage, pos, sf::Vector2f(1.f, -1.f), bulletSpeed, gunshotDistance, assets));
				break;
			}
		}
	}
	bulletSound.play();
}

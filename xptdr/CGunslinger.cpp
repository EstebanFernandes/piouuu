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
	iNeedMoreBullets(pos, damage, bulletSpeed, dir, sf::Vector2f(1.f,1.f));
}

void CGunslinger::iNeedMoreBullets(sf::Vector2f pos, int damage, float bulletSpeed, sf::Vector2f dir, sf::Vector2f bulletScale)
{
	std::bitset<nbAim> temp = std::bitset<nbAim>(typeTir);
	//magazine.push_back(CBullet(damage, pos, sf::Vector2f(1, 0), assets));
	for (int i = 0; i < temp.size(); i++)
	{
		if (temp[i] != 0)
		{
			switch (i) {
			case classic:
				magasine.push_back(CBulletAuto(damage, pos, bulletSpeed, dir, penetration, nameBulletSkin, assets, bulletScale));
				break;
			case doubleTirs1:
				magasine.push_back(CBulletAuto(damage, pos, bulletSpeed, sf::Vector2f(1.f, 0.75f), penetration, nameBulletSkin, assets, bulletScale));
				magasine.push_back(CBulletAuto(damage, pos, bulletSpeed, sf::Vector2f(1.f, -0.75f), penetration, nameBulletSkin, assets, bulletScale));
				break;
			case doubleTirs2:
				pos.y += 3.f;
				magasine.push_back(CBulletAuto(damage, pos, bulletSpeed, sf::Vector2f(1.f, 0.f), penetration, nameBulletSkin, assets, bulletScale));
				pos.y -= 6.f;
				magasine.push_back(CBulletAuto(damage, pos, bulletSpeed, sf::Vector2f(1.f, 0.f), penetration, nameBulletSkin, assets, bulletScale));
				break;
			case gunshotAim:
				//magasine.push_back(CBulletAuto(damage, pos, sf::Vector2f(1.f, 1.f), bulletSpeed, gunshotDistance, assets));
				magasine.push_back(CBulletAuto(damage, pos, sf::Vector2f(1.f, 0.75f), bulletSpeed, gunshotDistance, penetration, nameBulletSkin, assets, bulletScale));
				magasine.push_back(CBulletAuto(damage, pos, sf::Vector2f(1.f, 0.50f), bulletSpeed, gunshotDistance, penetration, nameBulletSkin, assets, bulletScale));
				magasine.push_back(CBulletAuto(damage, pos, sf::Vector2f(1.f, 0.25f), bulletSpeed, gunshotDistance, penetration, nameBulletSkin, assets, bulletScale));
				magasine.push_back(CBulletAuto(damage, pos, sf::Vector2f(1.f, 0.f), bulletSpeed, gunshotDistance, penetration, nameBulletSkin, assets, bulletScale));
				magasine.push_back(CBulletAuto(damage, pos, sf::Vector2f(1.f, -0.25f), bulletSpeed, gunshotDistance, penetration, nameBulletSkin, assets, bulletScale));
				magasine.push_back(CBulletAuto(damage, pos, sf::Vector2f(1.f, -0.50f), bulletSpeed, gunshotDistance, penetration, nameBulletSkin, assets, bulletScale));
				magasine.push_back(CBulletAuto(damage, pos, sf::Vector2f(1.f, -0.75f), bulletSpeed, gunshotDistance, penetration, nameBulletSkin, assets, bulletScale));
				//magasine.push_back(CBulletAuto(damage, pos, sf::Vector2f(1.f, -1.f), bulletSpeed, gunshotDistance, assets));
				break;
			case bombe:
				magasine.push_back(CBulletAuto(damage, pos, bulletSpeed, dir, penetration, nameBulletSkin, assets, bulletScale, true));
				break;
			}
		}
	}
	bulletSound.play();
}

void CGunslinger::shootTowardDirection(sf::Vector2f initPos, sf::Vector2f targetPos,int damage,float bulletSpeed)
{
	sf::Vector2f dir;
	sf::Vector2f otherPos = initPos - targetPos;
	/*
	if (targetPos.x < initPos.x) {
		dir.x = -1;
	}
	else if (targetPos.x > initPos.x) {
		dir.x = 1;
	}
	else {
		dir.x = 0;
	}
	*/
	float a = otherPos.y / otherPos.x;

	dir.x = -1 / std::sqrt(1 + std::pow(a, 2));
	dir.y = a * dir.x;

	if (otherPos.x < 0) {
		dir.x = dir.x * -1;
		dir.y = dir.y * -1;
	}

	/*
	dir = targetPos - initPos;
	float max = std::abs(std::min(dir.x, dir.y));
	dir = dir / max;
	*/
	iNeedMoreBullets(initPos, damage, bulletSpeed, dir);
}

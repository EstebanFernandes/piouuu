#include "chargeShot.h"

void chargeShot::sendBullet()
{
	sf::Vector2f pos(chargingBall.getPosition());
	if (typeTir == autoAim)
		*seekForTarget = true;
	for (int i = 0; i < referenceStat.dir2.size(); i++)
	{
		//initBuff(chargingBall);
		sf::Vector2f tempDirection = referenceStat.dir2[i];
		if (typeTir == gunshotAim)
		{
			tempDirection = utilities::getDirectionFromAngle(utilities::RandomatXPerc(15.f, utilities::getAngleFromDirection(tempDirection)));
			chargingBall.setGunShotDistance(utilities::RandomatXPerc(15.f, chargingBall.getGunshotTotalDistance()));
			chargingBall.setBulletSpeed(utilities::RandomatXPerc(0.5f, chargingBall.getBulletSpeed()));
		}
		if (typeTir == Spin)
		{
			tempDirection = utilities::getDirectionFromAngle(utilities::getAngleFromDirection(tempDirection) + angleOffset);
		}
		if (typeTir == doubleTirs2)
		{
			if (i == 0)
				chargingBall.setBulletPos(sf::Vector2f(pos.x, pos.y - 7.f));
			else
				chargingBall.setBulletPos(sf::Vector2f(pos.x, pos.y + 7.f));
		}
		if (typeTir != bombe)
		{
			chargingBall.setDirection(tempDirection);
			chargingBall.setDirectionSprite();
		}
		//magasine.push_back(chargingBall);
		//setAnimation(magasine.back());
		bulletSound->play();
		if (typeTir == gunshotAim)
		{
			chargingBall.setGunShotDistance(referenceStat.maxDistance);
			chargingBall.setBulletSpeed(referenceStat.bulletSpeed);
		}
	}
	chargingBall.isReference = true;
}

chargeShot::chargeShot(AssetManager* asset)
	:Gunslinger()
{
	assets = asset;
}

void chargeShot::weaponControls(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == touche)
		{
			if(isCharging!=true)
			{
				if (bulletClock.getElapsedTime().asSeconds() > 1 / referenceStat.attackSpeed)
				{
				isCharging = true;
				chargingBall = BulletAuto(referenceStat, assets);
				chargingBall.getSprite().setOrigin(0.f, chargingBall.getSprite().getLocalBounds().height / 2.f);
				chargingBall.setBulletPos(utilities::shootPos(pointerToPlayer->getPosition(), pointerToPlayer->getGlobalBounds().width / 2.f, 0));
				chargeClock.restart();
				bulletClock.restart();//ça évite qu'on puisse spam si jamais on veut les dégats minimum
				}
			}
		}
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == touche)
		{
			isCharging = false;
			sendBullet();
		}
	}
}

void chargeShot::updateWeapon(float dt)
{
	if (isCharging)
	{
		float time = chargeClock.getElapsedTime().asSeconds();
		if (time <0.5f)
		{
			float pourcentage = time / maxChargedTime;
			float scale = 1 + pourcentage * maxPlusScaleFactor;
			chargingBall.getSprite().setScale(scale, scale);
			chargingBall.setDamage((int)referenceStat.bulletDamage * scale);
			std::cout << "damage : " << chargingBall.getDamage() << std::endl;
		}
			chargingBall.setBulletPos(utilities::shootPos(pointerToPlayer->getPosition(), pointerToPlayer->getGlobalBounds().width / 2.f, 0));
	}
	Gunslinger::updateWeapon(dt);
}

void chargeShot::renderWeapon(sf::RenderTarget& target)
{
	Gunslinger::renderWeapon(target);
	if(isCharging)
	chargingBall.renderEntity(target);
}

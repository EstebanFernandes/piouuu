#include "Mannequin.h"

void Mannequin::updateEtat(int& etat)
{
	switch (etat)
	{
	case 0:
		getSprite().setTexture(assets->GetTexture("sb"));
		anim = Animation(getPointerSprite(), sf::Vector2i(73, 79),4 , 0.3f, 5);
		break;
	case 1:
		onAvance = true;
		getSprite().setTexture(assets->GetTexture("micelsb"));
		anim = Animation(getPointerSprite(), sf::Vector2i(85, 260), 8, 0.3f, 12);
		anim.changeIntRect(sf::Vector2i(1,0), sf::Vector2i(87, 260));
		anim.changeIntRect(sf::Vector2i(2, 0), sf::Vector2i(87, 260));
		anim.changeIntRect(sf::Vector2i(3, 0), sf::Vector2i(87, 260));
		anim.changeIntRect(sf::Vector2i(4, 0), sf::Vector2i(87, 260));
		anim.changeIntRect(sf::Vector2i(5,0), sf::Vector2i(87, 260));
		anim.changeIntRect(sf::Vector2i(6,0), sf::Vector2i(87, 260));
		anim.changeIntRect(sf::Vector2i(7,0), sf::Vector2i(87, 260));
		getSprite().setColor(sf::Color::White);
		isInvulnerable = true;
		break;
	case 2 :
		onAvance = true;
		sf::FloatRect globalBounds(getGlobalBounds());
		sf::Vector2f pos(getPosition());
		getSprite().setTexture(assets->GetTexture("micel"));
		anim = Animation(getPointerSprite(), sf::Vector2i(87, 108), 2, 0.3f, 6);

		setPosition(pos.x, globalBounds.top+(getGlobalBounds().height/2.f));
		maxHealthPoint = 5000;
		healthPoint = maxHealthPoint;
		isDead = false;
		isInvulnerable = true;
		break;
	}
	getSprite().setScale(2.f, 2.f);
}

void Mannequin::setAssets(AssetManager* asset)
{
	assets = asset;
	etatmannequin = 0;
	updateEtat(etatmannequin);
	setPosition((float)Engine::SCREEN_WIDTH * 0.75f, (float)Engine::SCREEN_HEIGHT * 0.5f);
	
	minHeight = getPosition().y - 100.f;
	maxHeight = minHeight + 200.f;
	
	color = sf::Color(255, 255, 255);
}

Mannequin::Mannequin(AssetManager* asset_)
{
	setAssets(asset_);
}

void Mannequin::updateMovement(float delta)
{
	if (isGoingUp)
	{
		if (getPosition().y <= minHeight)
			isGoingUp = false;
	}
	else
		if (getPosition().y >= maxHeight)
			isGoingUp = true;
	sf::Vector2f dir;
	if (isGoingUp)
		dir.y = -1.f;
	else
		dir.y = 1.f;
	if(onAvance)
	getSprite().move(speed * dir);
}

void Mannequin::enemyShoot()
{
}

void Mannequin::updateEntity(float delta)
{
	updateMovement(delta);
	anim.updateAnimation();
	if (isDead&&etatmannequin==0)
	{
		etatmannequin++;
		updateEtat(etatmannequin);

	}
	else if(etatmannequin==1){
		int actual = anim.getCurrentFrameNumber().x;
		if (last !=0&& actual == 0)
		{
			etatmannequin++;
			updateEtat(etatmannequin);
		}
		last = actual;
	}
	if (hasBeenHit)
	{
		color.g = 255-(int)(255.f * 1.f / (healthPoint / maxHealthPoint));
		color.b = color.g;
		if(etatmannequin==0)
		getSprite().setColor(color);
		std::cout << color.r << std::endl;
		hasBeenHit = false;
	}
}

void Mannequin::renderEntity(sf::RenderTarget& target)
{
	target.draw(getSprite());
}

void Mannequin::updatewPlayer(float delta, Player& player)
{
	if (player.getMainWeapon()->checkCollisions(*this)) {
		if(etatmannequin==0)reduceHP((float)player.getDamagePerBullet());
	}
	if (player.getSecondaryWeapon()->checkCollisions(*this)) {
		if (etatmannequin == 0)reduceHP((float)player.getDamagePerBullet());
	}
	if (healthPoint <= 0)
	{
		isDead = true;
		onAvance = false;
		deleteBuffs();
	}
}



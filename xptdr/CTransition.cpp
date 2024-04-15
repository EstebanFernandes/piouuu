#include "CTransition.h"
#include <iostream>

CTransition::CTransition()
{
	asset = NULL;
	sens = NULLTRANSITION;
}

bool CTransition::globalCollision()
{
	sf::FloatRect currentBounds = backTransi.getGlobalBounds();
	if (currentBounds.left + currentBounds.width<0 ||
		currentBounds.left>asset->sCREEN_WIDTH ||
		currentBounds.top + currentBounds.height < 0
		|| currentBounds.top>asset->sCREEN_HEIGHT)
		return true;
	return false;
}


CTransition::CTransition(CAssetManager* a, SENS_TRANSITION param, float time_)
{
	asset = a;
	sens = param;
	time = time_;
}

void CTransition::initTransition()
{
		clock.restart();
	if (transiState == 1)//Si la transition est à 1 c'est qu'on a déjà fait  un tour, donc on part en sens inverse
	{
		switch (sens)
		{
		case GAUCHE:
		case DROITE:
		case HAUT:
		case BAS:
			dir = dir*-1.f;
			break;
		case MILIEU:
			dir = sf::Vector2f(0, 0);
			//On verra
			break;
		case NULLTRANSITION:
			dir = sf::Vector2f(0, 0);
			speed = 0.f;
			break;
		}
		transiouuuuu = true;
	}
	else if(sens!=NULLTRANSITION)
	{
		backTransi = sf::RectangleShape(sf::Vector2f(asset->sCREEN_WIDTH * 2.f, asset->sCREEN_HEIGHT * 2.f));
		backTransi.setFillColor(sf::Color::Black);
		switch (sens)
		{
		case GAUCHE:
			backTransi.setPosition(-backTransi.getSize().x, 0.f);
			dir = sf::Vector2f(1, 0);
			speed = asset->sCREEN_WIDTH / (time * 60.f);
			break;
		case DROITE:
			backTransi.setPosition((float)asset->sCREEN_WIDTH, 0.f);
			dir = sf::Vector2f(-1, 0);
			speed = asset->sCREEN_WIDTH / (time * 60.f);
			break;
		case HAUT:
			backTransi.setPosition(0.f, -backTransi.getSize().y);
			dir = sf::Vector2f(0, 1);
			speed = asset->sCREEN_HEIGHT / (time * 60.f);
			break;
		case BAS:
			backTransi.setPosition((float)asset->sCREEN_HEIGHT, 0.f);
			dir = sf::Vector2f(0, -1);
			speed = asset->sCREEN_HEIGHT / (time * 60.f);
			break;
		case MILIEU:
			dir = sf::Vector2f(0, 0);
			//On verra
			break;
		}
		transiouuuuu = true;
	}
}

bool CTransition::updateTransition(float delta)
{
	alreadyBeenRendered = false; //Permet de jouer avec la transition, la rendre avant le draw etc
	if(clock.getElapsedTime().asSeconds()<time)
	{
		return false;
	}
		if (transiState == 0)
			transiState = 1;
		else
			transiState = 2;
		transiouuuuu = false;
	return true;

}

void CTransition::renderTransition(sf::RenderWindow& window)
{
	if(sens!=NULLTRANSITION&&alreadyBeenRendered==false)
	{
		backTransi.move(dir * speed);
		window.draw(backTransi);
		alreadyBeenRendered = true;
	}
}

void CTransition::switchSens(SENS_TRANSITION newSens)
{
	if(!transiouuuuu)
		sens = newSens;
}

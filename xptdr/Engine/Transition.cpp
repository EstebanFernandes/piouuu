#include "Transition.h"
#include <iostream>

Engine::Transition::Transition()
{
	asset = NULL;
	sens = NULLTRANSITION;
}

bool Engine::Transition::isFinito()
{
	sf::FloatRect bound = backTransi.getGlobalBounds();
	switch (sens)
	{
	case GAUCHE:
		if (bound.left + bound.width >= Engine::SCREEN_WIDTH)
		{
			return true;
		}
			break;
	case DROITE:
		if (bound.left <= 0.f )
			return true;
		break;
	case HAUT:
		if (bound.top >= 0.f)
			return true;
		break;
	case BAS:
		if (bound.top +bound.height<= 0.f)
			return true;
		break;
	case MILIEU:
		break;
	case NULLTRANSITION:
		break;
	}
	return false;
}

void Engine::Transition::initDirSpeed()
{
	switch (sens)
	{
	case GAUCHE:
		dir = sf::Vector2f(1, 0);
		speed = Engine::SCREEN_WIDTH / (time * 60.f);
		break;
	case DROITE:
		dir = sf::Vector2f(-1, 0);
		speed = Engine::SCREEN_WIDTH / (time * 60.f);
		break;
	case HAUT:
		dir = sf::Vector2f(0, 1);
		speed = Engine::SCREEN_HEIGHT / (time * 60.f);
		break;
	case BAS:
		dir = sf::Vector2f(0, -1);
		speed = Engine::SCREEN_HEIGHT / (time * 60.f);
		break;
	case MILIEU:
		dir = sf::Vector2f(0, 0);
		//On verra
		break;
	}
}


Engine::Transition::Transition(AssetManager* a, SENS_TRANSITION param, float time_)
{
	asset = a;
	sens = param;
	time = time_;
}

Engine::Transition::Transition(AssetManager* a, SENS_TRANSITION param, int state, float time_)
: Transition(a,param,time_)
{
	transiState = state;
	backTransi = sf::RectangleShape(sf::Vector2f((float)Engine::SCREEN_WIDTH, (float)Engine::SCREEN_HEIGHT));
	backTransi.setFillColor(sf::Color::Black);
}

void Engine::Transition::initTransition()
{
		clock.restart();
	if (transiState == 1)//Si la transition est à 1 c'est qu'on a déjà fait  un tour, donc on part en sens inverse
	{
		switch (sens)
		{
		case GAUCHE:
			backTransi.setPosition(0.f,0.f);
			sens = DROITE;
			break;
		case DROITE:
			sens = GAUCHE;
			break;
		case HAUT:
			sens = BAS;
			break;
		case BAS:
			sens = HAUT;
			break;
		case MILIEU:
			break;
		case NULLTRANSITION:
			break;
		}
		transiouuuuu = true;
		initDirSpeed();
	}
	else if(sens!=NULLTRANSITION)
	{
		backTransi = sf::RectangleShape(sf::Vector2f((float)Engine::SCREEN_WIDTH, (float)Engine::SCREEN_HEIGHT));
		backTransi.setFillColor(sf::Color::Black);
		switch (sens)
		{
		case GAUCHE:
			backTransi.setPosition(-backTransi.getSize().x, 0.f);
			dir = sf::Vector2f(1, 0);
			speed = Engine::SCREEN_WIDTH / (time * 60.f);
			break;
		case DROITE:
			backTransi.setPosition((float)Engine::SCREEN_WIDTH, 0.f);
			dir = sf::Vector2f(-1, 0);
			speed = Engine::SCREEN_WIDTH / (time * 60.f);
			break;
		case HAUT:
			backTransi.setPosition(0.f, -backTransi.getSize().y);
			dir = sf::Vector2f(0, 1);
			speed = Engine::SCREEN_HEIGHT / (time * 60.f);
			break;
		case BAS:
			backTransi.setPosition((float)Engine::SCREEN_HEIGHT, 0.f);
			dir = sf::Vector2f(0, -1);
			speed = Engine::SCREEN_HEIGHT / (time * 60.f);
			break;
		case MILIEU:
			dir = sf::Vector2f(0, 0);
			//On verra
			break;
		}
		transiouuuuu = true;
	}
}

bool Engine::Transition::updateTransition(float delta)
{
	alreadyBeenRendered = false; //Permet de jouer avec la transition, la rendre avant le draw etc
	if(clock.getElapsedTime().asSeconds()>=time&& isFinito())
	{
		if (transiState == 0)
			transiState = 1;
		else
			transiState = 2;
		transiouuuuu = false;
	return true;
	}

	backTransi.move(dir * speed);
	return false;

}

void Engine::Transition::renderTransition(sf::RenderTarget& window)
{
	if(sens!=NULLTRANSITION&&alreadyBeenRendered==false)
	{
		window.draw(backTransi);
		alreadyBeenRendered = true;
	}
}

void Engine::Transition::switchSens(SENS_TRANSITION newSens)
{
	if(!transiouuuuu)
		sens = newSens;
}

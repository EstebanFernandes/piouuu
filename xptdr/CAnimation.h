#pragma once
#include"SFML/Graphics.hpp"
#include<iostream>
//Classe qui permet de gérer les animations sur un sprite
class CAnimation
{
private:
	//Pointeur sur le sprite
	sf::Sprite* currentSprite;
	//Taille de chaque frame de la texture
	sf::IntRect currentFrame;
	//Horloge pour gérer le temps entre chaque frame
	sf::Clock animationTimer;
	//Temps entre deux frames
	float timeBetweenFrames;
	//Nombre de frame total
	int NumberofFrame;
	//Current frame nombre
	int currentFrameNumber;
public:
	CAnimation() {
		currentSprite = nullptr;
		NumberofFrame = -1;
		currentFrameNumber = -1;
		timeBetweenFrames = 0.f;
	}
	CAnimation(sf::Sprite* sprit,sf::IntRect textframe, int nbframe,float time)
	{
		currentSprite = sprit;
		currentFrame = textframe;
		NumberofFrame = nbframe;
		currentFrameNumber = 0;
		timeBetweenFrames = time;
	}
	void updateAnimation() {
		if (currentFrameNumber == NumberofFrame)
			currentFrameNumber = 0;
		if (animationTimer.getElapsedTime().asSeconds() > timeBetweenFrames)
		{
			currentFrame.left = currentFrameNumber * currentFrame.width;
			currentSprite->setTextureRect(currentFrame);
			currentFrameNumber++;
			animationTimer.restart();
		}
	}
};


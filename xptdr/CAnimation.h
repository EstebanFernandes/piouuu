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
	//Nombre de frame total sur la spritesheet
	int NumberofFrame;
	//Current frame nombre
	int currentXFrameNumber;
	//Intervalle sur lequel on doit se déplacer verticalement sur la spritesheet (de base  à 0 s'il n'y a qu'une couche sur la spritesheet)
	int highFrameNumber = -1;
	int lowFrameNumber = -1;
	int currentYFrameNumber=0;

public:
	//Constructeur par défaut
	CAnimation() {
		currentSprite = nullptr;
		NumberofFrame = -1;
		currentXFrameNumber = -1;
		timeBetweenFrames = 0.f;
	}
	//Constructeur de confort
	CAnimation(sf::Sprite* sprit,sf::IntRect textframe, int nbframe,float time)
	{
		currentSprite = sprit;
		currentFrame = textframe;
		NumberofFrame = nbframe;
		currentXFrameNumber = 0;
		timeBetweenFrames = time;
	}
	void updateAnimation() {
		if (currentXFrameNumber == NumberofFrame)
			currentXFrameNumber = 0;
		if (animationTimer.getElapsedTime().asSeconds() > timeBetweenFrames)
		{
			currentFrame.left = currentXFrameNumber * currentFrame.width;
			currentFrame.top = currentYFrameNumber * currentFrame.height;
			currentSprite->setTextureRect(currentFrame);
			currentXFrameNumber++;
			animationTimer.restart();
		}
	}
	void setDifferentAnimation(int t) {
		currentYFrameNumber=t;
	}
	void resetAnimation() {
		currentYFrameNumber=0;
	}
	int getCurrentYFrameNumber() {
		return currentYFrameNumber;
	}
};


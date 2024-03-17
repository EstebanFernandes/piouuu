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
	bool isHorizontal = true;
	//Pixelbetween two frames (default = 0)
	int pxbetFrames = 0;
	//Constructeur par défaut
	CAnimation() 
	{
		currentSprite = NULL;
		NumberofFrame = -1;
		currentXFrameNumber = -1;
		timeBetweenFrames = 0.f;
	}
	//Constructeur de confort
	CAnimation(sf::Sprite* sprit,sf::IntRect textframe, int nbframe,float time) : 
		currentFrame(textframe),
		NumberofFrame(nbframe),
		timeBetweenFrames(time)
	{
		currentSprite = sprit;
		currentSprite->setOrigin(currentFrame.width / 2.f, currentFrame.height / 2.f);
		currentXFrameNumber = 0;
		switchFrames();
	}
	void setTimeBetweenFrames(float time)
	{
		if (time < 0.f)
			timeBetweenFrames = time;
	}
	void setSprite(sf::Sprite* sprit)
	{
		currentSprite = sprit;
	}
	void setParameters(sf::Sprite* sprit, sf::IntRect textframe, int nbframe, float time) 
	{
		currentSprite = sprit;
		currentFrame = textframe;
		NumberofFrame = nbframe;
		timeBetweenFrames = time;
		currentXFrameNumber = 0;
		switchFrames();
	}

	void updateAnimation() {
		int* tempPointer = NULL;
		if (isHorizontal)
		{
			tempPointer = &currentXFrameNumber;
		}
		else {
			tempPointer = &currentYFrameNumber;
		}
		if (*tempPointer == NumberofFrame)
			*tempPointer = 0;
		if (animationTimer.getElapsedTime().asSeconds() > timeBetweenFrames)			{
			switchFrames();
			*tempPointer= *tempPointer+1;
			animationTimer.restart();
		}
	}
	void debug()
	{
		std::cout << currentFrame.left << " " << currentFrame.top
			<< " " << currentFrame.width << " " << currentFrame.height << std::endl;
	}
	void switchFrames() {
			currentFrame.left = currentXFrameNumber * currentFrame.width+pxbetFrames*currentXFrameNumber;
			currentFrame.top = currentYFrameNumber * currentFrame.height + pxbetFrames * currentYFrameNumber;
			currentSprite->setTextureRect(currentFrame);
	}
	void setDifferentAnimation(int t) {
		currentYFrameNumber=t;
		switchFrames();
	}
	void resetAnimation() {
		currentYFrameNumber=0;
	}
	int getCurrentYFrameNumber() {
		return currentYFrameNumber;
	}
	

	sf::Sprite* getSprite() {
		return currentSprite;
	}
	sf::IntRect* getCurrentFrame() { return &currentFrame; }
	int getCurrentFrameNumber()
	{
		if (isHorizontal)
			return currentXFrameNumber;
		return currentYFrameNumber;
	}
	int getMaxFrame()
	{
		return NumberofFrame;
	}
};


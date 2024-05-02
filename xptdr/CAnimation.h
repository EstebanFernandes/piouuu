#pragma once
#include"SFML/Graphics.hpp"
#include<iostream>
//Classe qui permet de gérer les animations sur un sprite
	typedef std::vector<std::vector<sf::IntRect>> matrixSpriteSheet;
class CAnimation
{
private:
	//Pointeur sur le sprite
	sf::Sprite* currentSprite;

	matrixSpriteSheet matrix;
	//Où on est sur la spritesheet
	sf::Vector2i currentFrame;
	//Horloge pour gérer le temps entre chaque frame
	sf::Clock animationTimer;
	//Temps entre deux frames
	float timeBetweenFrames;
	//Nombre de frames total sur la spritesheet x = sur le temps et en y c'est selon des trucs spéciaux
	sf::Vector2i NumberofFrame;


public:
	bool isHorizontal = true;
	//Pixelbetween two frames (default = 0)
	int pxbetFrames = 0;
	//Constructeur par défaut
	CAnimation() 
	{
		currentSprite = NULL;
		timeBetweenFrames = 0.f;
	}
	/// <summary>
	/// Constructeur de confort
	/// </summary>
	/// <param name="sprit">un pointeur vers le sprite</param>
	/// <param name="textframe">frame (on considère pour l'initialisation que c'est la même partout)</param>
	/// <param name="nbframe">on précise  le nombre, en x et en y de la spritesheet</param>
	/// <param name="time">temps entre chaque frale</param>
	/// <param name="pxbFrame"> pixel entre 2 frame, 0 par défaut</param>
	CAnimation(sf::Sprite* sprit,sf::Vector2i textframe, sf::Vector2i nbframe,float time,int pxbFrame = 0) : 
		NumberofFrame(nbframe),
		timeBetweenFrames(time),
		pxbetFrames(pxbFrame)
	{
		currentFrame.x = 0;
		currentFrame.y = 0;
		sf::IntRect temp(sf::Vector2i(0, 0), textframe);
		for (int i = 0; i < nbframe.x; i++)
		{
			matrix.push_back(std::vector<sf::IntRect>(nbframe.y, temp));
		}
		//matrix = matrixSpriteSheet(nbframe.x, std::vector<sf::IntRect>(nbframe.y,temp));
		currentSprite = sprit;
		currentSprite->setOrigin(matrix[currentFrame.x][currentFrame.y].width / 2.f, matrix[currentFrame.x][currentFrame.y].height / 2.f);
		computeMatrix();
		switchFrames();
	}

	CAnimation(sf::Sprite* sprit, sf::Vector2i frame, int nbframe, float time, int pxbFrame = 0)
		:CAnimation(sprit,frame,sf::Vector2i(nbframe,1),time,pxbFrame)
	{
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
	void setParameters(sf::Sprite* sprit, sf::Vector2i frame, int nbframe, float time,int pxBframe = 0)
	{
		setParameters(sprit, frame, sf::Vector2i(nbframe, 1), time);
	}
	void setParameters(sf::Sprite* sprit, sf::Vector2i frame, sf::Vector2i nbframe, float time, int pxBframe = 0)
	{
		NumberofFrame = nbframe;
		pxbetFrames = pxbetFrames;
		currentFrame.x = 0;
		currentFrame.y = 0;
		sf::IntRect temp(sf::Vector2i(0, 0), frame);
		matrix = matrixSpriteSheet(nbframe.x, std::vector<sf::IntRect>(nbframe.y, temp));
		currentSprite = sprit;
		currentSprite->setOrigin(matrix[currentFrame.x][currentFrame.y].width / 2.f, matrix[currentFrame.x][currentFrame.y].height / 2.f);
		computeMatrix();
		switchFrames();
	}

	void updateAnimation() {
		if (timeBetweenFrames != -1)
		{
			int* tempPointer = NULL;
			int maxFrame;
			if (isHorizontal)
			{
				tempPointer = &currentFrame.x;
				maxFrame = NumberofFrame.x;
			}
			else {
				tempPointer = &currentFrame.y;
				maxFrame = NumberofFrame.y;
			}
			if (animationTimer.getElapsedTime().asSeconds() > timeBetweenFrames)			{
				switchFrames();
					*tempPointer= *tempPointer+1;
				if (*tempPointer == maxFrame)
					*tempPointer = 0;
				animationTimer.restart();
			}
		}
	}
	void setAxes(bool isHorizontal_)
	{

	}
	void switchFrames() {
			currentSprite->setTextureRect(matrix[currentFrame.x][currentFrame.y]);
	}
	void setDifferentAnimation(int t) {
		if(currentFrame.y!=t)
		{
			currentFrame.y = t;
			switchFrames();
		}
	}
	void resetAnimation() {
		currentFrame.y=0;
	}
	sf::Vector2i getCurrentFrameNumber() {
		return currentFrame;
	}
	

	sf::Sprite* getSprite() {
		return currentSprite;
	}
	sf::IntRect* getCurrentFrame() { return &matrix[currentFrame.x][currentFrame.y]; }
	void setcurrentXFrameNumber(int i)
	{
		currentFrame.x = i;
		switchFrames();
	}
	void setcurrentYFrameNumber(int i)
	{
		currentFrame.y = i;
		switchFrames();
	}
	sf::Vector2i getMaxFrame()
	{
		return NumberofFrame;
	}
	void computeMatrix()
	{
		int curX=0;
		for (int i = 0; i < matrix.size(); i++)
		{
			int curY = 0;
			for (int j = 0; j < matrix[i].size(); j++)
			{
				sf::IntRect& currentRect = matrix[i][j];
				currentRect.left = curX;
				currentRect.top = curY;
				curY += currentRect.height + pxbetFrames;
			}
			curX += matrix[i][0].width + pxbetFrames;
		}
	}
	/// <summary>
	/// Change le rectangle pour la position indiquée
	/// </summary>
	/// <param name="pos">attention la position est entre 0 et numberofframe-1</param>
	/// <param name="size"></param>

	void changeIntRect(sf::Vector2i pos, sf::Vector2i size)
	{
		matrix[pos.x][pos.y].width = size.x;
		matrix[pos.x][pos.y].height = size.y;
		computeMatrix();
	}
	/// <summary>
	/// Change le rectangle pour toute la ligne ou la colonne (si le booleen vaut true)
	/// </summary>
	/// <param name="pos">attention la position est entre 0 et numberofframe-1</param>
	/// <param name="size"></param>
	/// <param name="isLine"></param>
	void changeIntRect(int pos, sf::Vector2i size,bool isLine=true)
	{
		if (isLine == true)
		{
			for (int i = 0; i <NumberofFrame.x;i++)
			{
				matrix[i][pos].width = size.x;
				matrix[i][pos].height = size.y;
			}
		}
		else
		{
			for (int j = 0; j < NumberofFrame.y; j++)
			{
				matrix[pos][j].width = size.x;
				matrix[pos][j].height = size.y;
			}
		}
		computeMatrix();
	}
};


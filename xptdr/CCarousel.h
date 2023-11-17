#pragma once
#define LeftMove true
#define RightMove false
#include"EllipseShape.h"
#include"CCard.h"
//Permet de créer un carousel pour afficher les personnages 
class CCarousel : public sf::Drawable 
{
public:
	//cette horloge sert à limiter la vitesse de défilement carousel
	sf::Clock carouselClock;
	EllipseShape ellipse;
	//Deux booléen pour le mouvement
	bool isMovingLeft;
	bool isMovingRight;
	//Index de chaque carte du carousel
	std::vector<int> currentIndex;
	//Destination de chaque carte du carousel
	std::vector<int> nextIndex;
	//Définit L'espacement entre les cartes 
	int plusIndex;
	//Liste qui contient les cartes
	std::vector<CCard> cards;

	bool isEllipseVisible = true;
	CCarousel()
	{
		isMovingLeft = false;
		isMovingRight = false;
		ellipse = EllipseShape(sf::Vector2f(400.f, 100.f));
		ellipse.setPosition(200.f, 200.f);
	}
	void addCard(CCard card) {
		cards.push_back(card);
		size_t nbEntity = (int)cards.size();
		size_t maxPoint = (int)ellipse.getPointCount();
		size_t n = maxPoint / nbEntity;
		ellipse.setPointCount(n*nbEntity);
		currentIndex.push_back(0);
		int newMax = (int)ellipse.getPointCount();
		for (int i = 0; i<nbEntity; i++)
		{
			currentIndex[i] = 100 + i * (int) n;
			if (currentIndex[i] >= newMax)
				currentIndex[i] -= newMax;
		}
		plusIndex = (int)n;
		nextIndex = currentIndex;
	}
	void move( bool Direction = LeftMove) {
		int plusoumoins = 0;
		if(Direction== LeftMove)
		{
			isMovingLeft = true;
			isMovingRight = false;
			plusoumoins++;

		}
		else {
			isMovingLeft = false;
			isMovingRight = true;
			plusoumoins--;
		}
		for (int i = 0; i < nextIndex.size(); i++)
		{
			nextIndex[i] += plusoumoins*plusIndex;
			if (nextIndex[i] >= (int)ellipse.getPointCount())
				nextIndex[i] -= (int)ellipse.getPointCount();
			else if (nextIndex[i] < 0)
				nextIndex[i] += (int)ellipse.getPointCount();
		}
	}
	void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		if(isEllipseVisible)
			target.draw(ellipse);
		std::vector<int> temp(currentIndex);
		int maxPoint = (int)ellipse.getPointCount();
		for (int i = 0; i < temp.size(); i++)
				temp[i] = abs(temp[i] - maxPoint / 2);
		for(int i=0;i<cards.size();i++)
		{ 
			int max = 0;
			int index = 0;
			for (int i = 0; i < temp.size(); i++)
			{
				if (max < temp[i])
				{
					max = temp[i];
					index = i;
				}
			}
			target.draw(cards[index]);
			temp[index] = 0;
		}
	}
	void update(float deltaTime) {
		bool ismoving = false;
		int plusoumoins = 0;
		if (isMovingLeft)
			plusoumoins++;
		else if (isMovingRight)
			plusoumoins--;
		int maxPoint = (int)ellipse.getPointCount();
		for (int i = 0; i < cards.size(); i++)
		{
			int nextindex = nextIndex[i];
			if (nextindex >= maxPoint)
				nextindex -= maxPoint-1;

			int& curIndex = currentIndex[i];
			if (carouselClock.getElapsedTime().asSeconds() > 0.003f && nextindex!=curIndex )
			{
				ismoving = true;
				curIndex += plusoumoins;
			}
			if (curIndex == maxPoint)
				curIndex = 0;
			else if (curIndex == -1)
				curIndex = maxPoint - 1;
				//SetScale of point
				float scaleNumber = 1.f;
				if (curIndex > maxPoint / 2)
					scaleNumber = abs(curIndex - maxPoint) / (float)(maxPoint / 2);
				else if (curIndex == 0)
					scaleNumber = 1.f / maxPoint;
				else
					scaleNumber = curIndex / (float)(maxPoint / 2);
				scaleNumber = 0.7f * scaleNumber;
				cards[i].setScale(0.3f + scaleNumber, 0.3f + scaleNumber);
				cards[i].setPosition(sf::Vector2f(ellipse.getPoint(curIndex).x + ellipse.getGlobalBounds().left - cards[i].getGlobalBounds().width / 2,
					ellipse.getPoint(curIndex).y + ellipse.getGlobalBounds().top));
		}
		if(ismoving)
				carouselClock.restart();
		
	}

	//fonction qui renvoie la carte selectionné, si on est en mouvement 
	CCard* getselectedCard()
	{
		for (int i = 0; i < currentIndex.size(); i++)
		{
			if (currentIndex[i] == 100)
				return &cards[i];
		}
		return NULL;
	}

	void setCarouselPosition(sf::Vector2f a)
	{
		ellipse.setPosition(a);
	}
	//l'argument pris correspond au rayon horizontal et vertical de l'ellipse
	void setSize(sf::Vector2f r)
	{
		ellipse.setRadius(r);
	}
	void setEllipseVisibility(bool r)
	{
		isEllipseVisible = r;
	}
};


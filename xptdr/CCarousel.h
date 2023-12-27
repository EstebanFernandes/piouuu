#pragma once
#define LeftMove false
#define RightMove true
#include"EllipseShape.h"
#include"CCard.h"
//Permet de créer un carousel pour afficher les personnages 
class CCarousel : public sf::Drawable 
{
private:
	int maxPoint;
	void setPositionofEntity(int curIndex,int i) {
		CCard& currentCard = cards[i];
		float yPosition = ellipse.getPoint(curIndex).y + ellipse.getGlobalBounds().top;
		float b = ellipse.getPoint((size_t)maxPoint / 2).y+ellipse.getPosition().y;
		float a = b + cardDefaultHeight;
		float z = (a-yPosition  ) / (a-b) * (200 - 100) + 100;
		float scaleNumber = 100 / z;
		scaleNumber = scaleNumber*2.f;
		cards[i].setScale(scaleNumber,scaleNumber);
		cards[i].setPosition(sf::Vector2f(
			ellipse.getPoint(curIndex).x + ellipse.getGlobalBounds().left - cards[i].getGlobalBounds().width / 2,
			yPosition));
		//std::cout << i << " " << scaleNumber<<std::endl;
	}
	float cardDefaultHeight = 0.f;
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
	bool isMoving = false;
	CCarousel()
	{
		isMoving = false;
		isMovingLeft = false;
		isMovingRight = false;
		ellipse = EllipseShape(sf::Vector2f(400.f, 100.f));
		ellipse.setPosition(200.f, 200.f);
		maxPoint = (int)ellipse.getPointCount();
	}
	void addCard(CCard card) {
		cardDefaultHeight = card.getGlobalBounds().height;
		cards.push_back(card);
		size_t nbEntity = (int)cards.size();
		size_t n = (size_t)maxPoint / nbEntity;
		ellipse.setPointCount(n*nbEntity);
		maxPoint = (int)ellipse.getPointCount();
		currentIndex.push_back(0);
		int newMax = (int)ellipse.getPointCount();
		for (int i = 0; i<nbEntity; i++)
		{
			currentIndex[i] = (newMax/2) + i * (int) n;
			if (currentIndex[i] >= newMax)
				currentIndex[i] -= newMax;
			setPositionofEntity(currentIndex[i], i);

		}
		plusIndex = (int)n;
		nextIndex = currentIndex;
	}
	bool move( bool Direction = LeftMove) {
		if (nextIndex[0] != currentIndex[0])
		{
			return false;
		}
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
		isMoving = true;
		return true;
	}
	void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		if(isEllipseVisible)
			target.draw(ellipse);
		std::vector<int> temp(currentIndex);
		for (int i = 0; i < temp.size(); i++)
				temp[i] = abs(temp[i] - maxPoint / 2);
		for(int i=0;i<cards.size();i++)
		{ 
			int max = -1;
			int index = 0;
			for (int j = 0; j < temp.size(); j++)
			{
				if (max < temp[j])
				{
					max = temp[j];
					index = j;
				}
			}
			target.draw(cards[index]);
			temp[index] = -10;
		}
	}
	void update(float deltaTime) {
		int plusoumoins = 0;
		if (isMovingLeft)
		{
			plusoumoins++;
		}
		else if (isMovingRight)
		{
			plusoumoins--;
		}
		if (nextIndex[0] == currentIndex[0])
			isMoving = false;
		if (isMoving) {
			for (int i = 0; i < cards.size(); i++)
			{
				cards[i].update(deltaTime);
				int nextindex = nextIndex[i];
				if (nextindex >= maxPoint)
					nextindex -= maxPoint - 1;

				int& curIndex = currentIndex[i];
				if (carouselClock.getElapsedTime().asSeconds() > 0.003f && nextindex != curIndex)
				{
					curIndex += plusoumoins;
				}
				if (curIndex == maxPoint)
					curIndex = 0;
				else if (curIndex == -1)
					curIndex = maxPoint - 1;
				//SetScale of point
				setPositionofEntity(curIndex, i);
			}
			carouselClock.restart();
		}
		else
		{
			for (int i = 0; i < cards.size(); i++)
				cards[i].update(deltaTime);
		}
	}
	//fonction qui renvoie la carte selectionné, si on est en mouvement 
	CCard* getselectedCard()
	{
		for (int i = 0; i < currentIndex.size(); i++)
		{
			if (currentIndex[i] == (int)ellipse.getPointCount()/2)
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
	sf::FloatRect getGlobalBounds();
	void setCardsScale(sf::Vector2f scale)
	{
		for (int i = 0; i < cards.size(); i++)
		{
			cards[i].setScale(scale);
		}
	}
	void updatePos() {
		for (int i = 0; i < cards.size(); i++)
		{
			int& curIndex = currentIndex[i];
			setPositionofEntity(curIndex, i);
		}
	}
	void displayScale() {
		for (int i = 0; i < cards.size(); i++)
		{
			std::cout << cards[i].getScale().x << " " << cards[i].getScale().y << std::endl;
		}
	}
};


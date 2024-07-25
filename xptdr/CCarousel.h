#pragma once
#define LeftMove false
#define RightMove true
#include"EllipseShape.h"
#include"CCard.h"
#include "SpinningCard.hpp"
//Permet de créer un carousel pour afficher les personnages 
class CCarousel : public sf::Drawable 
{
private:
	const sf::Vector2f sizeOfCard = sf::Vector2f(255, 365.f);
public:
	struct cardHandler {
	public:
		sf::Vector2f finalPos;
		sw::SpinningCard* cardBack;
		sw::SpinningCard* cardMask;
		sw::SpinningCard* cardFace;
		sw::SpinningCard* spriteCard;
		float degree;
		float scale = 1.f;
		bool canMove = false;
		bool drawSprite = false;
		image sprite;
		int pouranim = 0;

		void freeMemory() {
			delete cardBack;
			delete cardFace;
			delete spriteCard;
			delete cardMask;
		}
		void move(sf::Vector2f offset)
		{
			if(canMove)
			{
				cardFace->move(offset);
				cardBack->move(offset);
				cardMask->move(offset);
				sprite.sprite.move(offset);
				spriteCard->move(offset);
			}
		}
		void move(float x, float y)
		{
			move(sf::Vector2f(x, y));
		}
		void setScale(float newScale)
		{
			scale = newScale;
			cardFace->setScale(scale, scale);
			cardBack->setScale(scale, scale);
			cardMask->setScale(scale, scale);
			spriteCard->setScale(scale, scale);
			sprite.sprite.setScale(scale, scale);
		}
		sf::Vector2f getScale() {
			return cardFace->getScale();
		}
		void spin(float spin)
		{
			degree = spin;
			cardFace->spin(spin);
			cardBack->spin(spin);
			cardMask->spin(spin);
			spriteCard->spin(spin);
		}

		void spinVertically(float angleInDegrees) {
			cardFace->spinVertically(angleInDegrees);
			cardBack->spinVertically(angleInDegrees);
			cardMask->spinVertically(angleInDegrees);
			spriteCard->spinVertically(angleInDegrees);
		}
		void setPosition(sf::Vector2f pos)
		{
			cardFace->setPosition(pos);
			cardBack->setPosition(pos);
			cardMask->setPosition(pos);
			spriteCard->setPosition(pos);
			sprite.sprite.setPosition(pos);
		}
		sf::Vector2f getSize() {
			return sf::Vector2f(275.f, 385.f) * scale;
		}
		void draw(sf::RenderTarget& renderTarget,bool drawMask = true) const
		{
			bool backFirst = (degree > 90.f && degree < 270.f) ? true : false;
			if (backFirst)
			{
				renderTarget.draw(*cardBack);
			}
			else {
				renderTarget.draw(*cardBack);
				renderTarget.draw(*cardFace);
				if (drawSprite&& (degree==0.f||degree==360.f))
					renderTarget.draw(sprite.sprite);
				else
				renderTarget.draw(*spriteCard);
			}
			if(drawMask)
			renderTarget.draw(*cardMask);
		}
		void update(float dt) {
			if (sprite.isAnimated) {
				if (pouranim++ == 1)
					sprite.anim.setSprite(&sprite.sprite);
				sprite.anim.updateAnimation();
			}
		}		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="currentIndex">Index compris entre 0 et plusIndex </param>
		/// <param name="totalPoint"> point entre deux position (plusIndex)</param>
		/// <param name="valueRange"></param>
		/// <param name="sens"></param>
		void updateSpin(int currentIndex, int totalPoint,
			int valueRange,bool sens, int pointIndex,int middlePoint=-1.f)
		{
			float perc = 0.f;
			
			if (middlePoint != -1.f)
			{//Dans ce cas sens prend comme valeur l'index du point du milieu (150 ou 50 dans notre cas)
				//On doit regarder par rapport à l'index car au milieu les cartes changent de sens
				int difference = std::abs(pointIndex - middlePoint);
				perc = 1.f - difference / radiusToMiddle;
			}
			else if (currentIndex <= valueRange)
			{
				perc = (float)currentIndex / (float)(valueRange);
			}
			else if (currentIndex >= totalPoint - (valueRange))
			{
				perc = (float)(totalPoint-currentIndex)/ (float)(valueRange);
			}
			else
				perc = 1.f;

			if (currentIndex == totalPoint)
				perc = 0.f;
			float spinDegree = 30.f * perc;

			if (sens == LeftMove)
				spin(360.f - spinDegree);
			else 
			{
				spin(spinDegree);

			}
			
		}

		//Methode qui sert à sauvegarder l'état actuel du sprite
		void saveCardState() {
			sf::Vector2f scale = spriteCard->getScale();
			sf::Vector2f pos = spriteCard->getPosition();
			delete spriteCard;
			spriteCard = new sw::SpinningCard(sprite.sprite);
			spriteCard->spin(degree);
			spriteCard->setScale(scale);
			spriteCard->setPosition(pos);
		}
		sf::Vector2f getPosition() 
		{
			return cardBack->getPosition();
		}
	};
	private:
	sf::Texture cardTexture;
	sf::Texture backCardTexture;
	int maxPoint;
	static const int radiusToMiddle = 5;
	void setScaleRelativeToPoint(int pointIndex, int index)
	{

		cardHandler& currentCard = cards[index];
		sf::Vector2f pos = ellipse.getPoint(pointIndex);
		pos += sf::Vector2f(ellipse.getGlobalBounds().left, ellipse.getGlobalBounds().top);
		//Fake a z axis to handle the correct scaling of the card
		float b = ellipse.getPoint((size_t)maxPoint / 2).y + ellipse.getGlobalBounds().top;
		float a = b + cardDefaultHeight;
		float z = (a - pos.y) / (a - b) * (200 - 100) + 100;
		float scaleNumber = 100 / z;
		scaleNumber = scaleNumber * 2.f;
		cards[index].setScale(scaleNumber);
	}

	void setPositionofEntity(int curIndex,int i) {
		//Set position of everything
		
		cardHandler& currentCard = cards[i];
		sf::Vector2f pos = ellipse.getPoint(curIndex);
		pos += sf::Vector2f(ellipse.getGlobalBounds().left, ellipse.getGlobalBounds().top);
		setScaleRelativeToPoint(curIndex, i);
		cards[i].setPosition(pos);
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
	std::vector<cardHandler> cards;
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
	~CCarousel(){}
	//The list should be well design
	void addCards(std::vector<CCard>& cardList)
	{

		backCardTexture.loadFromFile("res/img/backCard.png");
		//On crée les cartes et la texture associé
		sf::Vector2f completeSizeOfCard(275.f, 385.f);
		sf::Vector2f sizeOfCard(255.f, 365.f);
		sf::RenderTexture renderTexture;
		renderTexture.create((int)sizeOfCard.x * (int)(cardList.size()), (int)sizeOfCard.y);
		renderTexture.clear();
		for (int i = 0; i < cardList.size(); i++)
		{
			renderTexture.draw(cardList[i]);
		}
		renderTexture.display();
		cardTexture = renderTexture.getTexture();



		cardDefaultHeight = sizeOfCard.y+20.f;
		size_t nbEntity = (int)cardList.size();
		size_t n = (size_t)maxPoint / nbEntity;
		ellipse.setPointCount(n * nbEntity);
		maxPoint = (int)ellipse.getPointCount();
		for (int i = 0; i < nbEntity; i++)
		currentIndex.push_back(0);
		int newMax = (int)ellipse.getPointCount();
		for (int i = 0; i < nbEntity; i++)
		{
			currentIndex[i] = (newMax / 2) + i * (int)n;
			if (currentIndex[i] >= newMax)
				currentIndex[i] -= newMax;
			sf::Vector2f pos = ellipse.getPoint(currentIndex[i]);
			pos += sf::Vector2f(ellipse.getGlobalBounds().left, ellipse.getGlobalBounds().top);
			sf::Sprite spriteCard(cardTexture)
				, backSpriteCard(backCardTexture)
				, cardMask(backCardTexture);
			spriteCard.setTextureRect(
				sf::IntRect(
					sf::Vector2i((int)sizeOfCard.x * i, 0), sf::Vector2i(sizeOfCard)));
			utilities::centerObject(spriteCard);
			utilities::centerObject(backSpriteCard);
			utilities::centerObject(cardMask);
			cardMask.setColor(sf::Color(0, 0, 0, 100));
			cardHandler tempCard;
			tempCard.finalPos = pos;
			sf::Vector2i frame(153, 66);
			tempCard.sprite.sprite.setTexture(*cardList[i].getSprite().getTexture());
			tempCard.sprite.sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), frame));
			tempCard.sprite.anim = CAnimation(&tempCard.sprite.sprite, frame, 4, 0.16f);
			tempCard.sprite.isAnimated = true;
			tempCard.canMove = true;

			tempCard.cardBack = new sw::SpinningCard(backSpriteCard);
			tempCard.cardFace = new sw::SpinningCard(spriteCard);
			tempCard.spriteCard = new sw::SpinningCard(tempCard.sprite.sprite);
			tempCard.cardMask = new sw::SpinningCard(cardMask);
			//Les cartes commencent retournées
			tempCard.spin(180.f);
			sf::Vector2f moveTo(-sizeOfCard.x ,pos.y);
			tempCard.setPosition(moveTo);
			cards.push_back(tempCard);
			setScaleRelativeToPoint(currentIndex[i], i);
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
			if(i==cards.size()-1)
				cards.at(index).draw(target,false);
			else
				cards.at(index).draw(target);
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
			int dividedBy = 10;
			int valueRange = plusIndex / dividedBy;
			while (valueRange == 0)
			{
				dividedBy--;
				valueRange = plusIndex / dividedBy;
			}

			for (int i = 0; i < cards.size(); i++)
			{
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
				int totalTillNextPos = 0;
				//Si on va vers la gauche (en fixant le fond) et qu'on passe sur le milieu

				if (plusoumoins == -1&& nextindex+plusIndex>maxPoint)
				{
					if (curIndex > maxPoint - plusIndex) //On est entre next index et maxPoint
						totalTillNextPos = plusIndex - std::abs(nextIndex[i] - currentIndex[i]);
					else //on est entre 0 et plusIndex
						totalTillNextPos = curIndex + (nextindex + plusIndex) % maxPoint;
				}
				else if(plusoumoins==1 && nextindex - plusIndex  < 0) {

					if (curIndex > maxPoint - plusIndex) //On est entre next index et maxPoint
					{
						totalTillNextPos = std::abs(curIndex - maxPoint);
						totalTillNextPos += nextindex;
					}
					else //on est entre 0 et plusIndex
						totalTillNextPos = plusIndex - std::abs(nextIndex[i] - currentIndex[i]);
				}
				else {
					totalTillNextPos = plusIndex- std::abs(nextIndex[i] - currentIndex[i]);
				}
				bool sens = (plusoumoins == 1) ? RightMove : LeftMove;
				int middleValue = (curIndex > maxPoint / 2) ? maxPoint * 3 / 4 : maxPoint / 4;
				bool oui = false;
				if (
					utilities::isNumberBetween((maxPoint / 4) - radiusToMiddle, (maxPoint / 4) + radiusToMiddle, curIndex) ||
					utilities::isNumberBetween((maxPoint * 3 / 4) - radiusToMiddle, (maxPoint * 3 / 4) + radiusToMiddle, curIndex))
				{
					oui = true;
				}

				 if (curIndex <= maxPoint/4 || curIndex>=maxPoint*3/4)
				{
					sens = !sens;
				}

				 if(oui)
					cards[i].updateSpin(totalTillNextPos, plusIndex,valueRange,sens,currentIndex[i],middleValue);
				 else
					 cards[i].updateSpin(totalTillNextPos, plusIndex, valueRange, sens, currentIndex[i]);

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

	void setCarouselPosition(sf::Vector2f a)
	{
		ellipse.setPosition(a);
	}
	//l'argument pris correspond au rayon horizontal et vertical de l'ellipse
	void setSize(sf::Vector2f r)
	{
		ellipse.setRadius(r);
		utilities::centerObject(ellipse);
	}
	void setEllipseVisibility(bool r)
	{
		isEllipseVisible = r;
	}
	sf::FloatRect getGlobalBounds();
	void setCardsScale(sf::Vector2f scale)
	{
		//à refaire parce que là c'est nul
		for (int i = 0; i < cards.size(); i++)
		{
			cards[i].setScale(scale.x);
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
	void updateCurrentSelectedCard(int curIndex)
	{
		if (curIndex >= 0 && curIndex < cards.size())
		{
			for (int i = 0; i < cards.size(); i++)
			{
				cards[i].drawSprite = (i == curIndex) ? true : false;
			}
		}
	}
};


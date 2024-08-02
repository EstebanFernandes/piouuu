#pragma once
class lifeForEntity
{
protected:
	int maxhealth;
	int iENTLifePoint;
public:
	int getMaxHealth() { return maxhealth; }
	int getLifePoint() { return iENTLifePoint; }
	void reduceHP(int damage) {
		iENTLifePoint -= damage;
		if (iENTLifePoint < 0)
			iENTLifePoint = 0;
		else if (iENTLifePoint > maxhealth)
			iENTLifePoint = maxhealth;
	}
};


#pragma once
#include "Player.h"
//entité qui doivent rentrer en collision avec le joueur.
class HittingEntity : public Mob, public BuffEntity
{
protected:
	float scoreGived;
public:
	bool seekForTarget = false;
	HittingEntity() { scoreGived = 0; }
	virtual ~HittingEntity(){}

	/// <summary>
	/// Cette méthode est à appeler sur chaque entité qui rentre en contact avec le joueur
	/// </summary>
	/// <param name="delta"></param>
	/// <param name="player"></param>
	virtual void updatewPlayer(float delta, Player& player)=0;
	//virtual void updatewGunslinger(float delta, Gunslinger& Gunz) = 0;
	//virtual void die(std::vector<HittingEntity*> r) = 0;
	void setScoreGived(float score) {
		if (score >= 0)
			scoreGived = score;
	}
	float getScoreGived()
	{
		return scoreGived;
	}
	virtual void setTarget(Mob * target){}//Ne fait rien
};


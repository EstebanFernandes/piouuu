#pragma once
#include "CPlayer.h"
//entité qui doivent rentrer en collision avec le joueur.
class CHittingEntity : public CMob
{
protected:
	float scoreGived;
public:
	CHittingEntity() { scoreGived = 0; }
	virtual ~CHittingEntity(){}
	/// <summary>
	/// Cette méthode est à appeler sur chaque entité qui rentre en contact avec le joueur
	/// </summary>
	/// <param name="delta"></param>
	/// <param name="player"></param>
	virtual void updatewPlayer(float delta, CPlayer& player)=0;
	//virtual void updatewGunslinger(float delta, CGunslinger& Gunz) = 0;
	//virtual void die(std::vector<CHittingEntity*> r) = 0;
	void setScoreGived(float score) {
		if (score >= 0)
			scoreGived = score;
	}
	float getScoreGived()
	{
		return scoreGived;
	}
};


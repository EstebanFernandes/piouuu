#pragma once
#include"Gunslinger.h"
class Gunshot : public Gunslinger
{
private:
	int bulletIndex;
public:
	Gunshot(AssetManager* asset);
	void updateWeapon(float dt);
};


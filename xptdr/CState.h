#pragma once
class CState
{
public:

	//Méthodes :
	virtual void STEInit() = 0;
	virtual void STEHandleInput() = 0;
	virtual void STEUpdate(float delta) = 0;
	virtual void STEDraw(float delta) = 0; // différence entre les frames
	virtual void STEPause() {};
	virtual void STEResume() {};
};


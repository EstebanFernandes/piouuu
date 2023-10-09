#pragma once
class CState
{
public:

	//M�thodes :
	virtual void STEInit() = 0;
	virtual void STEHandleInput() = 0;
	virtual void STEUpdate(float delta) = 0;
	virtual void STEDraw(float delta) = 0; // diff�rence entre les frames
	virtual void STEPause() {};
	virtual void STEResume() {};
};


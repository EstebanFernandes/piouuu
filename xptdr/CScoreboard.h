#pragma once
#include "CState.h"
#include "CParserCSV.h"
#include "CJeu.h"

class CScoreboard : public CState
{
private:
	GameDataRef data;
public:
	CScoreboard(GameDataRef _data);
	CScoreboard(GameDataRef _data, int score);
	void STEInit();
	void STEHandleInput();
	void STEUpdate(float delta);
	void STEDraw(float delta); // différence entre les frames
};


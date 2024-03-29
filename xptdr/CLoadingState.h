#pragma once
#include"CState.h"
#include"CParserXML.h"
#include<thread>
#include"Level.h"
/// <summary>
/// écran de chargement qui load les infos sur un niveau
/// //écran posé au dessus de l'écran de base add is replacing false, on passe un pointeur vers le stockage du niveau
/// </summary>
//info nécessaire pour le parserXML pour load un niveau
struct infoForloading {
	Level* level;
	std::string fileName;
	bulletStorage* bulletStorage;
};
class CLoadingState : public CState
{
private:
	GameDataRef data;
	infoForloading info;
	std::thread loadingThread;
public:
	CLoadingState(GameDataRef data_,infoForloading info_);
	void STEInit();
	void STEHandleInput();
	void STEUpdate(float delta);
	void STEDraw(float delta);

	void threadFunction(infoForloading* infoquoi);
};


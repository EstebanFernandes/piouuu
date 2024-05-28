#pragma once
#include"CGameState.h"
#include"CParserXML.h"
#include"CLoadingState.h"
class CLevelGameState : public CGameState
{
private:
	std::string levelFilePath;
	Level level;
	bool isLevelInit = false;
	bool isLevelSet = false;
	void deleteEntity(int& i);
	void deleteEntity(std::vector<CHittingEntity*>::iterator& entity);
	void startLevel();
public:
	CLevelGameState(GameDataRef _data);
	CLevelGameState(GameDataRef _data, std::vector<CCharacter>& characters,std::string filePath);
	CLevelGameState(GameDataRef _data, std::vector<CCharacter>& characters);
	/// <summary>
	/// Filepath throught an xml file defining a level
	/// </summary>
	/// <param name="filePath"></param>
	void STEInit();
	void STEUpdate(float delta);
	void initAssets();
	void GameOver();
	void STEResume();
	void STEDraw(float delta);
	void afterTransi();
	void drawOnTarget(sf::RenderTarget& target, float interpolation);
};



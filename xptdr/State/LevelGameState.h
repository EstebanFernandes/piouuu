#pragma once
#include"GameState.h"
#include"../IO/ParserXML.h"
#include"LoadingState.h"

using Engine::Transition;
namespace StateNS {

	class LevelGameState : public GameState
	{
	private:
		std::string levelFilePath;
		Level level;
		bool isLevelInit = false;
		bool isLevelSet = false;
		void deleteEntity(int& i);
		void deleteEntity(std::vector<HittingEntity*>::iterator& entity);
		void startLevel();

		void initBackground();
	public:
		LevelGameState(GameDataRef _data);
		LevelGameState(GameDataRef _data, std::vector<Character>& characters,std::string filePath);
		LevelGameState(GameDataRef _data, std::vector<Character>& characters);
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
		//Méthode surchargée de GameState
		void updateSun() {
			BG1.getLayer("sun").sprite.setPosition(ellipseForSun.getPoint(indexForSun));
			lightShader.setUniform("lightPoint", utilities::glslCoord(ellipseForSun.getPoint(indexForSun), (float)Engine::SCREEN_HEIGHT));
			if (!level.isInfinite)
				GameState::updateSun();
		}
		void updateBackground(float delta);
		void debugInfo() {
			ImGui::SliderInt("Index soleil", &indexForSun, 0, 600);
		}
	};



}
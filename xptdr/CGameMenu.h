#pragma once
#include "CState.h"
#include "DEFINITIONS.h"
#include "CMainMenuState.h"
class CGameMenu : public CState, public InterfaceState
{
private:
	GameDataRef data;
	// On met un petit compteur avant de reprendre
	bool resumeClicked = false;
	sf::Texture texta;
	sf::Sprite backGroundImage;
	std::vector<CButton> buttons;
	std::vector<float> where;
	int index;
	sf::Clock resumeClock;
	sf::Time ahah;
	sf::Text decompte;
	bool mdrr = false;
	void choosedButton();
public:
	CGameMenu(GameDataRef _data);
	void STEInit();
	void STEHandleInput();
	void STEUpdate(float delta);
	void STEDraw(float delta);
	void outline(int previndex);
	void STEResume()
	{
		resizeScreen();
	}
	void resizeScreen();
};


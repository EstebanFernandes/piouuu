#include "CState.h"
//Nécessaire pour éviter les erreurs de link (vive le c++)
CTransition CState::currentTransi= CTransition();
float CState::angleOffset = (float)(rand() % 360);
float CState::time = 0.f;
sf::Clock CState::globalClock = sf::Clock();
CBackground CState::background = CBackground();
void CState::updateTime()
{
	time = globalClock.getElapsedTime().asSeconds();
}

CState::~CState()
{
}

#include "CState.h"
//Nécessaire pour éviter les erreurs de link (vive le c++)
CTransition CState::currentTransi= CTransition();
float CState::angleOffset = (float)(rand() % 360);
float CState::time = 0.f;
sf::Clock CState::globalClock = sf::Clock();
CBackground CState::background = CBackground();
//char A::a[6] = {1,2,3,4,5,6};
inputPlayer CState::inputOfPlayers[2] = { inputPlayer(0),inputPlayer(1) };
void CState::updateTime()
{
	time = globalClock.getElapsedTime().asSeconds();
}

CState::~CState()
{
}

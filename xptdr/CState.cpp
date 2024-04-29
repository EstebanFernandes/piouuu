#include "CState.h"
//Nécessaire pour éviter les erreurs de link (vive le c++)
CTransition CState::currentTransi= CTransition();

void CState::updateTime()
{
	time = clock.getElapsedTime().asSeconds();
}

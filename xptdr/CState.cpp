#include "CState.h"
//N�cessaire pour �viter les erreurs de link (vive le c++)
CTransition CState::currentTransi= CTransition();

void CState::updateTime()
{
	time = clock.getElapsedTime().asSeconds();
}

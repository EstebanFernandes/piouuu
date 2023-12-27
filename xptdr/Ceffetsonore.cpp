#include "Ceffetsonore.h"
#include <iostream>

CeffetSonore::CeffetSonore()
{
}

CeffetSonore::CeffetSonore(std::string fileName)
{
	if (buffer.loadFromFile(fileName))
	{
		sound.setBuffer(buffer);
	}
	else
	{
		std::cout << "Erreur lors du chargement de l'effet sonore." << std::endl;
	}
}

void CeffetSonore::play()
{
	sound.play();
}

void CeffetSonore::setVolume(float volume)
{
	sound.setVolume(volume);
}
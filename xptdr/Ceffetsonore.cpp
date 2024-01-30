#include "Ceffetsonore.h"
#include <iostream>

CeffetSonore::CeffetSonore()
{
}

void CeffetSonore::stockSound(const std::string& name, const std::string& filePath)
{
	auto it = sfxstorages.find(name);
	if(it==sfxstorages.end())
	{
		sf::SoundBuffer buff;
		if (buff.loadFromFile(filePath)) {
			sfxstorages[name] = buff;
		}
	}
}

void CeffetSonore::addSound(const std::string& name,sf::Sound* son)
{
	*son = sf::Sound(sfxstorages.at(name));
	sonetgame temp;
	temp.son = son;
	temp.son->setVolume(temp.volumeparSon * (volumeOverAll / 100.f));
	sons.push_back(temp);

}

sf::SoundBuffer& CeffetSonore::getSound(const std::string& name)
{
	return sfxstorages.at(name);
}

void CeffetSonore::overAllVolume(float volume)
{
	if (volume >= 0.f && volume <= 100.f)
	{
		volumeOverAll = volume;
		int max = (int)sons.size();
		for (int i = 0; i < max; i++)
		{
			sons[i].son->setVolume(sons[i].volumeparSon * (volumeOverAll / 100.f));
		}
	}
}

void CeffetSonore::checkVect()
{
	int max = (int)sons.size();
	for (int i = 0; i < max; i++)
	{
		if (sons[i].son->getBuffer() == nullptr)
		{
			sons.erase(sons.begin() + i);
			if (i != 0)
				i--;
			max--;
		}
	}
}

void CeffetSonore::deleteSound(sf::Sound* a)
{
	int max = (int)sons.size();
	for (int i = 0; i < max; i++)
	{
		if (sons[i].son == a)
		{
			sons.erase(sons.begin() + i);
			if (i != 0)
				i--;
			max--;
		}
	}
}

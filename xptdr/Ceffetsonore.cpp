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

void CeffetSonore::addSound(const std::string& name,sf::Sound** son)
{
	sonetgame temp;
	temp.son = sf::Sound(sfxstorages.at(name));
	temp.son.setVolume(temp.volumeparSon * (volumeOverAll / 100.f));
	sons.push_back(temp);
	*son = &(sons.back().son);
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
		for (auto i = sons.begin(); i != sons.end(); i++)
			i->son.setVolume(i->volumeparSon * (volumeOverAll / 100.f));
	}
}

void CeffetSonore::checkList()
{
	//eheh
}

void CeffetSonore::deleteSound(sf::Sound* a)
{
	if (a != NULL)
	{
		for (auto i = sons.begin(); i != sons.end();)
		{
			if (a == &i->son)
			{
				i = sons.erase(i);
				break;
			}
			else
				i++;
		}
		std::cout << "size of the sons manager : " << sons.size();
	}
}

void CeffetSonore::setSonVolume(sf::Sound* son_, float vol)
{
	for (auto son = sons.begin(); son != sons.end() ; son++)
	{
		if ((&son->son) == son_)
		{
			son->volumeparSon = vol;
			son->son.setVolume(son->volumeparSon * (volumeOverAll / 100.f));
		}

	}
}

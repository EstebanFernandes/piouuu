#pragma once
#include <SFML/Audio.hpp>

class CeffetSonore
{
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;

public:
	CeffetSonore();
	CeffetSonore(std::string fileName);

	void play();
	void setVolume(float volume);
};
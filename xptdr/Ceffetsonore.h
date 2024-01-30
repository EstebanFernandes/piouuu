#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>
struct sonetgame {
	sf::Sound* son;
	float volumeparSon = 100.f;
};
class CeffetSonore
{
private:
	std::vector<sonetgame> sons;
	std::unordered_map<std::string, sf::SoundBuffer> sfxstorages;
	float volumeOverAll = 100.f;
public:
	CeffetSonore();
	/// <summary>
	/// Fonction qui stock le son dans une map de son buffer
	/// </summary>
	/// <param name="id"></param>
	/// <param name="filePath"></param>
	void stockSound(const std::string& name, const std::string& filePath);
	/// <summary>
	/// Fonction qui ajoute un son dans la liste des sons actifs et en renvoie la réference
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	void addSound(const std::string& name,sf::Sound* son);
	sf::SoundBuffer& getSound(const std::string& name);
	void overAllVolume(float volume);
	void checkVect();
	void deleteSound(sf::Sound* a);
	void clearSoundBuffer() {

		//for (auto it = sfxstorages.cbegin(); it != sfxstorages.cend() /* not hoisted */; /* no increment */)
		//{
		//	
		//		//sfxstorages.erase(it++);    // or "it = m.erase(it)" since C++11

		//}
	}
};
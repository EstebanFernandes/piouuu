#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>

namespace Engine {
	struct sonetgame {
		sf::Sound son;
		float volumeparSon = 100.f;
	};
	class EffetSonore
	{
	private:
		std::list<sonetgame> sons;
		std::unordered_map<std::string, sf::SoundBuffer> sfxstorages;
		float volumeOverAll = 100.f;
	public:
		EffetSonore();
		/// <summary>
		/// Fonction qui stock le son dans une map de son buffer
		/// </summary>
		/// <param name="id"></param>
		/// <param name="filePath"></param>
		void stockSound(const std::string& name, const std::string& filePath);
		/// <summary>
		/// Fonction qui ajoute un son dans la liste des sons actifs et en renvoie la r�ference
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		void addSound(const std::string& name,sf::Sound** son);
		sf::SoundBuffer& getSound(const std::string& name);
		void overAllVolume(float volume);
		/// <summary>
		/// v�rifie si des �lements de la liste peuvent �tre supprim�s
		/// > fait rien
		/// </summary>
		void checkList();
		void deleteSound(sf::Sound* a);
		void clearSoundBuffer() {

			for (auto it = sfxstorages.cbegin(); it != sfxstorages.cend() /* not hoisted */; /* no increment */)
			{
					it = sfxstorages.erase(it);    // or "it = m.erase(it)" since C++11
			}
		}
		void setSonVolume(sf::Sound* son, float vol);
	};
}
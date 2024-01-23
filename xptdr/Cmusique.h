#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>

struct musiqueetgame{
    std::unique_ptr<sf::Music> music;
    float volumeparPiste = 100.f;
};
class Cmusique
{
private:
    // Map pour stocker les pointeurs vers les musiques associ�es � leurs identifiants
    std::unordered_map<std::string, musiqueetgame> musiques;
    /// <summary>
    /// Facteur compris entre 0 et 100 qui d�finit le niveau de la musique, on peut ajuster chaque piste
    /// </summary>
    float volumeOverAll = 100.f;
public:
    // Ajoute musique
    void ajouterMusique(const std::string& id, const std::string& filePath);

    // Joue la musique
    void jouerMusique(const std::string& id);

    // Met en pause la musique
    void pauseMusique(const std::string& id);

    // Remet la musique � jouer
    void resumeMusique(const std::string& id);

    // Arr�te la musique
    void stopMusique(const std::string& id);

    // R�gle le volume de la musique
    void volumeMusique(const std::string& id, float volume);
    void overAllVolume(float volume);
};

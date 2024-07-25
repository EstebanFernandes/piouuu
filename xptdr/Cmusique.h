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
    //Avoir la musique
    sf::Music* getMusique(const std::string& id);

    /// <summary>
    /// R�gle le volume de la piste
    /// </summary>
    /// <param name="id"> de la musique</param>
    /// <param name="volume"> en float</param>
    void volumeMusique(const std::string& id, float volume);
    /// <summary>
    /// R�gle le volume g�n�rale de la musique
    /// </summary>
    /// <param name="volume"></param>
    void overAllVolume(float volume);
};

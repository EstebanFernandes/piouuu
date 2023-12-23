#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>

class Cmusique
{
private:
    // Map pour stocker les pointeurs vers les musiques associ�es � leurs identifiants
    std::unordered_map<std::string, std::unique_ptr<sf::Music>> musiques; 
public:
    // Ajoute musique
    void ajouterMusique(const std::string& id, const std::string& filePath);

    // Joue la musique
    void jouerMusique(const std::string& id);

    // Met en pause la musique
    void pauseMusique(const std::string& id);

    // Arr�te la musique
    void stopMusique(const std::string& id);

    // R�gle le volume de la musique
    void volumeMusique(const std::string& id, float volume);
};

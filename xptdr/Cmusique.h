#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>

class Cmusique
{
private:
    // Map pour stocker les pointeurs vers les musiques associées à leurs identifiants
    std::unordered_map<std::string, std::unique_ptr<sf::Music>> musiques; 
public:
    // Ajoute un nouvel identifiant de musique et charge le fichier associé
    void ajouterMusique(const std::string& id, const std::string& filePath);

    // Joue la musique associée à l'identifiant donné
    void jouerMusique(const std::string& id);

    // Met en pause la musique associée à l'identifiant donné
    void pauseMusique(const std::string& id);

    // Arrête la musique associée à l'identifiant donné
    void stopMusique(const std::string& id);

    // Règle le volume de la musique associée à l'identifiant donné (entre 0 et 100)
    void volumeMusique(const std::string& id, float volume);
};

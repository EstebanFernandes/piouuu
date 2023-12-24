#include "Cmusique.h"

void Cmusique::ajouterMusique(const std::string& id, const std::string& filePath)
{
    std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();
    music->openFromFile(filePath);
    musiques[id] = std::move(music);
}

void Cmusique::jouerMusique(const std::string& id)
{
    auto it = musiques.find(id);
    if (it != musiques.end()) {
        it->second->play();
    }
}

void Cmusique::pauseMusique(const std::string& id)
{
    auto it = musiques.find(id);
    if (it != musiques.end()) {
        it->second->pause();
    }
}

void Cmusique::resumeMusique(const std::string& id)
{
    auto it = musiques.find(id);
    if (it != musiques.end() && it->second->getStatus() == sf::Music::Paused) {
        it->second->play(); 
    }
}

void Cmusique::stopMusique(const std::string& id)
{
    auto it = musiques.find(id);
    if (it != musiques.end()) {
        it->second->stop();
    }
}

void Cmusique::volumeMusique(const std::string& id, float volume)
{
    auto it = musiques.find(id);
    if (it != musiques.end()) {
        it->second->setVolume(volume);
    }
}

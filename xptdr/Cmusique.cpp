#include "Cmusique.h"

void Cmusique::ajouterMusique(const std::string& id, const std::string& filePath)
{
    std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();
    music->openFromFile(filePath);
    musiques[id].music = std::move(music);
}

void Cmusique::jouerMusique(const std::string& id)
{
    auto it = musiques.find(id);
    if (it != musiques.end()) {
        it->second.music->play();
    }
}

void Cmusique::pauseMusique(const std::string& id)
{
    auto it = musiques.find(id);
    if (it != musiques.end()) {
        it->second.music->pause();
    }
}

void Cmusique::resumeMusique(const std::string& id)
{
    auto it = musiques.find(id);
    if (it != musiques.end() && it->second.music->getStatus() == sf::Music::Paused) {
        it->second.music->play(); 
    }
}

void Cmusique::stopMusique(const std::string& id)
{
    auto it = musiques.find(id);
    if (it != musiques.end()) {
        it->second.music->stop();
    }
}

void Cmusique::volumeMusique(const std::string& id, float volume)
{
    auto it = musiques.find(id);
    if (it != musiques.end()) {
        it->second.music->setVolume(volume);
    }
}

void Cmusique::overAllVolume(float volume)
{
    if (volume >= 0.f && volume <= 100.f)
    {
        volumeOverAll = volume;
        for (auto it = musiques.begin(); it != musiques.end(); it++) {
            it->second.music->setVolume(it->second.music->getVolume() * (volumeOverAll / 100.f));
        }
    }
}

#include "Musique.h"

void Engine::Musique::ajouterMusique(const std::string& id, const std::string& filePath)
{
    std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();
    music->openFromFile(filePath);
    music->setLoop(true);
    musiques[id].music = std::move(music);
}

void Engine::Musique::jouerMusique(const std::string& id)
{
    auto it = musiques.find(id);
    if (it != musiques.end()) {
        it->second.music->play();
    }
}

void Engine::Musique::pauseMusique(const std::string& id)
{
    auto it = musiques.find(id);
    if (it != musiques.end()) {
        it->second.music->pause();
    }
}

void Engine::Musique::resumeMusique(const std::string& id)
{
    auto it = musiques.find(id);
    if (it != musiques.end() && it->second.music->getStatus() == sf::Music::Paused) {
        it->second.music->play(); 
    }
}

void Engine::Musique::stopMusique(const std::string& id)
{
    auto it = musiques.find(id);
    if (it != musiques.end()) {
        it->second.music->stop();
    }
}

sf::Music* Engine::Musique::getMusique(const std::string& id)
{
    auto it = musiques.find(id);
    if (it != musiques.end())
    {
        return it->second.music.get();
    }
    return NULL;
}

void Engine::Musique::volumeMusique(const std::string& id, float volume)
{
    auto it = musiques.find(id);
    if (it != musiques.end()) {
        it->second.volumeparPiste = volume;
    }
}


void Engine::Musique::overAllVolume(float volume)
{
    if (volume >= 0.f && volume <= 100.f)
    {
        volumeOverAll = volume;
        for (auto it = musiques.begin(); it != musiques.end(); it++) {
            it->second.music->setVolume(it->second.volumeparPiste * (volumeOverAll / 100.f));
        }
    }
}
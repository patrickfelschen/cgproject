#include "SoundManager.h"

SoundManager &SoundManager::getInstance() {
    static SoundManager instance;
    return instance;
}

void SoundManager::init(std::initializer_list<const char*> sounds) {
    this->soundEngine = irrklang::createIrrKlangDevice();
    this->soundEngine->setSoundVolume(0.02);

    for(auto sound: sounds) {
        this->soundEngine->addSoundSourceFromFile(sound);
    }

    printf("IRRKLANG::SOUNDSOURCES: %i\n", this->soundEngine->getSoundSourceCount());
}

void SoundManager::destroy() {
    soundEngine->drop();
}

void SoundManager::playSingle2DSound(const char *file) {
    if(!this->soundEngine->isCurrentlyPlaying(this->soundEngine->getSoundSource(file))) {
        this->soundEngine->play2D(this->soundEngine->getSoundSource(file));
    }
}

void SoundManager::play2DSound(const char *file, bool loop) {
    this->soundEngine->play2D(this->soundEngine->getSoundSource(file), loop);
}

void SoundManager::stopPlaying() {
    this->soundEngine->stopAllSounds();
}

void SoundManager::stopSound(const char *file) {
    this->soundEngine->stopAllSoundsOfSoundSource(this->soundEngine->getSoundSource(file));
}

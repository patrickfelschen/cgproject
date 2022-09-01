#include "SoundManager.h"

SoundManager &SoundManager::getInstance() {
    static SoundManager instance;
    return instance;
}

void SoundManager::init(std::initializer_list<const char*> sounds) {
    this->soundEngine = irrklang::createIrrKlangDevice();
    if(!this->soundEngine) {
        std::cerr << "ERROR::SOUNDMANAGER::INIT: Error starting sound engine " << std::endl;
        exit(EXIT_FAILURE);
    }

    this->soundEngine->setSoundVolume(0.1);

    for(auto sound: sounds) {
        this->soundEngine->addSoundSourceFromFile(sound);
    }
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

irrklang::ISound* SoundManager::play3DSound(const char *file, const Vector3f &pos, bool loop, bool startPaused) {
    return this->soundEngine->play3D(file, irrklang::vec3df(pos.x, pos.y, pos.z), loop, startPaused);
}

void SoundManager::setListenerPos(const Vector3f &pos, const Vector3f &dir) {
    this->soundEngine->setListenerPosition(irrklang::vec3df(pos.x, pos.y, pos.z), irrklang::vec3df(dir.x, dir.y, dir.z));
}

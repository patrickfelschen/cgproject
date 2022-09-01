#include "SoundManager.h"
#include "../utils/Camera.h"

SoundManager &SoundManager::getInstance() {
    static SoundManager instance;
    return instance;
}

void SoundManager::init(std::initializer_list<const char *> sounds) {
    this->soundEngine = irrklang::createIrrKlangDevice();
    if (!this->soundEngine) {
        std::cerr << "ERROR::SOUNDMANAGER::INIT: Error starting sound engine " << std::endl;
        exit(EXIT_FAILURE);
    }

    this->soundEngine->setSoundVolume(0.1);

    for (auto sound: sounds) {
        this->soundEngine->addSoundSourceFromFile(sound);
    }
}

void SoundManager::destroy() {
    soundEngine->drop();
}

void SoundManager::play2DSound(const char *file, bool loop, bool repeat) {
    irrklang::ISoundSource *source = this->soundEngine->getSoundSource(file);
    if ((repeat && !this->soundEngine->isCurrentlyPlaying(source)) || !repeat) {
        this->soundEngine->play2D(source);
    }
}

void SoundManager::stopPlaying() {
    this->soundEngine->stopAllSounds();
}

void SoundManager::stopSound(const char *file) {
    this->soundEngine->stopAllSoundsOfSoundSource(this->soundEngine->getSoundSource(file));
}

irrklang::ISound *SoundManager::play3DSound(const char *file, const Vector3f &pos, bool loop, bool startPaused) {
    return this->soundEngine->play3D(file, irrklang::vec3df(pos.x, pos.y, pos.z), loop, startPaused);
}

void SoundManager::setListenerPos(const Camera* camera) {
    this->soundEngine->setListenerPosition(
            irrklang::vec3df(camera->getPosition().x, camera->getPosition().y, camera->getPosition().z),
            irrklang::vec3df(camera->getTarget().x, camera->getTarget().y, camera->getTarget().z),
            irrklang::vec3df(),
            irrklang::vec3df(camera->getUp().x, -camera->getUp().y, camera->getUp().z)
    );
}

#include "SoundManager.h"

SoundManager &SoundManager::getInstance() {
    static SoundManager instance;
    return instance;
}

/**
 * Initialisiert irrKlang
 * @param sounds Erzeugt SoundSources aus den übergebenen Sounds und fügt sie der SoundEngine hinzu
 */
void SoundManager::init(std::initializer_list<const char *> sounds) {
    this->soundEngine = irrklang::createIrrKlangDevice();
    if (!this->soundEngine) {
        std::cerr << "ERROR::SOUNDMANAGER::INIT: Error starting sound engine " << std::endl;
        exit(EXIT_FAILURE);
    }

    this->soundEngine->setSoundVolume(0.1);

    for (auto sound: sounds) {
        this->soundEngine->addSoundSourceFromFile(sound, irrklang::ESM_AUTO_DETECT, true);
    }
}

void SoundManager::destroy() {
    soundEngine->drop();
}

/**
 * Spielt einen 2D Sound ab
 * @param file Pfad zur Datei
 * @param loop Gibt an, ob sich der Sound nach ablauf wiederholen soll
 * @param repeat Legt fest, ob der Sound vor Ablauf erneut abgespielt werden darf (Dadurch entsteht überlappen des Tons)
 */
void SoundManager::play2DSound(const char *file, bool loop, bool repeat) {
    irrklang::ISoundSource *source = this->soundEngine->getSoundSource(file);
    if ((repeat && !this->soundEngine->isCurrentlyPlaying(source)) || !repeat) {
        this->soundEngine->play2D(source, loop);
    }
}

/**
 * Stoppt alle Sounds
 */
void SoundManager::stopPlaying() {
    this->soundEngine->stopAllSounds();
}

/**
 * Stop einen Sound
 * @param file Pfad zur Datei
 */
void SoundManager::stopSound(const char *file) {
    this->soundEngine->stopAllSoundsOfSoundSource(this->soundEngine->getSoundSource(file));
}

/**
 * Spielt einen 3D Sound ab
 * @param file Pfad zur Datei
 * @param pos Position des Sounds
 * @param loop Gibt an, ob sich der Sound nach ablauf wiederholen soll
 * @param startPaused Verhindert das automatische Abspielen des Sounds
 * @return Pointer zum Sound
 */
irrklang::ISound *SoundManager::play3DSound(const char *file, const Vector3f &pos, bool loop, bool startPaused) {
    return this->soundEngine->play3D(file, irrklang::vec3df(pos.x, pos.y, pos.z), loop, startPaused);
}

/**
 * Ändert die Position des Hörers
 * @param camera Kameraposition wird für Hörerposition verwendet
 */
void SoundManager::setListenerPos(const Camera *camera) {
    this->soundEngine->setListenerPosition(
            irrklang::vec3df(camera->getPosition().x, camera->getPosition().y, camera->getPosition().z),
            irrklang::vec3df(camera->getTarget().x, camera->getTarget().y, camera->getTarget().z),
            irrklang::vec3df(),
            irrklang::vec3df(camera->getUp().x, -camera->getUp().y, camera->getUp().z)
    );
}

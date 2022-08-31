#ifndef CG_SOUNDMANAGER_H
#define CG_SOUNDMANAGER_H

#include <irrKlang.h>
#include <map>
#include <cstdarg>

class SoundManager {
private:
    SoundManager() {}

    irrklang::ISoundEngine *soundEngine;

public:
    static SoundManager &getInstance();

    SoundManager(SoundManager const&)   = delete;
    void operator=(SoundManager const&) = delete;

    void init(std::initializer_list<const char*> sounds);

    void destroy();

    void playSingle2DSound(const char *file);

    void play2DSound(const char *file, bool loop = false);

    void stopPlaying();

    void stopSound(const char *file);
};


#endif //CG_SOUNDMANAGER_H

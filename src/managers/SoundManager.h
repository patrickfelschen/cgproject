#ifndef CG_SOUNDMANAGER_H
#define CG_SOUNDMANAGER_H

#include <irrKlang.h>
#include <map>
#include <cstdarg>
#include <iostream>
#include "../maths/Vector3f.h"
#include "../utils/Camera.h"

class SoundManager {
private:
    SoundManager() {}

    irrklang::ISoundEngine *soundEngine;

public:
    static SoundManager &getInstance();

    SoundManager(SoundManager const &) = delete;

    void operator=(SoundManager const &) = delete;

    void init(std::initializer_list<const char *> sounds);

    void destroy();

    void play2DSound(const char *file, bool loop = false, bool repeat = false);

    irrklang::ISound *play3DSound(const char *file, const Vector3f &pos, bool loop = false, bool startPaused = false);

    void setListenerPos(const Camera *camera);

    void stopPlaying();

    void stopSound(const char *file);
};


#endif //CG_SOUNDMANAGER_H

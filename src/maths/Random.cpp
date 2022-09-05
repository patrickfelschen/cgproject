//
// Created by Patrick on 25.08.2022.
//

#include "Random.h"

/**
 * Liefert eine zufällige Zahl zwischen min und max zurück
 * Quelle: https://levelup.gitconnected.com/learning-c-generating-random-numbers-the-c-11-way-f041bbe94f3e
 * @param min kleinste Zahl
 * @param max größte Zahl
 * @return Zufallszahl
 */
float Random::randFloat(float min, float max) {
    std::random_device rd;
    std::default_random_engine random_engine(rd());
    std::uniform_int_distribution<int> dist(0, 10000);
    float rand = (float) dist(random_engine) / 10000;
    return rand * (max - min) + min;
}

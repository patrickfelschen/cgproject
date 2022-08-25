//
// Created by Patrick on 25.08.2022.
//

#include <ctime>
#include <cstdlib>
#include "Random.h"

int Random::randInt(int min, int max) {
    srand(time(nullptr));
    return ((int(rand()) / int(RAND_MAX)) * (max - min)) + min;
}

float Random::randFloat(float min, float max) {
    std::random_device rd;
    std::default_random_engine random_engine(rd());
    std::uniform_int_distribution<int> dist(0, 10000);
    float rand = (float)dist(random_engine)/10000;
    return rand * (max - min) + min;
}

//
// Created by Patrick on 25.08.2022.
//

#ifndef CG_RANDOM_H
#define CG_RANDOM_H


#include <random>

class Random {
public:
    static int randInt(int min, int max);

    static float randFloat(float min, float max);
};


#endif //CG_RANDOM_H

//
// Created by Patrick on 30.08.2022.
// https://www.khronos.org/opengl/wiki/Interface_Block_(GLSL)
//

#ifndef CG_LIGHTMANAGER_H
#define CG_LIGHTMANAGER_H

#include <vector>
#include "../buffers/UniformBuffer.h"
#include "../utils/Camera.h"
#include "../utils/Color.h"

#define MAX_LIGHT_COUNT 30

enum LightType {
    POINT = 0,
    DIR = 1,
    SPOT = 2
};

struct Light {
    int type; Vector3f p5;

    Vector3f position; float p0;
    Vector3f direction; float p1;

    Color ambient;
    Color diffuse;
    Color specular;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;

    Vector3f p2;
};

struct Lights {
    int staticLightsCount = 0; Vector3f p0;
    Light dynamicLight;
    Light staticLights[MAX_LIGHT_COUNT];
};

class LightManager {
public:
    explicit LightManager(const Camera *camera);

    virtual ~LightManager();

    void render();

    void setDynamicLight(Vector3f position, Vector3f direction);
    void addPoint(Vector3f position);
    void addSpot(Vector3f position, Vector3f direction);
    void addDir(Vector3f dir);

private:
    const Camera *camera;
    UniformBuffer *uboSpotLights;
    Lights lights;
};


#endif //CG_LIGHTMANAGER_H

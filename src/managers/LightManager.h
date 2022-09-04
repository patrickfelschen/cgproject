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

// Maximale Anzahl an statischen Lichtquellen,
// diese muss mit dem Shader abgeglichen werden.
#define MAX_LIGHT_COUNT 30

enum LightType {
    POINT = 0,
    DIR = 1,
    SPOT = 2
};

/**
 * Struktur einer einzelnen Lichtquelle
 * Paddings:
 * https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL (Uniform block layout)
 * https://www.khronos.org/opengl/wiki/Interface_Block_(GLSL)#Memory_layout (Memory layout, std140)
 * Definition: siehe Shader
 */
struct Light {
    int type; Vector3f padding0;

    Vector3f position; float padding1;
    Vector3f direction; float padding2;

    Color ambient;
    Color diffuse;
    Color specular;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;

    Vector3f padding3;
};
/**
 * Struktur für mehrere Lichtquellen
 */
struct Lights {
    int staticLightsCount = 0; Vector3f padding0;
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

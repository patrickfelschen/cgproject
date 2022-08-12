//
// Created by Patrick on 02.08.2022.
//

#ifndef CG_SHADER_H
#define CG_SHADER_H


#include <unordered_map>
#include "GL/glew.h"
#include "../utils/Loader.h"
#include "../maths/Vector3f.h"
#include "../maths/Matrix.h"
#include "../utils/Camera.h"
#include "../utils/Color.h"

class Shader {
public:
    Shader();

    Shader(const char *vsFilePath, const char *fsFilePath, bool useView);

    virtual ~Shader();

    void activate(const Camera &camera);

    void deactivate() const;

    void setModelTransform(const Matrix &modelTransform);

    void setUniform(const char *name, float value);

    void setUniform(const char *name, const Vector3f &value);

    void setUniform(const char *name, const Color &value);

    void setUniform(const char *name, int value);

    void setUniform(const char *name, const Matrix &value);

protected:
    Matrix modelTransform;

    GLint getUniformLocation(const char *name);

    virtual void setUniforms(const Camera &camera);

private:
    // ID des shaders
    GLuint id = 0;
    // Pfad der Shaderdateien
    const char *vsFilePath;
    const char *fsFilePath;

    bool useView;

    std::unordered_map<const char *, GLint> uniformLocationCache;

    void compile();
};


#endif //CG_SHADER_H

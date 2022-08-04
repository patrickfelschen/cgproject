//
// Created by Patrick on 02.08.2022.
//

#ifndef CG_SHADER_H
#define CG_SHADER_H


#include "GL/glew.h"
#include "../utils/Loader.h"
#include "../maths/Vector3f.h"
#include "../maths/Matrix.h"
#include "../utils/Camera.h"

class Shader {
public:
    Shader(const char *vsFilePath, const char *fsFilePath);

    virtual ~Shader();

    void activate(const Camera &camera) const;

    void deactivate() const;

    void setUniform(GLint locationId, int value) const;

    void setUniform(GLint locationId, float value) const;

    void setUniform(GLint locationId, const Vector3f &value) const;

    void setUniform(GLint locationId, const Matrix &value) const;

    void setModelTransform(const Matrix &modelTransform);

protected:
    // ID des shaders
    GLuint shaderProgramId = 0;
    // Pfad der Shaderdateien
    const char *vsFilePath;
    const char *fsFilePath;

    Matrix modelTransform;

    GLint transformLoc = 0;
    GLint projectionLoc = 0;
    GLint viewLoc = 0;
    GLint lightPosLoc = 0;
    GLint camPosLoc = 0;

    void compile();

    void queryUniforms();

    GLint getUniformLocation(const char *uniform) const;
};


#endif //CG_SHADER_H

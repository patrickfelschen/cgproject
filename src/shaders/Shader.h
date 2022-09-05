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
    explicit Shader(const char *vsFilePath, const char *fsFilePath);

    virtual ~Shader();

    void activate();

    void deactivate() const;

    virtual void setTransform(const Matrix &t);

    void setUniform(const std::string &name, float value);

    void setUniform(const std::string &name, const Vector3f &value);

    void setUniform(const std::string &name, const Color &value);

    void setUniform(const std::string &name, int value);

    void setUniform(const std::string &name, const Matrix &value);

protected:
    virtual void setUniforms() = 0;

    Matrix transform;
private:
    // ID des Shaders
    GLuint id = 0;
    // Pfad der Shaderdateien
    const char *vsFilePath;
    const char *fsFilePath;

    std::unordered_map<std::string, GLint> uniformLocationCache;

    GLint getUniformLocation(const std::string &name);
};


#endif //CG_SHADER_H

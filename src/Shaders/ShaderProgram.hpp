#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "../GLincludes.hpp"
#include "../Utils/Vector3f.h"
#include "../Utils/Matrix.h"

class ShaderProgram {
private:
    GLuint programID;
    GLuint vertexShaderID;
    GLuint fragmentShaderID;

    static GLuint loadShader(const std::string &file, int type);

public:
    ShaderProgram(const std::string &vertexFile, const std::string &fragmentFile);

    virtual ~ShaderProgram();

    void start();

    void stop();

    void cleanUp();

protected:
    virtual void bindAttributes() = 0;

    void bindAttribute(int attribute, std::string variableName);

    GLuint getUniformLocation(const std::string &uniformName);

    virtual void getAllUniformLocations() = 0;

    void loadFloat(GLint location, const float &value);

    void loadVector(GLint location, const Vector3f &vector);

    void loadBoolean(GLint location, const bool &value);

    void loadMatrix(GLint location, const Matrix &matrix);
};

#endif

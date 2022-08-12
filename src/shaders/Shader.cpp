//
// Created by Patrick on 02.08.2022.
// https://youtu.be/gDtHL6hy9R8
//

#include "Shader.h"

Shader::Shader() {
    vsFilePath = "../assets/shaders/shader.vert";
    fsFilePath = "../assets/shaders/shader.frag";
    this->modelTransform.identity();
    compileShaders();
}

Shader::Shader(const char *vsFilePath, const char *fsFilePath, bool useView) : vsFilePath(vsFilePath),
                                                                               fsFilePath(fsFilePath),
                                                                               useView(useView) {
    this->modelTransform.identity();
    compileShaders();
}

void Shader::addShader(const char *shaderText, GLenum shaderType) const {
    GLuint shaderObject = glCreateShader(shaderType);
    if (shaderObject == 0) {
        std::cerr << "ERROR::SHADER::ADDSHADER: Can not create shader type " << shaderType << std::endl;
        exit(EXIT_FAILURE);
    }
    const GLchar *p[1];
    p[0] = shaderText;

    GLint lengths[1];
    lengths[0] = (GLint) strlen(shaderText);

    glShaderSource(shaderObject, 1, p, lengths);
    glCompileShader(shaderObject);

    GLint success;
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shaderObject, 1024, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::ADDSHADER: " << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }

    glAttachShader(id, shaderObject);
    glDeleteShader(shaderObject);
}

void Shader::compileShaders() {
    id = glCreateProgram();
    if (id == 0) {
        std::cerr << "ERROR::SHADER::COMPILESHADERS: Can not create shader program" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string vs, fs;

    Loader::readShaderFile(vsFilePath, vs);
    addShader(vs.c_str(), GL_VERTEX_SHADER);

    Loader::readShaderFile(fsFilePath, fs);
    addShader(fs.c_str(), GL_FRAGMENT_SHADER);

    GLint success = 0;
    GLchar errorLog[1024] = {0};

    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (success == 0) {
        glGetProgramInfoLog(id, sizeof(errorLog), nullptr, errorLog);
        std::cerr << "ERROR::SHADER::COMPILESHADERS: Can not link shader program: " << errorLog << std::endl;
        exit(EXIT_FAILURE);
    }

    glValidateProgram(id);
    glGetProgramiv(id, GL_VALIDATE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, sizeof(errorLog), nullptr, errorLog);
        std::cerr << "ERROR::SHADER::COMPILESHADERS: Invalid shader program: " << errorLog << std::endl;
        exit(EXIT_FAILURE);
    }

    glUseProgram(id);
}

void Shader::setUniforms(const Camera &camera) {
    setUniform("uProjection", camera.getProj());
    if (useView) {
        setUniform("uView", camera.getView());
    } else {
        Matrix view;
        view.identity();
        setUniform("uView", view);
    }
    setUniform("uTransform", modelTransform);
}

void Shader::activate(const Camera &camera) {
    if (id <= 0) {
        std::cerr << "ERROR::SHADER::ACTIVATE can not activate shader" << std::endl;
        exit(EXIT_FAILURE);
    }
    // Shader aktivieren
    glUseProgram(id);

    // Uniform setzen
    setUniforms(camera);
}

void Shader::deactivate() const {
    glUseProgram(0);
}

void Shader::setUniform(const char *name, int value) {
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform(const char *name, float value) {
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform(const char *name, const Vector3f &value) {
    glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}

void Shader::setUniform(const char *name, const Color &value) {
    glUniform3f(getUniformLocation(name), value.r, value.g, value.b);
}

void Shader::setUniform(const char *name, const Matrix &value) {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, value.m);
}

GLint Shader::getUniformLocation(const char *name) {
    if (uniformLocationCache.find(name) != uniformLocationCache.end()) {
        return uniformLocationCache[name];
    }

    GLint locationId = glGetUniformLocation(id, name);
    if (locationId == -1) {
        std::cerr << "ERROR::SHADER::GETUNIFORMLOCATION: can not find uniform location: " << name << std::endl;
        exit(EXIT_FAILURE);
    }
    uniformLocationCache[name] = locationId;

    return locationId;
}

void Shader::setModelTransform(const Matrix &mt) {
    this->modelTransform = mt;
}

Shader::~Shader() = default;

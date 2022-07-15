#include "ShaderProgram.hpp"

GLuint ShaderProgram::loadShader(const std::string &file, int type) {
    std::ifstream stream(file);
    std::string line;
    std::stringstream sstream;

    if (!stream.is_open()) {
        std::cerr << "Shader " << file << " not found!" << std::endl;
        exit(EXIT_FAILURE);
    }

    while (getline(stream, line)) {
        sstream << line << "\n";
    }

    stream.close();

    std::string shaderString = sstream.str();

    GLuint shaderID = glCreateShader(type);
    const char *source = shaderString.c_str();
    glShaderSource(shaderID, 1, &source, nullptr);
    glCompileShader(shaderID);

    GLint shaderStatus;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderStatus);

    if (shaderStatus == GL_FALSE) {
        int length;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
        char *message = new char[length * sizeof(char)]; //(char*)__alloca(length * sizeof(char));
        glGetShaderInfoLog(shaderID, length, &length, message);
        std::cerr << message << std::endl;
        delete[] message;
    }

    return shaderID;

}

ShaderProgram::ShaderProgram(const std::string &vertexFile, const std::string &fragmentFile) {
    this->vertexShaderID = loadShader(vertexFile, GL_VERTEX_SHADER);
    this->fragmentShaderID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
    this->programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);
    glValidateProgram(programID);
    // bindAttributes();
}

ShaderProgram::~ShaderProgram() {

}

void ShaderProgram::start() {
    glUseProgram(programID);
}

void ShaderProgram::stop() {
    glUseProgram(0);
}

void ShaderProgram::cleanUp() {
    stop();
    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
    glDeleteProgram(programID);
}

void ShaderProgram::bindAttribute(int attribute, std::string variableName) {
    glBindAttribLocation(programID, attribute, variableName.c_str());
}

GLuint ShaderProgram::getUniformLocation(const std::string &uniformName) {
    return glGetUniformLocation(programID, uniformName.c_str());
}

void ShaderProgram::loadFloat(GLint location, const float &value) {
    glUniform1f(location, value);
}

void ShaderProgram::loadVector(GLint location, const Vector3f &vector) {
    glUniform3f(location, vector.X, vector.Y, vector.Z);
}

void ShaderProgram::loadBoolean(GLint location, const bool &value) {
    float toLoad = 0;
    if (value) {
        toLoad = 1;
    }
    glUniform1f(location, toLoad);
}

void ShaderProgram::loadMatrix(GLint location, const Matrix &matrix) {
    glUniformMatrix4fv(location, 1, GL_FALSE, matrix.m);
}

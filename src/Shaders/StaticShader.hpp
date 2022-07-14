#ifndef StaticShader_hpp
#define StaticShader_hpp

#include "ShaderProgram.hpp"
#include "../Entities/Camera.hpp"
#include "../Toolbox/Maths.hpp"

class StaticShader : public ShaderProgram {
private:
    GLuint location_transformationMatrix;
    GLuint location_projectionMatrix;
    GLuint location_viewMatrix;
    static const std::string VERTEX_FILE;
    static const std::string FRAGMENT_FILE;
public:
    StaticShader();

    virtual ~StaticShader();

    void loadTransformationMatrix(const Matrix &matrix);

    void loadProjectionMatrix(const Matrix &projection);

    void loadViewMatrix(Camera camera);

protected:
    void bindAttributes() override;

    void getAllUniformLocations() override;
};

#endif

//
// Quelle: https://learnopengl.com/Model-Loading/Mesh
//

#pragma once

#include <vector>
#include "Vector3f.h"
#include "../GLincludes.hpp"
#include "../Shaders/StaticShader.hpp"
#include "Vector2f.h"

struct Vertex {
    Vector3f position;
    Vector3f normal;
    Vector2f texCoords;
};
struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    // Mesh Daten
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh();

    Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices,
         const std::vector<Texture> &textures);

    ~Mesh();
};

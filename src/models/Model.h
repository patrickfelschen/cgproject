//
// Created by Patrick on 01.08.2022.
//

#ifndef CG_MODEL_H
#define CG_MODEL_H

#include <iostream>
#include <vector>
#include "GL/glew.h"
#include "../maths/Vector3f.h"
#include "../utils/Loader.h"
#include "../shaders/Shader.h"
#include "../textures/Texture.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/Importer.hpp"
#include "../maths/Vector2f.h"

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)
#define INVALID_MATERIAL 0xFFFFFFFF

#define POSITION_LOCATION 0
#define TEX_COORD_LOCATION 1
#define NORMAL_LOCATION 2

enum BUFFER_TYPE {
    INDEX_BUFFER    = 0,
    POS_VB          = 1,
    TEXCOORD_VB     = 2,
    NORMAL_VB       = 3,
    WVP_MAT_VB      = 4,
    WORLD_MAT_VB    = 5,
    NUM_BUFFERS     = 6
};

struct BasicMeshEntry {
    BasicMeshEntry() {
        numIndices = 0;
        baseVertex = 0;
        baseIndex  = 0;
        materialIndex = INVALID_MATERIAL;
    }

    unsigned int numIndices;
    unsigned int baseVertex;
    unsigned int baseIndex;
    unsigned int materialIndex;
};

class Model {
public:
    explicit Model(const Shader &shader);
    ~Model() = default;

    void update(float deltaTime);
    void render(const Camera &camera);

    void setPosition(const Vector3f& v);
    void setScale(const float& v);
    void setRotation(const Vector3f& v, const float& a);

    bool loadMesh(const char* filename);

private:
    GLuint VAO = 0;

    GLuint buffers[NUM_BUFFERS] = { 0 };

    Shader shader;

    std::vector<BasicMeshEntry> meshes;
    std::vector<Texture*> textures;

    std::vector<Vector3f> positions;
    std::vector<Vector3f> normals;
    std::vector<Vector2f> texCoords;
    std::vector<unsigned int> indices;

    Matrix transform;

    void clear();
    bool initFromScene(const aiScene* pScene, const char* filename);
    void countVerticesAndIndices(const aiScene* pScene, unsigned int& numVertices, unsigned int& numIndices);
    void reserveSpace(unsigned int numVertices, unsigned int numIndices);
    void initAllMeshes(const aiScene* pScene);
    void initSingleMesh(const aiMesh* pAiMesh);
    bool initMaterials(const aiScene* pScene, const std::string& filename);
    void populateBuffers();
};


#endif //CG_MODEL_H

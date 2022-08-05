//
// Created by Patrick on 01.08.2022.
//

#ifndef CG_OBJECTMODEL_H
#define CG_OBJECTMODEL_H

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
#include "Model.h"

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)
#define INVALID_MATERIAL 0xFFFFFFFF

#define POSITION_LOCATION 0
#define TEX_COORD_LOCATION 1
#define NORMAL_LOCATION 2

enum BUFFER_TYPE {
    INDEX_BUFFER = 0,
    POS_VB = 1,
    TEXCOORD_VB = 2,
    NORMAL_VB = 3,
    WVP_MAT_VB = 4,
    WORLD_MAT_VB = 5,
    NUM_BUFFERS = 6
};

struct BasicMeshEntry {
    BasicMeshEntry() {
        numIndices = 0;
        baseVertex = 0;
        baseIndex = 0;
        materialIndex = INVALID_MATERIAL;
    }

    unsigned int numIndices;
    unsigned int baseVertex;
    unsigned int baseIndex;
    unsigned int materialIndex;
};

struct Material {
    Material() {
        pDiffuse = nullptr;
        pSpecular = nullptr;
        ambientColor = Color(1.0f, 1.0f, 1.0f);
        diffuseColor = Color(1.0f, 1.0f, 1.0f);
        specularColor = Color(1.0f, 1.0f, 1.0f);
    }

    Texture* pDiffuse;
    Texture* pSpecular;
    Color ambientColor;
    Color diffuseColor;
    Color specularColor;
};

class ObjectModel : public Model {
public:
    explicit ObjectModel(Shader *shader, const char *filename);

    ~ObjectModel() override = default;

    void update(float deltaTime) override;

    void render(const Camera &camera) override;

private:
    GLuint VAO = 0;

    bool useTexture = false;
    GLuint useTextureLoc    = 0;
    GLuint diffuseColorLoc  = 0;
    GLuint specularColorLoc = 0;
    GLuint ambientColorLoc  = 0;

    GLuint buffers[NUM_BUFFERS] = {0};

    std::vector<BasicMeshEntry> meshes;
    std::vector<Material> materials;

    std::vector<Vector3f> positions;
    std::vector<Vector3f> normals;
    std::vector<Vector2f> texCoords;
    std::vector<unsigned int> indices;

    bool loadMesh(const char *filename);

    void clear();

    bool initFromScene(const aiScene *pScene, const char *filename);

    void countVerticesAndIndices(const aiScene *pScene, unsigned int &numVertices, unsigned int &numIndices);

    void reserveSpace(unsigned int numVertices, unsigned int numIndices);

    void initAllMeshes(const aiScene *pScene);

    void initSingleMesh(const aiMesh *pAiMesh);

    bool initMaterials(const aiScene *pScene, const std::string &filename);

    void loadTextures(const std::string& dir, const aiMaterial* pMaterial, int index);

    void loadDiffuseTexture(const std::string& dir, const aiMaterial* pMaterial, int index);

    void loadSpecularTexture(const std::string& dir, const aiMaterial* pMaterial, int index);

    void loadColors(const aiMaterial* pMaterial, int index);

    void populateBuffers();


};


#endif //CG_OBJECTMODEL_H

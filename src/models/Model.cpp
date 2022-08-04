//
// Created by Patrick on 01.08.2022.
//

#include "Model.h"
#include "../utils/Vertex.h"

Model::Model(const Shader &shader) : shader(shader) {
    transform.identity();
}

void Model::update(float deltaTime) {
//    Matrix scale = Matrix().identity();
//    scale.scale(0.2f);
//
//    Matrix rotation = Matrix().identity();
//    rotation.rotationY(0.0f);
//
//    Matrix translation = Matrix().identity();
//    translation.translation(0.0f, 0.0f, 0.0f);
//
//    Matrix worldTransformation = translation * rotation * scale;

    shader.setModelTransform(transform);
}

void Model::render(const Camera &camera) {
    shader.activate(camera);

    glBindVertexArray(VAO);

    for(unsigned int i = 0; i < meshes.size(); i++) {
        unsigned int materialIndex = meshes[i].materialIndex;

        assert(materialIndex < textures.size());

        if(textures[materialIndex])
           textures[materialIndex]->activate(i);

        glDrawElementsBaseVertex(GL_TRIANGLES,
                                 meshes[i].numIndices,
                                 GL_UNSIGNED_INT,
                                 (void*)(sizeof(unsigned int) * meshes[i].baseIndex),
                                 meshes[i].baseVertex);

        textures[materialIndex]->deactivate();
    }

    glBindVertexArray(0);
    shader.deactivate();
}

void Model::setPosition(const Vector3f &v) {
    transform.translation(v);
}

void Model::setScale(const float &v) {
    transform.scale(v);
}

void Model::setRotation(const Vector3f &v, const float &a) {
    transform.rotationAxis(v, a);
}

bool Model::loadMesh(const char *filename) {
    clear();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(ARRAY_SIZE_IN_ELEMENTS(buffers), buffers);

    bool ret = false;
    Assimp::Importer importer;

    const aiScene* pScene = importer.ReadFile(filename, ASSIMP_LOAD_FLAGS);

    if(!pScene) {
        std::cerr << "ERROR::MODEL: " << importer.GetErrorString() << std::endl;
        exit(EXIT_FAILURE);
    }

    ret = initFromScene(pScene, filename);

    glBindVertexArray(0);

    return ret;
}

void Model::clear() {
    std::destroy(textures.begin(), textures.end());

//    if(buffers[0] != 0)
//        glDeleteBuffers(ARRAY_SIZE_IN_ELEMENTS)

    if(VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
}

bool Model::initFromScene(const aiScene *pScene, const char *filename) {
    meshes.resize(pScene->mNumMeshes);
    textures.resize(pScene->mNumMaterials);

    unsigned int numVertices = 0;
    unsigned int numIndices  = 0;

    countVerticesAndIndices(pScene, numVertices, numIndices);

    reserveSpace(numVertices, numIndices);

    initAllMeshes(pScene);

    if(!initMaterials(pScene, filename)) {
        std::cerr << "ERROR::MODEL: could not initialize materials" << std::endl;
        exit(EXIT_FAILURE);
    }

    populateBuffers();

    return true;
}

void Model::countVerticesAndIndices(const aiScene *pScene, unsigned int &numVertices, unsigned int &numIndices) {
    for(unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].materialIndex = pScene->mMeshes[i]->mMaterialIndex;
        meshes[i].numIndices    = pScene->mMeshes[i]->mNumFaces * 3; // Flag: aiProcess_Triangulate -> alle Polygone werden zu Dreiecken, deswegen * 3
        meshes[i].baseVertex    = numVertices;
        meshes[i].baseIndex     = numIndices;

        numVertices += pScene->mMeshes[i]->mNumVertices;
        numIndices  += meshes[i].numIndices;
    }
}

void Model::reserveSpace(unsigned int numVertices, unsigned int numIndices) {
    positions.reserve(numVertices);
    normals.reserve(numVertices);
    texCoords.reserve(numVertices);
    indices.reserve(numIndices);
}

void Model::initAllMeshes(const aiScene *pScene) {
    for(unsigned int i = 0; i < meshes.size(); i++) {
        const aiMesh* pAiMesh = pScene->mMeshes[i];
        initSingleMesh(pAiMesh);
    }
}

void Model::initSingleMesh(const aiMesh *pAiMesh) {
    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    for(unsigned int i = 0; i < pAiMesh->mNumVertices; i++) {
        const aiVector3D& pPos      = pAiMesh->mVertices[i];
        const aiVector3D& pNormal   = pAiMesh->mNormals[i];
        const aiVector3D& pTexCoord = pAiMesh->HasTextureCoords(0) ? pAiMesh->mTextureCoords[0][i] : Zero3D;

        positions.push_back(Vector3f(pPos.x, pPos.y, pPos.z));
        normals.push_back(Vector3f(pNormal.x, pNormal.y, pNormal.z));
        texCoords.push_back(Vector2f(pTexCoord.x, pTexCoord.y));
    }

    for(unsigned int i = 0; i < pAiMesh->mNumFaces; i++) {
        const aiFace& face = pAiMesh->mFaces[i];
        assert(face.mNumIndices == 3);
        indices.push_back(face.mIndices[0]);
        indices.push_back(face.mIndices[1]);
        indices.push_back(face.mIndices[2]);
    }
}

bool Model::initMaterials(const aiScene *pScene, const std::string& filename) {
    std::string::size_type slashIndex = filename.find_last_of("/");
    std::string dir;

    if(slashIndex == std::string::npos)
        dir = ".";
    else if(slashIndex == 0)
        dir = "/";
    else
        dir = filename.substr(0, slashIndex);

    bool ret = true;

    for(unsigned int i = 0; i < pScene->mNumMaterials; i++) {
        const aiMaterial* pMaterial = pScene->mMaterials[i];

        textures[i] = NULL;

        if(pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString path;

            if(pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                std::string p(path.data);

                if(p.substr(0, 2) == ".\\")
                    p = p.substr(2, p.size() - 2);

                std::string fullPath = dir + "/" + p;

                textures[i] = new Texture(fullPath.c_str());

                if(!textures[i]) {
                    std::cerr << "ERROR::MODEL: error loading texture" << std::endl;
                    ret = false;
                }
            }
        }
    }

    return ret;
}

void Model::populateBuffers() {
    glBindBuffer(GL_ARRAY_BUFFER, buffers[POS_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions[0]) * positions.size(), &positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(POSITION_LOCATION);
    glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords[0]) * texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(TEX_COORD_LOCATION);
    glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), &normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(NORMAL_LOCATION);
    glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[INDEX_BUFFER]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);
}

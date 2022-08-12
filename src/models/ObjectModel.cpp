//
// Created by Patrick on 01.08.2022.
//

#include "ObjectModel.h"
#include "../utils/Vertex.h"
ObjectModel::ObjectModel(Shader *shader, const char *filename) : Model(shader) {
    loadMesh(filename);
}

void ObjectModel::update(float deltaTime) {
    Model::update(deltaTime);
}

void ObjectModel::render(const Camera &camera) {
    shader->activate(camera);

    glBindVertexArray(VAO);

    for (auto &mesh: meshes) {
        unsigned int materialIndex = mesh.materialIndex;

        assert(materialIndex < materials.size());

        if (materials[materialIndex].pDiffuse) {
            materials[materialIndex].pDiffuse->activate(0);
        }
        if (materials[materialIndex].pSpecular) {
            materials[materialIndex].pSpecular->activate(1);
        }

        shader->setUniform("uMaterial.ambientColor", materials[materialIndex].ambientColor);
        shader->setUniform("uMaterial.diffuseColor", materials[materialIndex].diffuseColor);
        shader->setUniform("uMaterial.specularColor", materials[materialIndex].specularColor);
        shader->setUniform("uMaterial.shininess", materials[materialIndex].shininess);

        Model::render(camera);

        glDrawElementsBaseVertex(
                GL_TRIANGLES,
                mesh.numIndices,
                GL_UNSIGNED_INT,
                (void *) (sizeof(unsigned int) * mesh.baseIndex),
                mesh.baseVertex
        );

        if (materials[materialIndex].pDiffuse) {
            materials[materialIndex].pDiffuse->deactivate();
        }
        if(materials[materialIndex].pSpecular) {
            materials[materialIndex].pSpecular->deactivate();
        }
    }

    glBindVertexArray(0);
    shader->deactivate();
}

bool ObjectModel::loadMesh(const char *filename) {
    clear();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(ARRAY_SIZE_IN_ELEMENTS(buffers), buffers);

    bool ret = false;
    Assimp::Importer importer;

    const aiScene *pScene = importer.ReadFile(filename, ASSIMP_LOAD_FLAGS);

    if (!pScene) {
        std::cerr << "ERROR::MODEL: " << importer.GetErrorString() << std::endl;
        exit(EXIT_FAILURE);
    }

    ret = initFromScene(pScene, filename);

    glBindVertexArray(0);

    return ret;
}

void ObjectModel::clear() {
    std::destroy(materials.begin(), materials.end());

    if (VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
}

bool ObjectModel::initFromScene(const aiScene *pScene, const char *filename) {
    meshes.resize(pScene->mNumMeshes);
    materials.resize(pScene->mNumMaterials);

    unsigned int numVertices = 0;
    unsigned int numIndices = 0;

    countVerticesAndIndices(pScene, numVertices, numIndices);

    reserveSpace(numVertices, numIndices);

    initAllMeshes(pScene);

    if (!initMaterials(pScene, filename)) {
        std::cerr << "ERROR::MODEL: could not initialize materials" << std::endl;
        exit(EXIT_FAILURE);
    }

    populateBuffers();

    return true;
}

void ObjectModel::countVerticesAndIndices(const aiScene *pScene, unsigned int &numVertices, unsigned int &numIndices) {
    for (unsigned int i = 0; i < meshes.size(); i++) {
        meshes[i].materialIndex = pScene->mMeshes[i]->mMaterialIndex;
        meshes[i].numIndices = pScene->mMeshes[i]->mNumFaces *
                               3; // Flag: aiProcess_Triangulate -> alle Polygone werden zu Dreiecken, deswegen * 3
        meshes[i].baseVertex = numVertices;
        meshes[i].baseIndex = numIndices;

        numVertices += pScene->mMeshes[i]->mNumVertices;
        numIndices += meshes[i].numIndices;
    }
}

void ObjectModel::reserveSpace(unsigned int numVertices, unsigned int numIndices) {
    positions.reserve(numVertices);
    normals.reserve(numVertices);
    texCoords.reserve(numVertices);
    indices.reserve(numIndices);
}

void ObjectModel::initAllMeshes(const aiScene *pScene) {
    for (unsigned int i = 0; i < meshes.size(); i++) {
        const aiMesh *pAiMesh = pScene->mMeshes[i];
        initSingleMesh(pAiMesh);
    }
}

void ObjectModel::initSingleMesh(const aiMesh *pAiMesh) {
    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    for (unsigned int i = 0; i < pAiMesh->mNumVertices; i++) {
        const aiVector3D &pPos = pAiMesh->mVertices[i];
        const aiVector3D &pNormal = pAiMesh->mNormals[i];
        const aiVector3D &pTexCoord = pAiMesh->HasTextureCoords(0) ? pAiMesh->mTextureCoords[0][i] : Zero3D;

        positions.push_back(Vector3f(pPos.x, pPos.y, pPos.z));
        normals.push_back(Vector3f(pNormal.x, pNormal.y, pNormal.z));
        texCoords.push_back(Vector2f(pTexCoord.x, pTexCoord.y));
    }

    for (unsigned int i = 0; i < pAiMesh->mNumFaces; i++) {
        const aiFace &face = pAiMesh->mFaces[i];
        assert(face.mNumIndices == 3);
        indices.push_back(face.mIndices[0]);
        indices.push_back(face.mIndices[1]);
        indices.push_back(face.mIndices[2]);
    }
}

bool ObjectModel::initMaterials(const aiScene *pScene, const std::string &filename) {
    std::string::size_type slashIndex = filename.find_last_of("/");
    std::string dir;

    if (slashIndex == std::string::npos)
        dir = ".";
    else if (slashIndex == 0)
        dir = "/";
    else
        dir = filename.substr(0, slashIndex);

    bool ret = true;

    for (unsigned int i = 0; i < pScene->mNumMaterials; i++) {
        const aiMaterial* pMaterial = pScene->mMaterials[i];

        loadTextures(dir, pMaterial, i);
        loadColors(pMaterial, i);
    }

    return ret;
}


void ObjectModel::loadTextures(const std::string& dir, const aiMaterial* pMaterial, int index) {
    loadDiffuseTexture(dir, pMaterial, index);
    loadSpecularTexture(dir, pMaterial, index);
}

void ObjectModel::loadDiffuseTexture(const std::string &dir, const aiMaterial *pMaterial, int index) {
    materials[index].pDiffuse = nullptr;

    if(pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
        aiString path;

        if(pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
            std::string p(path.data);

            if (p.substr(0, 2) == ".\\") {
                p = p.substr(2, p.size() - 2);
            }

            std::string fullPath = dir + "/" + p;

            materials[index].pDiffuse = new Texture(fullPath.c_str());

            if (!materials[index].pDiffuse) {
                std::cerr << "ERROR::MODEL: error loading diffuse texture" << std::endl;
            }
        }
    }
}

void ObjectModel::loadSpecularTexture(const std::string &dir, const aiMaterial *pMaterial, int index) {
    materials[index].pSpecular = nullptr;

    if(pMaterial->GetTextureCount(aiTextureType_SPECULAR) > 0) {
        aiString path;

        if(pMaterial->GetTexture(aiTextureType_SPECULAR, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
            std::string p(path.data);

            if (p.substr(0, 2) == ".\\") {
                p = p.substr(2, p.size() - 2);
            }

            std::string fullPath = dir + "/" + p;

            materials[index].pSpecular = new Texture(fullPath.c_str());

            if (!materials[index].pSpecular) {
                std::cerr << "ERROR::MODEL: error loading specular texture" << std::endl;
            }
        }
    }
}

void ObjectModel::loadColors(const aiMaterial *pMaterial, int index) {
    aiColor3D ambientColor(0.0f, 0.0f, 0.0f);
    aiColor3D diffuseColor(0.0f, 0.0f, 0.0f);
    aiColor3D specularColor(0.0f, 0.0f, 0.0f);
    float shininess;


    if(pMaterial->Get(AI_MATKEY_COLOR_AMBIENT, ambientColor) == AI_SUCCESS) {
        materials[index].ambientColor.r = ambientColor.r;
        materials[index].ambientColor.g = ambientColor.g;
        materials[index].ambientColor.b = ambientColor.b;
    }
    else {
        materials[index].ambientColor = Color(1.0f, 1.0f, 1.0f);
    }

    if(pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor) == AI_SUCCESS) {
        materials[index].diffuseColor.r = diffuseColor.r;
        materials[index].diffuseColor.g = diffuseColor.g;
        materials[index].diffuseColor.b = diffuseColor.b;
    }
    else {
        materials[index].diffuseColor = Color(1.0f, 1.0f, 1.0f);
    }

    if(pMaterial->Get(AI_MATKEY_COLOR_SPECULAR, specularColor) == AI_SUCCESS) {
        materials[index].specularColor.r = specularColor.r;
        materials[index].specularColor.g = specularColor.g;
        materials[index].specularColor.b = specularColor.b;
    }
    else {
        materials[index].specularColor = Color(1.0f, 1.0f, 1.0f);
    }

    if(aiGetMaterialFloat(pMaterial, AI_MATKEY_SHININESS, &shininess) == AI_SUCCESS) {
        materials[index].shininess = shininess;
    }
    else {
        materials[index].shininess = 20.0f;
    }
}


void ObjectModel::populateBuffers() {
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

//
// Created by Patrick on 17.08.2022.
// https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/model.h
//

#include "ObjectModel.h"


ObjectModel::ObjectModel(Shader *shader, const std::string &filePath) : Model(shader) {
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(
            filePath,
            aiProcess_Triangulate |
            aiProcess_GenSmoothNormals |
            aiProcess_FlipUVs |
            aiProcess_CalcTangentSpace
    );
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP: " << importer.GetErrorString() << std::endl;
        return;
    }
    // retrieve the directory path of the filepath
    this->directory = filePath.substr(0, filePath.find_last_of('/'));
    this->processNode(scene->mRootNode, scene);
    this->setBoundingBox();
}

ObjectModel::~ObjectModel() = default;

void ObjectModel::update(float deltaTime) {
    Model::update(deltaTime);
}

void ObjectModel::render(const Camera &camera) {
    this->shader->activate(camera);
    Model::render(camera);
    for (auto &mesh: meshes) {
        mesh.render();
    }
    this->shader->deactivate();
}

void ObjectModel::processNode(aiNode *node, const aiScene *scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh ObjectModel::processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        Vector3f vector;
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.pos = vector;
        // normals
        if (mesh->HasNormals()) {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
        }
        // texture coordinates
        Vector2f texCoord;
        if (mesh->mTextureCoords[0]) {
            texCoord.x = mesh->mTextureCoords[0][i].x;
            texCoord.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoord0 = texCoord;
        } else {
            vertex.texCoord0 = Vector2f(0.0f, 0.0f);
        }
        if (mesh->mTextureCoords[1]) {
            texCoord.x = mesh->mTextureCoords[1][i].x;
            texCoord.y = mesh->mTextureCoords[1][i].y;
            vertex.texCoord1 = texCoord;
        } else {
            vertex.texCoord1 = Vector2f(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }
    // process materials
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    // 1. diffuse maps
    std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // return a mesh object created from the extracted mesh data
    return {vertices, indices, textures};
}

std::vector<Texture> ObjectModel::loadMaterialTextures(
        aiMaterial *mat,
        aiTextureType type,
        const std::string &typeName
) {
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString aiTexturePath;
        mat->GetTexture(type, i, &aiTexturePath);
        std::string filePath = this->directory + '/' + aiTexturePath.C_Str();
        // Cache abfragen ob Textur zuvor geladen
        if (textureCache.find(filePath) != textureCache.end()) {
            textures.push_back(textureCache[filePath]);
            //std::cout << "TextureCache HIT" << std::endl;
            continue;
        }
        // Cache füllen
        Texture newTexture = Texture(filePath, typeName);
        textureCache[filePath] = newTexture;
        textures.push_back(newTexture);
    }
    return textures;
}

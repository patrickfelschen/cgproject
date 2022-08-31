//
// Created by Patrick on 17.08.2022.
// https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/model.h
//

#include "ObjectModel.h"
#include "../shaders/PhongShader.h"


ObjectModel::ObjectModel(Shader *shader, const std::string &filePath) : Model() {
    this->shader = shader;
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
    std::cout << "OBJECTMODEL::LOADED: " << filePath << std::endl;
    this->setBoundingBox();
}

ObjectModel::~ObjectModel() = default;

void ObjectModel::render() const {
    this->shader->activate();
    for (auto &mesh: meshes) {
        mesh.render(shader);
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
    // Vertices
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
            vertex.texCoord0 = Vector2f(1.0f, 1.0f);
        }
        if (mesh->mTextureCoords[1]) {
            texCoord.x = mesh->mTextureCoords[1][i].x;
            texCoord.y = mesh->mTextureCoords[1][i].y;
            vertex.texCoord1 = texCoord;
        } else {
            vertex.texCoord1 = Vector2f(1.0f, 1.0f);
        }
        vertices.push_back(vertex);
    }
    // Indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }
    // Materials
    unsigned int diffCount = 0;
    unsigned int specCount = 0;
    aiMaterial *uiMaterial = scene->mMaterials[mesh->mMaterialIndex];
    // 1. diffuse maps
    std::vector<Texture> diffuseMaps = loadMaterialTextures(uiMaterial, aiTextureType_DIFFUSE, "texture_diffuse", diffCount);
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    std::vector<Texture> specularMaps = loadMaterialTextures(uiMaterial, aiTextureType_SPECULAR, "texture_specular", specCount);
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    // std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    // textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    // std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    // textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    Material material;
    aiColor4D aiColor;
    float shininess = 1;
    uiMaterial->Get(AI_MATKEY_COLOR_AMBIENT, aiColor);
    material.ambient = Color(aiColor);
    uiMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, aiColor);
    material.diffuse = Color(aiColor);
    uiMaterial->Get(AI_MATKEY_COLOR_SPECULAR, aiColor);
    material.specular = Color(aiColor);
    uiMaterial->Get(AI_MATKEY_SHININESS, shininess);
    material.shininess = shininess;

    if (diffCount == 0) {
        Texture diffTex("texture_diffuse");
        textures.push_back(diffTex);
    }

    if (specCount == 0) {
        Texture specTex("texture_specular");
        textures.push_back(specTex);
    }

    // return a mesh object created from the extracted mesh data
    return {vertices, indices, textures, material};
}

std::vector<Texture> ObjectModel::loadMaterialTextures(
        aiMaterial *mat,
        aiTextureType type,
        const std::string &typeName,
        unsigned int &textureCount
) {
    std::vector<Texture> textures;
    textureCount = mat->GetTextureCount(type);
    for (unsigned int i = 0; i < textureCount; i++) {
        aiString aiTexturePath;
        mat->GetTexture(type, i, &aiTexturePath);
        std::string filePath = this->directory + '/' + aiTexturePath.C_Str();
        // Cache abfragen ob Textur zuvor geladen
        if (textureCache.find(filePath) != textureCache.end()) {
            textures.push_back(textureCache[filePath]);
            std::cout << "OBJECTMODEL::LOADMATERIALTEXTURE: TextureCache HIT " << filePath << std::endl;
            continue;
        }
        // Cache füllen
        Texture newTexture = Texture(filePath, typeName);
        textureCache[filePath] = newTexture;
        textures.push_back(newTexture);
    }
    return textures;
}

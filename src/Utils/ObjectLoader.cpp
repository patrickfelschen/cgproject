//
// Created by Patrick on 15.07.2022.
//

#include "ObjectLoader.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"


RawModel ObjectLoader::loadObjectModel(const std::string &filePath, Loader &loader) {
    Assimp::Importer importer;
    // Lädt eine Objekt und transformiert alle Formen zu Dreiecken.
    // Zudem werden die Texturkoordinanten um die y-Achese gedreht, um diese in
    // OpenGL richtig verwenden zu können.
    const aiScene *scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

    // Prüft ob die Scene vollständig und nicht null ist.
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR:MODEL::Fehler beim Laden eines Objekts" << std::endl;
        std::cout << importer.GetErrorString() << std::endl;
        return RawModel();
    }

    // Geht alle Knoten rekursiv durch
    processNode(scene->mRootNode, scene);

    return loader.loadToVAO(meshes[0].vertices, meshes[0].indices);
}

void ObjectLoader::processNode(aiNode *node, const aiScene *scene) {
    // Bearbeite alle Meshes vom Knoten
    for (unsigned int nodeIndex = 0; nodeIndex < node->mNumMeshes; nodeIndex++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[nodeIndex]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // Gehe alle Kindknoten durch
    for (unsigned int childIndex = 0; childIndex < node->mNumChildren; childIndex++) {
        processNode(node->mChildren[childIndex], scene);
    }
}

Mesh ObjectLoader::processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // Bearbeite die Vertices
    for (unsigned int vertexIndex = 0; vertexIndex < mesh->mNumVertices; vertexIndex++) {
        Vertex vertex;

        // Laden der Vertex-Position
        if (mesh->HasPositions()) {
            Vector3f position;
            position.X = mesh->mVertices[vertexIndex].x;
            position.Y = mesh->mVertices[vertexIndex].y;
            position.Z = mesh->mVertices[vertexIndex].z;
            vertex.position = position;
        }

        // Laden der Vertex-Normalen
        if (mesh->HasNormals()) {
            Vector3f normal;
            normal.X = mesh->mNormals[vertexIndex].x;
            normal.Y = mesh->mNormals[vertexIndex].y;
            normal.Z = mesh->mNormals[vertexIndex].z;
            vertex.normal = normal;
        }
        // Prüfe ob Texturkoordinaten vorhanden sind.
        // Assimp kann bis zu 8 verschiedene Texturkoordinaten haben
        // im Rahmen des Projektes wird nur der erste Satz an Koordinaten verwendet.
        // Sind garkeine vorhanden, wird ein Standardwert angenommen.
        if (mesh->HasTextureCoords(0)) {
            Vector2f texCoords;
            texCoords.X = mesh->mTextureCoords[0][vertexIndex].x;
            texCoords.Y = mesh->mTextureCoords[0][vertexIndex].y;
            vertex.texCoords = texCoords;
        } else {
            vertex.texCoords.X = 0.0f;
            vertex.texCoords.Y = 0.0f;
        }
        vertices.push_back(vertex);
    }

    // Bearbeite die Indices
    for (unsigned int faceIndex = 0; faceIndex < mesh->mNumFaces; faceIndex++) {
        aiFace face = mesh->mFaces[faceIndex];
        for (unsigned int index = 0; index < face.mNumIndices; index++) {
            indices.push_back(face.mIndices[index]);
        }
    }

    /* Bearbeite die Materialien
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        // Lade die diffusen Texturen und füge diese in die Liste ein
        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        // Lade die specularen Texturen und füge diese in die Liste ein
        std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }
    */

    // Erstelle ein Mesh aus den erfassten Eigenschaften
    return Mesh(vertices, indices, textures);
}

ObjectLoader::ObjectLoader() {

}

ObjectLoader::~ObjectLoader() {

}

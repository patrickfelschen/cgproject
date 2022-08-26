//
// Created by Patrick on 17.08.2022.
//

#ifndef CG_OBJECTMODEL_H
#define CG_OBJECTMODEL_H


#include "Model.h"
#include "../utils/Texture.h"
#include "../utils/Mesh.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "../shaders/PhongShader.h"
#include <unordered_map>

class ObjectModel : public Model {
public:
    explicit ObjectModel(PhongShader *shader, const std::string &filePath);

    ~ObjectModel() override;

    void render() const override;

    PhongShader *shader;
private:
    std::unordered_map<std::string, Texture> textureCache;
    std::string directory;

    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string &typeName, unsigned int& textureCount);

};


#endif //CG_OBJECTMODEL_H

//
// Created by Patrick on 15.07.2022.
//

#ifndef CG_OBJECTLOADER_H
#define CG_OBJECTLOADER_H


#include <string>
#include "../Models/RawModel.hpp"
#include "../RenderEngine/Loader.hpp"
#include "assimp/scene.h"
#include "Mesh.h"

class ObjectLoader {
public:
    RawModel loadObjectModel(const std::string &fileName, Loader &loader);

    ObjectLoader();

    virtual ~ObjectLoader();

private:
    std::vector<Mesh> meshes;

    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
};


#endif //CG_OBJECTLOADER_H

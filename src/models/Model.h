//
// Created by Patrick on 04.08.2022.
//

#ifndef CG_MODEL_H
#define CG_MODEL_H


#include "../maths/Matrix.h"
#include "../utils/Camera.h"
#include "../shaders/Shader.h"
#include "../utils/Mesh.h"
#include "../utils/Aabb.h"

class Model {
public:
    explicit Model() = default;

    virtual ~Model() = default;

    /**
     * Muss vom Model implementiert werden.
     * i.d.R Shader aktivieren -> Meshes zeichnen -> Shader deaktivieren
     */
    virtual void render() const = 0;

    AABB getBoundingBox() const;

protected:
    // Alle Meshes die angezeigt werden sollen
    std::vector<Mesh> meshes;

    AABB boundingBox;

    void setBoundingBox();

private:
    void drawBoundingBox() const;
};


#endif //CG_MODEL_H

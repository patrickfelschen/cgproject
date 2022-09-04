//
// Created by Patrick on 04.08.2022.
//

#include "Model.h"

/**
 * Sucht aus allen Meshes die größte Ausdehnung in X-,Y- und Z-Richtung (positiv und negativ) und bildet daraus min und max
 * min und max liegen diagonal zueinander und bilden die Eckpunkte der Bounding Box
 */
void Model::setBoundingBox() {
    Vector3f min = Vector3f(0, 0, 0);
    Vector3f max = Vector3f(0, 0, 0);
    for (auto &mesh: meshes) {
        for (auto &vertex: mesh.vertices) {
            min.x = std::min(min.x, vertex.pos.x);
            min.y = std::min(min.y, vertex.pos.y);
            min.z = std::min(min.z, vertex.pos.z);

            max.x = std::max(max.x, vertex.pos.x);
            max.y = std::max(max.y, vertex.pos.y);
            max.z = std::max(max.z, vertex.pos.z);
        }
    }
    this->boundingBox.Min = min;
    this->boundingBox.Max = max;
}

AABB Model::getBoundingBox() const {
    return boundingBox;
}

/**
 * Zeichnet Linien der Bounding Box
 */
void Model::drawBoundingBox() const {
    glBegin(GL_LINES);

    glVertex3f(boundingBox.Min.x, boundingBox.Min.y, boundingBox.Min.z); // 1
    glVertex3f(-boundingBox.Min.x, boundingBox.Min.y, boundingBox.Min.z); // 2

    glVertex3f(boundingBox.Min.x, boundingBox.Min.y, boundingBox.Min.z); // 1
    glVertex3f(boundingBox.Min.x, -boundingBox.Min.y, boundingBox.Min.z); // 3

    glVertex3f(boundingBox.Min.x, boundingBox.Min.y, boundingBox.Min.z); // 1
    glVertex3f(boundingBox.Min.x, boundingBox.Min.y, -boundingBox.Min.z); // 4

    glVertex3f(boundingBox.Max.x, boundingBox.Max.y, boundingBox.Max.z); // 5
    glVertex3f(-boundingBox.Max.x, boundingBox.Max.y, boundingBox.Max.z); // 6

    glVertex3f(-boundingBox.Min.x, boundingBox.Min.y, boundingBox.Min.z); // 2
    glVertex3f(-boundingBox.Min.x, -boundingBox.Min.y, boundingBox.Min.z); // 7

    glVertex3f(boundingBox.Min.x, -boundingBox.Min.y, boundingBox.Min.z); // 3
    glVertex3f(-boundingBox.Min.x, -boundingBox.Min.y, boundingBox.Min.z); // 7

    glVertex3f(boundingBox.Min.x, -boundingBox.Min.y, boundingBox.Min.z); // 3
    glVertex3f(-boundingBox.Max.x, boundingBox.Max.y, boundingBox.Max.z); // 6

    glVertex3f(boundingBox.Min.x, boundingBox.Min.y, -boundingBox.Min.z); // 4
    glVertex3f(-boundingBox.Max.x, boundingBox.Max.y, boundingBox.Max.z); // 6

    glVertex3f(boundingBox.Max.x, boundingBox.Max.y, boundingBox.Max.z); // 5
    glVertex3f(-boundingBox.Min.x, -boundingBox.Min.y, boundingBox.Min.z); // 7

    glVertex3f(boundingBox.Max.x, -boundingBox.Max.y, boundingBox.Max.z); // 8
    glVertex3f(boundingBox.Max.x, boundingBox.Max.y, boundingBox.Max.z); // 5

    glVertex3f(boundingBox.Max.x, -boundingBox.Max.y, boundingBox.Max.z); // 8
    glVertex3f(boundingBox.Min.x, boundingBox.Min.y, -boundingBox.Min.z); // 4

    glVertex3f(boundingBox.Max.x, -boundingBox.Max.y, boundingBox.Max.z); // 8
    glVertex3f(-boundingBox.Min.x, boundingBox.Min.y, boundingBox.Min.z); // 2

    glEnd();
}







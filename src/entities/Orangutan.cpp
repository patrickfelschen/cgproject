//
// Created by Patrick on 04.08.2022.
//

#include "Orangutan.h"

Orangutan::Orangutan(Model *model) : Entity(model) {
    Entity::setPosition(0, 0, 2);
}

Orangutan::~Orangutan() = default;

void Orangutan::update(float deltaTime) {
    Entity::update(deltaTime);
}

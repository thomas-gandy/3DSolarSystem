#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

#include "sphere.hpp"

SphereVertexModel* SphereVertexModel::instance() {
    static SphereVertexModel ssvm = SphereVertexModel();
    return &ssvm;
}

SphereVertexModel::SphereVertexModel() {
    initVertices();
    initIndices();
    initGlObjects();
}

void SphereVertexModel::initVertices() {
    constexpr float stackAngleStep = M_PI / float(stacks);
    constexpr float sectorAngleStep = (2 * M_PI) / float(sectors);

    int stack, sector;
    float x, y, z, cosOfStackAngle;
    for (stack = 0; stack <= stacks; stack++) {
        y = radius * std::sin((M_PI / 2) - (stack * stackAngleStep));
        cosOfStackAngle = std::cos(stack * stackAngleStep);
        for (sector = 0; sector <= sectors; sector++) {
            x = radius * cosOfStackAngle * std::cos(sector * sectorAngleStep);
            z = radius * cosOfStackAngle * std::sin(sector * sectorAngleStep);
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
            vertices.push_back(float(sector) / sectors);
            vertices.push_back(float(stack) / stacks);
        }
    }
}

void SphereVertexModel::initIndices() {
    int k1, k2;
    for (int stack = 0; stack < stacks; stack++) {
        k1 = stack * sectors;
        k2 = k1 + sectors;
        for (int sector = 0; sector < sectors; sector++, k1++, k2++) {
            if (stack != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }
            if (stack != stacks - 1) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}

void SphereVertexModel::initGlObjects() {
    glGenVertexArrays(1, &vertexArrayObjectID);
    glBindVertexArray(vertexArrayObjectID);

    glGenBuffers(1, &vertexBufferObjectID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjectID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &elementBufferObjectID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObjectID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Sphere::Sphere(glm::vec3 pos) {
    worldCoord = pos;
    model = SphereVertexModel::instance();
}

void Sphere::update() {
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, worldCoord);
}

void Sphere::render() {
    glBindVertexArray(model->vertexArrayObjectID);
    glDrawElements(GL_TRIANGLES, model->indices.size(), GL_UNSIGNED_INT, 0);
}

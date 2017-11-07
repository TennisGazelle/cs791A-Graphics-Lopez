//
// Created by Daniel Lopez on 10/30/17.
//

#ifndef TUTORIAL_BILLBOARDLIST_H
#define TUTORIAL_BILLBOARDLIST_H

#include <shaders/billboardShader.h>
#include "graphics_headers.h"
#include "texture.h"

class BillboardList {
public:
    BillboardList();
    ~BillboardList();

    bool Init(const std::string& textureFileName);

    void Render(const glm::mat4& viewProjection, const glm::vec3& cameraPosWorldSpace);
private:
    void CreatePositionBuffer();

    GLuint VBO;
    Texture* billboardTexture;
    BillboardShader* bbShader;

    const unsigned int NUM_ROWS = 10;
    const unsigned int NUM_COLS = 10;
};


#endif //TUTORIAL_BILLBOARDLIST_H

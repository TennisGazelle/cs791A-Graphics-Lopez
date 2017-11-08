//
// Created by Daniel Lopez on 10/30/17.
//

#include <textureManager.h>
#include "billboardList.h"

BillboardList::BillboardList() {

}

BillboardList::~BillboardList() {

}

bool BillboardList::Init(const std::string &textureFileName) {
    if (!TMInstance->addTexture("dickbutt", textureFileName)){
        printf("error loading dicks in billboard list\n");
        return false;
    }
    billboardTexture = TMInstance->getTexture("dickbutt");

    CreatePositionBuffer();

    bbShader = new BillboardShader();
    if (!bbShader->Initialize()) {
        printf("error in initalizing billboard shader\n");
        return false;
    }
    if (!bbShader->LoadShader(GL_VERTEX_SHADER, "../shaders/billboard_vs.glsl") ||
        !bbShader->LoadShader(GL_GEOMETRY_SHADER, "../shaders/billboard_gs.glsl") ||
        !bbShader->LoadShader(GL_FRAGMENT_SHADER, "../shaders/billboard_fs.glsl")) {
        printf("billboard shader failed to load shaders from text");
        return false;
    }

    if (!bbShader->Finalize()) {
        printf("error in billboard finalizing\n");
        return false;
    }

    if (!bbShader->LinkShaderProps()) {
        printf("error in linking billboard shader\n");
        return false;
    }

    return true;
}

void BillboardList::Render(const glm::mat4 &viewProjection, const glm::vec3 &cameraPosWorldSpace) {
    // enable our shader
    bbShader->Enable();
    // set the VP in our shader (uniform)
    glUniformMatrix4fv(bbShader->vpMatrix, 1, GL_FALSE, glm::value_ptr(viewProjection));
    // set the camera position (uniform)
    glUniform3fv(bbShader->cameraPosition, 1, glm::value_ptr(cameraPosWorldSpace));
    // bind our texture to color
    billboardTexture->enable(COLOR_TEXTURE_UNIT);
    glUniform1i(bbShader->colorMap, COLOR_TEXTURE_UNIT_INDEX);
    TMInstance->setTextureUnit(0);
    TMInstance->enableTexture("dickbutt", COLOR_TEXTURE_UNIT);

    // the following is similar to a mesh render....:
    // enable attrib array
    glEnableVertexAttribArray(0);
    // bind buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // position vector passing in
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    // glDrawArrays
    glDrawArrays(GL_POINTS, 0, NUM_ROWS * NUM_COLS);
    // disable attrib array
    glDisableVertexAttribArray(0);
}

void BillboardList::CreatePositionBuffer() {
    std::vector<glm::vec3> positions;
    positions.reserve(NUM_COLS * NUM_ROWS);

    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            glm::vec3 position((float)i, 0, (float)j);
            positions.push_back(position);
        }
    }

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * positions.size(), &positions[0], GL_STATIC_DRAW);
}
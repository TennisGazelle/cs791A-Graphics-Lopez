//
// Created by Daniel Lopez on 11/5/17.
//

#include <vector>
#include "randomTexture.h"

RandomTexture::RandomTexture() : textureHandler(0) {

}

RandomTexture::~RandomTexture() {
    if (textureHandler != 0) {
        glDeleteTextures(1, &textureHandler);
    }
}

bool RandomTexture::Init(unsigned int size) {
    std::vector<glm::vec3> randomData(size);
    for (unsigned int i = 0; i < size; i++) {
        randomData[i].x = rand() / RAND_MAX;
        randomData[i].y = rand() / RAND_MAX;
        randomData[i].z = rand() / RAND_MAX;
    }

    glGenTextures(1, &textureHandler);
    glBindTexture(GL_TEXTURE_1D, textureHandler);
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, size, 0, GL_RGB, GL_FLOAT, &randomData[0]);
    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    return true;
}

void RandomTexture::Bind(GLenum textureUnit) {
    glActiveTexture(textureUnit);
    glBindBuffer(GL_TEXTURE_1D, textureHandler);
}
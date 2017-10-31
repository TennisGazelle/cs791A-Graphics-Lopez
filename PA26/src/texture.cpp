//
// Created by Daniel Lopez on 10/30/17.
//

#include "texture.h"

Texture::Texture() : textureHandler(0) {

}

Texture::~Texture() {
    if (textureHandler != 0) {
        glDeleteTextures(1, &textureHandler);
    }
}

bool Texture::loadTexture(const std::string &filename) {
    Magick::Image textureImage;
    Magick::Blob blob;
    textureImage.read(filename);
    size_t width = textureImage.columns();
    size_t height = textureImage.rows();
    textureImage.write(&blob, "RGBA");

    if (!textureImage.isValid()) {
        return false;
    }

    glGenTextures(1, &textureHandler);
    glBindTexture(GL_TEXTURE_2D, textureHandler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //or GL_NEAREST
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //or GL_NEAREST
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, blob.data());

    return true;
}

void Texture::enable(GLenum textureUnit) {
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, textureHandler);
}

void Texture::disable() {
    glDisable(GL_TEXTURE_2D);
}


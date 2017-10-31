//
// Created by Daniel Lopez on 10/30/17.
//

#ifndef TUTORIAL_TEXTURE_H
#define TUTORIAL_TEXTURE_H


#include <string>
#include <Magick++.h>

#include "graphics_headers.h"

class Texture {
public:
    Texture();
    ~Texture();
    bool loadTexture(const std::string& filename);
    void enable(GLenum textureUnit);
    void disable();

private:
    GLuint textureHandler;
};


#endif //TUTORIAL_TEXTURE_H
